#include "tcpsocket.h"

tcpSocket::tcpSocket(const QString &hostAddress, const int &port, QObject *parent) :
    QObject(parent),
    _host_address(hostAddress),
    _port_number(port)
{

    m_timerRetryConnect = new QTimer(this);
    connect(m_timerRetryConnect,SIGNAL(timeout()),this,SLOT(connectToHost()));
    m_timerRetryConnect->start(1000);

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
    m_timerRetryConnect->start(8000);
}

void tcpSocket::connectToHost()
{
    m_timerRetryConnect->stop();
    if(!m_tcpSocket.isOpen())
     {
        emit connectingToHost(_host_address, _port_number);
        m_tcpSocket.connectToHost(_host_address, _port_number);
        if (m_tcpSocket.waitForConnected(5000)){
            emit connected();
        }
        else  {
            m_tcpSocket.close();
            emit disconnected();

        }
        m_timerRetryConnect->start(8000);
     }

}
