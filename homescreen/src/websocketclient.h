#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QtWebSockets/QWebSocket>
#include <QThread>


class websocketClient : public QObject
{
    Q_OBJECT
public:
    explicit websocketClient(const QUrl &wsUrl, QObject *parent = nullptr);

    void sendTextMessage(QString message);
    void startWs();
    void stopWs();

signals:
    void connected();
    void textMessageReceived(QString message);
    void closed();
    void reconnect();

public slots:
    void onError(QAbstractSocket::SocketError error);
    void onConnected();
    void onTextMessageReceived(QString message);
    void onClosed();
    void onReConnect();

private:
    QWebSocket m_webSocket;
    QUrl m_url;


};

#endif // WEBSOCKETCLIENT_H
