#include "mainkauto.h"

mainkauto::mainkauto(QObject *parent) : QObject(parent)
{
    m_lib = new QLibHomeScreen(this);



//    QUrl bindingAddress;
//    bindingAddress.setScheme(QStringLiteral("ws"));
//    bindingAddress.setHost(QStringLiteral("localhost"));
//    bindingAddress.setPort(1700);
//    bindingAddress.setPath(QStringLiteral("/api"));

//    m_wsclient =  new websocketClient(bindingAddress);
//    QObject::connect(m_wsclient, SIGNAL(textMessageReceived(QString)), this, SLOT(onReceivedDataWebsocket(const QString&)));
//    QObject::connect(m_wsclient, &websocketClient::connected, this, &mainkauto::onWebsocketConnected);
//    QObject::connect(m_wsclient, &websocketClient::closed, this, &mainkauto::onWebsocketDisconnected);
//    m_wsclient->startWs();
//    addConsoleLog("start ws: "+ bindingAddress.toString());

    m_tcpSocket = new tcpSocket("192.168.0.104",5000);
    QObject::connect(m_tcpSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(onReceivedDataTcpSocket(const QString&)));
    QObject::connect(m_tcpSocket, &tcpSocket::connected, this, &mainkauto::onTcpSocketConnected);
    QObject::connect(m_tcpSocket, &tcpSocket::disconnected, this, &mainkauto::onTcpSocketDisconnected);
    QObject::connect(m_tcpSocket, SIGNAL(connectingToHost(QString,int)), this, SLOT(onConnectingTcpSocket(QString,int)));

}

void mainkauto::addConsoleLog(QString _msg)
{
    emit add_log_to_console(_msg);
}

void mainkauto::testConsole()
{
    addConsoleLog("Test console: Hello K-Auto!!");
}

void mainkauto::onReceivedDataTcpSocket(const QString &message)
{
    addConsoleLog("Tcp socket data received: " + message);
}

void mainkauto::onTcpSocketDisconnected()
{
    addConsoleLog("Tcp socket disconnected");
}

void mainkauto::onTcpSocketConnected()
{
    addConsoleLog("Tcp socket connected");
}

void mainkauto::onConnectingTcpSocket(QString _host, int _port)
{
    addConsoleLog("connecting to Tcp socket: host " + _host + " - port " + QString::number(_port));

}
