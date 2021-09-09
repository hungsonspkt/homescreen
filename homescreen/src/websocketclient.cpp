#include "websocketclient.h"

websocketClient::websocketClient(const QUrl &wsUrl, QObject *parent) :
    QObject(parent),
    m_url(wsUrl)
{
    connect(&m_webSocket, &QWebSocket::connected, this, &websocketClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &websocketClient::onClosed);
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &websocketClient::onTextMessageReceived);
}

void websocketClient::sendTextMessage(QString message)
{
    qint64 sent = m_webSocket.sendTextMessage(message);
}

void websocketClient::startWs()
{
    qDebug() << "ws url " << m_url;
    m_webSocket.open(m_url);
}

void websocketClient::stopWs()
{

}

void websocketClient::onError(QAbstractSocket::SocketError error)
{
    qDebug() << "WSError: " << QString(error);

}

void websocketClient::onConnected()
{
    emit connected();
}

void websocketClient::onTextMessageReceived(QString message)
{
    emit textMessageReceived(message);
}

void websocketClient::onClosed()
{
    emit closed();
}

void websocketClient::onReConnect()
{

}
