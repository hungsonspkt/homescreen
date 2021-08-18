/*
 * Copyright (C) 2016, 2017 Mentor Graphics Development (Deutschland) GmbH
 * Copyright (c) 2017, 2018 TOYOTA MOTOR CORPORATION
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <QGuiApplication>
#include <QCommandLineParser>
#include <QtCore/QUrlQuery>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlComponent>
#include <QtQml/qqml.h>
#include <QQuickWindow>
#include <QTimer>


#include <weather.h>
#include <bluetooth.h>
#include "applicationlauncher.h"
#include "statusbarmodel.h"
#include "mastervolume.h"
#include "homescreenhandler.h"
#include "hmi-debug.h"
#include "chromecontroller.h"

#include <qpa/qplatformnativeinterface.h>
#include <wayland-client.h>

#include "wayland-agl-shell-client-protocol.h"
#include "shell.h"

#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions
#include<pthread.h>

pthread_t tid;
int fdUSB = 0x00;

void printserial()
{
	fdUSB = open( "/dev/ttyS0", O_RDWR| O_NOCTTY );
    struct termios tty;
	struct termios tty_old;
	memset (&tty, 0, sizeof tty);

	/* Error Handling */
	if ( tcgetattr ( fdUSB, &tty ) != 0 ) {
	   printf("error tcgetattr\n");
	   return;
	}

	/* Save old tty parameters */
	tty_old = tty;

	/* Set Baud Rate */
	cfsetospeed (&tty, (speed_t)B115200);
	cfsetispeed (&tty, (speed_t)B115200);

	/* Setting other Port Stuff */
	tty.c_cflag     &=  ~PARENB;            // Make 8n1
	tty.c_cflag     &=  ~CSTOPB;
	tty.c_cflag     &=  ~CSIZE;
	tty.c_cflag     |=  CS8;

	tty.c_cflag     &=  ~CRTSCTS;           // no flow control
	tty.c_cc[VMIN]   =  1;                  // read doesn't block
	tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
	tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

	/* Make raw */
	cfmakeraw(&tty);

	/* Flush Port, then applies attributes */
	tcflush( fdUSB, TCIFLUSH );
	if ( tcsetattr ( fdUSB, TCSANOW, &tty ) != 0) {
	   printf("flush serial bufer failed\n");
	   return;
	}
	if(fdUSB != 0x00)
	{
		write (fdUSB, "K-Auto hello!\n", strlen("K-Auto hello!\n")); 
	}
	close(fdUSB);
	fdUSB = 0x00;
}

void* doSomeThing(void *arg)
{
	usleep(10000000);//10s
	
    while(1)
    {
    	usleep(1000000);//1s
    	printserial();
    }

    return NULL;
}

static void
global_add(void *data, struct wl_registry *reg, uint32_t name,
	   const char *interface, uint32_t)
{
	struct agl_shell **shell = static_cast<struct agl_shell **>(data);

	if (strcmp(interface, agl_shell_interface.name) == 0) {
		*shell = static_cast<struct agl_shell *>(
			wl_registry_bind(reg, name, &agl_shell_interface, 1)
		);
	}
}

static void
global_remove(void *data, struct wl_registry *reg, uint32_t id)
{
	/* Don't care */
	(void) data;
	(void) reg;
	(void) id;
}

static const struct wl_registry_listener registry_listener = {
	global_add,
	global_remove,
};

static struct wl_surface *
getWlSurface(QPlatformNativeInterface *native, QWindow *window)
{
	void *surf = native->nativeResourceForWindow("surface", window);
	return static_cast<struct ::wl_surface *>(surf);
}

static struct wl_output *
getWlOutput(QPlatformNativeInterface *native, QScreen *screen)
{
	void *output = native->nativeResourceForScreen("output", screen);
	return static_cast<struct ::wl_output*>(output);
}


