#include "tcpsocket.h"

tcpSocket::tcpSocket(const QString &hostAddress, const int &port, QObject *parent) :
    QObject(parent),
    _host_address(hostAddress),
    _port_number(port)
{

    m_timerRunonStartup = new QTimer(this);
    connect(m_timerRunonStartup,SIGNAL(timeout()),this,SLOT(connectToHost()));
    m_timerRunonStartup->setSingleShot(true);
    m_timerRunonStartup->start(1000);

    connect(&m_tcpSocket,SIGNAL(readyRead()),this,SLOT(getMessageReceived()));
    connect(&m_tcpSocket,SIGNAL(disconnected()),this,SLOT(onClosed()));

}

void tcpSocket::getMessageReceived()
{
    QByteArray data_received = m_tcpSocket.readAll();
    m_tcpSocket.flush();
    emit textMessageReceived(QString::fromUtf8(data_received.data()));
}

void tcpSocket::onClosed()
{
    emit disconnected();
}

void tcpSocket::connectToHost()
{
    if(m_tcpSocket.isOpen())
     {
         m_tcpSocket.close();
         emit disconnected();
     }
     else{
         m_tcpSocket.connectToHost(_host_address, _port_number);
         emit connectingToHost(_host_address, _port_number);
         if (m_tcpSocket.waitForConnected(5000)){
             emit connected();
         }
         else  {
             emit disconnected();

         }
     }
}
