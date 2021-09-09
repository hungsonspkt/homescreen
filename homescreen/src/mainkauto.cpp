#include "mainkauto.h"

mainkauto::mainkauto(QObject *parent) : QObject(parent)
{
    m_lib = new QLibHomeScreen(this);

    m_timerTestConsole = new QTimer(this);
    connect(m_timerTestConsole,SIGNAL(timeout()),this,SLOT(testConsole()));
//    m_timerTestConsole->start(1000);

    QUrl bindingAddress;
    bindingAddress.setScheme(QStringLiteral("ws"));
    bindingAddress.setHost(QStringLiteral("localhost"));
    bindingAddress.setPort(1700);
    bindingAddress.setPath(QStringLiteral("/api"));

    m_wsclient =  new websocketClient(bindingAddress);
    QObject::connect(m_wsclient, SIGNAL(textMessageReceived(QString)), this, SLOT(onReceivedDataWebsocket(const QString&)));
    QObject::connect(m_wsclient, &websocketClient::connected, this, &mainkauto::onWebsocketConnected);
    QObject::connect(m_wsclient, &websocketClient::closed, this, &mainkauto::onWebsocketDisconnected);
    m_wsclient->startWs();
    addConsoleLog("start ws: "+ bindingAddress.toString());

}

void mainkauto::addConsoleLog(QString _msg)
{
    emit add_log_to_console(_msg);
}

void mainkauto::testConsole()
{
    addConsoleLog("Test console: Hello K-Auto!!");
}

void mainkauto::onReceivedDataWebsocket(const QString &message)
{
    addConsoleLog("Data WS Received: " + message);
}

void mainkauto::onWebsocketDisconnected()
{
    addConsoleLog("WS disconnected");
}

void mainkauto::onWebsocketConnected()
{
    addConsoleLog("WS connected");
}