static struct agl_shell *
register_agl_shell(QPlatformNativeInterface *native)
{
	struct wl_display *wl;
	struct wl_registry *registry;
	struct agl_shell *shell = nullptr;

	wl = static_cast<struct wl_display *>(
			native->nativeResourceForIntegration("display")
	);
	registry = wl_display_get_registry(wl);

	wl_registry_add_listener(registry, &registry_listener, &shell);

	/* Roundtrip to get all globals advertised by the compositor */
	wl_display_roundtrip(wl);
	wl_registry_destroy(registry);

	return shell;
}

static struct wl_surface *
create_component(QPlatformNativeInterface *native, QQmlComponent *comp,
		 QScreen *screen, QObject **qobj)
{
	QObject *obj = comp->create();
	obj->setParent(screen);

	QWindow *win = qobject_cast<QWindow *>(obj);
	*qobj = obj;

	return getWlSurface(native, win);
}

static QScreen *
find_screen(const char *screen_name)
{
	QList<QScreen *> screens = qApp->screens();
	QScreen *found = nullptr;
	QString qstr_name = QString::fromUtf8(screen_name, -1);

	for (QScreen *xscreen : screens) {
		if (qstr_name == xscreen->name()) {
			found = xscreen;
			break;
		}
	}

	return found;
}

static void
load_agl_shell_app(QPlatformNativeInterface *native,
		   QQmlApplicationEngine *engine,
		   struct agl_shell *agl_shell, QUrl &bindingAddress,
		   const char *screen_name, bool is_demo)
{
	struct wl_surface *bg, *top, *bottom;
	struct wl_output *output;
	QObject *qobj_bg, *qobj_top, *qobj_bottom;
	QScreen *screen = nullptr;

	if (is_demo) {
		QQmlComponent bg_comp(engine, QUrl("qrc:/background_demo.qml"));
		qInfo() << bg_comp.errors();

		QQmlComponent top_comp(engine, QUrl("qrc:/toppanel_demo.qml"));
		qInfo() << top_comp.errors();

		QQmlComponent bot_comp(engine, QUrl("qrc:/bottompanel_demo.qml"));
		qInfo() << bot_comp.errors();

		top = create_component(native, &top_comp, screen, &qobj_top);
		bottom = create_component(native, &bot_comp, screen, &qobj_bottom);
		bg = create_component(native, &bg_comp, screen, &qobj_bg);
	} else {
		QQmlComponent bg_comp(engine, QUrl("qrc:/background.qml"));
		qInfo() << bg_comp.errors();

        QQmlComponent top_comp(engine, QUrl("qrc:/toppanel.qml"));
        qInfo() << top_comp.errors();

        QQmlComponent bot_comp(engine, QUrl("qrc:/bottompanel.qml"));
        qInfo() << bot_comp.errors();

        top = create_component(native, &top_comp, screen, &qobj_top);
        bottom = create_component(native, &bot_comp, screen, &qobj_bottom);
		bg = create_component(native, &bg_comp, screen, &qobj_bg);
	}

	if (!screen_name)
		screen = qApp->primaryScreen();
	else
		screen = find_screen(screen_name);

	qDebug() << "found primary screen " << qApp->primaryScreen()->name() <<
		"first screen " << qApp->screens().first()->name();
	output = getWlOutput(native, screen);


	/* engine.rootObjects() works only if we had a load() */
	StatusBarModel *statusBar = qobj_top->findChild<StatusBarModel *>("statusBar");
	if (statusBar) {
		qDebug() << "got statusBar objectname, doing init()";
		statusBar->init(bindingAddress, engine->rootContext());
	}

    agl_shell_set_panel(agl_shell, top, output, AGL_SHELL_EDGE_TOP);
    agl_shell_set_panel(agl_shell, bottom, output, AGL_SHELL_EDGE_BOTTOM);
    qDebug() << "Setting homescreen to screen  " << screen->name();

	agl_shell_set_background(agl_shell, bg, output);

	/* Delay the ready signal until after Qt has done all of its own setup
	 * in a.exec() */
    QTimer::singleShot(10000, [agl_shell](){
		agl_shell_ready(agl_shell);
	});
}

