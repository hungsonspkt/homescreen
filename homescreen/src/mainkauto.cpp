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

    m_tcpSocket = new tcpSocket("127.192.90.189",5000);
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
    addConsoleLog("data received: " + message);

//    {"odo":12500, "curSpeed":30, "batteryLev":60, signalLightLeft:0, signalLightRight:1}
//    signalLight: 0=>left, 1=>right

    QJsonDocument  car_jsd = QJsonDocument::fromJson( message.toUtf8());
    QJsonObject    car_jsodt = car_jsd.object();

    emit update_data_parameter(car_jsodt["odo"].toVariant().toLongLong(), car_jsodt["curSpeed"].toInt(),
            car_jsodt["batteryLev"].toInt(), car_jsodt["signalLightLeft"].toInt(), car_jsodt["signalLightRight"].toInt());


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
