/*
 * Copyright (c) 2017 TOYOTA MOTOR CORPORATION
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

#include "qlibhomescreen.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "hmi-debug.h"
using namespace std;

#define _POPUPREPLY "on_screen_reply"
#define _REQ_POPUP_MESSAGE "on_screen_message"
#define _TAPSHORTCUT "tap_shortcut"
#define _KEY_DATA "data"
#define _KEY_APPLICATION_DATA "application_id"
#define _KEY_REPLY_MESSAGE "reply_message"
#define _KEY_REQUEST_MESSAGE "display_message"

static QLibHomeScreen* myThis;

// Note: qlibhomescreen will be integrated to libqtappfw
/**
 * QLibHomeScreen construction function
 *
 * #### Parameters
 * - parent [in] : object parent.
 *
 * #### Return
 * - None
 *
 */
QLibHomeScreen::QLibHomeScreen(QObject *parent) :
    QObject(parent),
    mp_hs(NULL)
{
    HMI_DEBUG("qlibhomescreen", "called.");
}

/**
 * QLibHomeScreen destruction function
 *
 * #### Parameters
 * - None
 *
 * #### Return
 * - None
 *
 */
QLibHomeScreen::~QLibHomeScreen()
{
    HMI_DEBUG("qlibhomescreen", "called.");
    if (mp_hs != NULL) {
        delete mp_hs;
    }
}

/**
 * init function
 *
 * call libhomescreen init function to connect to binder by websocket
 *
 * #### Parameters
 * - prot  : port from application
 * - token : token from application
 *
 * #### Return
 * - None
 *
 */
void QLibHomeScreen::init(int port, const QString &token)
{
    HMI_DEBUG("qlibhomescreen", "called.");
    string ctoken = token.toStdString();
    mp_hs = new LibHomeScreen();
    mp_hs->init(port, ctoken.c_str());

    myThis = this;
}


/**
 * call on screen message
 *
 * use libhomescreen api to call onscreen message
 *
 * #### Parameters
 * - message : message contents
 *
 * #### Return
 * - Returns 0 on success or -1 in case of error.
 *
 */
int QLibHomeScreen::onScreenMessage(const QString &message)
{
    HMI_DEBUG("qlibhomescreen", "called.");
    string str = message.toStdString();
    return mp_hs->onScreenMessage(str.c_str());
}

/**
 * subscribe event
 *
 * use libhomescreen api to subscribe homescreen event
 *
 * #### Parameters
 * - evetNave : homescreen event name
 *
 * #### Return
 * - Returns 0 on success or -1 in case of error.
 *
 */
int QLibHomeScreen::subscribe(const QString &evetName)
{
    HMI_DEBUG("qlibhomescreen", "called.");
    string str = evetName.toStdString();
    return mp_hs->subscribe(str);
}

/**
 * unsubscribe event
 *
 * use libhomescreen api to unsubscribe homescreen event
 *
 * #### Parameters
 * - evetNave : homescreen event name
 *
 * #### Return
 * - Returns 0 on success or -1 in case of error.
 *
 */
int QLibHomeScreen::unsubscribe(const QString &evetName)
{
    HMI_DEBUG("qlibhomescreen", "called.");
    string str = evetName.toStdString();
    return mp_hs->unsubscribe(str);
}

/**
 * set homescreen event handler function
 *
 * #### Parameters
 * - et : homescreen event name
 * - f  : event handler function
 *
 * #### Return
 * - None.
 *
 */
void QLibHomeScreen::set_event_handler(enum QEventType et, handler_fun f)
{
    HMI_DEBUG("qlibhomescreen", "called.");
    LibHomeScreen::EventType hs_et = (LibHomeScreen::EventType)et;
    return this->mp_hs->set_event_handler(hs_et, std::move(f));
}

/**
 * tapShortcut function
 *
 * #### Parameters
 * - application_id : tapped application id
  *
 * #### Return
 * - None.
 *
 */
void QLibHomeScreen::tapShortcut(QString application_id)
{
    HMI_DEBUG("qlibhomescreen","tapShortcut %s", application_id.toStdString().c_str());
    mp_hs->showWindow(application_id.toStdString().c_str(), nullptr);
}

/**
 * show application by application id and display area
 *
 * #### Parameters
 * - application_id  : application id
 * - area  : display area liked {"area":"normal"}
 *
 * #### Return
 * - None.
 *
 */
void QLibHomeScreen::showWindow(QString application_id, json_object* area)
{
    mp_hs->showWindow(application_id.toStdString().c_str(), area);
}

/**
 * show application by application id and display area
 *
 * #### Parameters
 * - application_id  : application id
 * - area  : display area liked "normal"
 *
 * #### Return
 * - None.
 *
 */
void QLibHomeScreen::showWindow(QString application_id, QString area)
{
    if(area.isNull()) {
        mp_hs->showWindow(application_id.toStdString().c_str(), nullptr);
    } else {
        struct json_object *j_obj = json_object_new_object();
        struct json_object *value = json_object_new_string(area.toStdString().c_str());
        json_object_object_add(j_obj, "area", value);
        mp_hs->showWindow(application_id.toStdString().c_str(), j_obj);
    }
}

/**
 * hide application by application id
 *
 * #### Parameters
 * - application_id  : application id
 *
 * #### Return
 * - None.
 *
 */
void QLibHomeScreen::hideWindow(QString application_id)
{
    mp_hs->hideWindow(application_id.toStdString().c_str());
}

/**
 * send onscreen reply to application
 *
 * #### Parameters
 * - application_id  : application id
 * - reply  : the reply contents
 *
 * #### Return
 * - None.
 *
 */
void QLibHomeScreen::replyShowWindow(QString application_id, json_object* reply)
{
    mp_hs->replyShowWindow(application_id.toStdString().c_str(), reply);
}

/**
 * send onscreen reply to application
 *
 * #### Parameters
 * - application_id  : application id
 * - reply  : the reply contents which can convert to json
 *
 * #### Return
 * - None.
 *
 */
void QLibHomeScreen::replyShowWindow(QString application_id, QString reply)
{
    if(reply.isNull())
        mp_hs->replyShowWindow(application_id.toStdString().c_str(), nullptr);
    else
        mp_hs->replyShowWindow(application_id.toStdString().c_str(), json_tokener_parse(reply.toStdString().c_str()));
}

/**
 * show information
 *
 * push information to HomeScreen
 *
 * #### Parameters
 * - info : information that want to show
 *
 * #### Return
 * - None.
 *
 */
void QLibHomeScreen::showInformation(QString info)
{
	struct json_object* j_obj = json_object_new_object();
	struct json_object* val = json_object_new_string(info.toStdString().c_str());
	json_object_object_add(j_obj, "info", val);

    mp_hs->showInformation(j_obj);
}

/**
 * show notification
 *
 * push notification to HomeScreen
 *
 * #### Parameters
 * - icon : provided icon
 * - text : text that want to show
 *
 * #### Resturn
 * - None.
 *
 */
void QLibHomeScreen::showNotification(QString icon, QString text)
{
	struct json_object* j_obj = json_object_new_object();
	struct json_object* val_icon = json_object_new_string(icon.toStdString().c_str());
	struct json_object* val_text = json_object_new_string(text.toStdString().c_str());
	json_object_object_add(j_obj, "icon", val_icon);
	json_object_object_add(j_obj, "text", val_text);

    mp_hs->showNotification(j_obj);
}