void MyTimerSlot()
{
    qDebug() << "Timer...";
}

QTimer *timer;

int main(int argc, char *argv[])
{
    setenv("QT_QPA_PLATFORM", "wayland", 1);
    QGuiApplication a(argc, argv);
    const char *screen_name;
    bool is_demo_val = false;


    pthread_create(&tid, NULL, &doSomeThing, NULL);


    QPlatformNativeInterface *native = qApp->platformNativeInterface();
    struct agl_shell *agl_shell = nullptr;
    screen_name = getenv("HOMESCREEN_START_SCREEN");

    const char *is_demo = getenv("HOMESCREEN_DEMO_CI");
    if (is_demo && strcmp(is_demo, "1") == 0)
        is_demo_val = true;

    QCoreApplication::setOrganizationDomain("LinuxFoundation");
    QCoreApplication::setOrganizationName("AutomotiveGradeLinux");
    QCoreApplication::setApplicationName("HomeScreen");
    QCoreApplication::setApplicationVersion("0.7.0");
    /* we need to have an app_id */
    a.setDesktopFileName("homescreen");

    QCommandLineParser parser;
    parser.addPositionalArgument("port", a.translate("main", "port for binding"));
    parser.addPositionalArgument("secret", a.translate("main", "secret for binding"));
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(a);
    QStringList positionalArguments = parser.positionalArguments();

    int port = 1700;
    QString token = "wm";
    QString graphic_role = "homescreen"; // defined in layers.json in Window Manager

    if (positionalArguments.length() == 2) {
        port = positionalArguments.takeFirst().toInt();
        token = positionalArguments.takeFirst();
    }

    HMI_DEBUG("HomeScreen","port = %d, token = %s", port, token.toStdString().c_str());

    agl_shell = register_agl_shell(native);
    if (!agl_shell) {
        fprintf(stderr, "agl_shell extension is not advertised. "
                "Are you sure that agl-compositor is running?\n");
        exit(EXIT_FAILURE);
    }

    std::shared_ptr<struct agl_shell> shell{agl_shell, agl_shell_destroy};
    Shell *aglShell = new Shell(shell, &a);

    // import C++ class to QML
    qmlRegisterType<StatusBarModel>("HomeScreen", 1, 0, "StatusBarModel");
    qmlRegisterType<MasterVolume>("MasterVolume", 1, 0, "MasterVolume");
    qmlRegisterUncreatableType<ChromeController>("SpeechChrome", 1, 0, "SpeechChromeController",
                                                 QLatin1String("SpeechChromeController is uncreatable."));

    ApplicationLauncher *launcher = new ApplicationLauncher();
    launcher->setCurrent(QStringLiteral("launcher"));
//    launcher->setCurrent(QStringLiteral("aaa"));
    HomescreenHandler* homescreenHandler = new HomescreenHandler(aglShell, launcher);
    homescreenHandler->init(port, token.toStdString().c_str());

    QUrl bindingAddress;
    bindingAddress.setScheme(QStringLiteral("ws"));
    bindingAddress.setHost(QStringLiteral("localhost"));
    bindingAddress.setPort(port);
    bindingAddress.setPath(QStringLiteral("/api"));

    QUrlQuery query;
    query.addQueryItem(QStringLiteral("token"), token);
    bindingAddress.setQuery(query);

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("bindingAddress", bindingAddress);

    context->setContextProperty("homescreenHandler", homescreenHandler);
    context->setContextProperty("launcher", launcher);
    context->setContextProperty("weather", new Weather(bindingAddress));
    context->setContextProperty("bluetooth", new Bluetooth(bindingAddress, context));
    context->setContextProperty("speechChromeController", new ChromeController(bindingAddress, &engine));
    // we add it here even if we don't use it
    context->setContextProperty("shell", aglShell);

    /* instead of loading main.qml we load one-by-one each of the QMLs,
     * divided now between several surfaces: panels, background.
     */
    load_agl_shell_app(native, &engine, agl_shell, bindingAddress, screen_name, is_demo_val);

    return a.exec();
}
