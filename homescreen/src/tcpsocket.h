#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QtNetwork/QtNetwork>
#include <QtCore>
#include <QTcpSocket>
#include <QString>
#include <QDebug>
#include <QTimer>

class tcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit tcpSocket(const QString &hostAddress, const int &port, QObject *parent = nullptr);

signals:
    void connected();
    void textMessageReceived(QString message);
    void disconnected();
    void connectingToHost(QString _host, int _port);

private slots:
    void getMessageReceived();
    void onClosed();
    void connectToHost();


private:
    QTimer *m_timerRunonStartup;

    QTcpSocket m_tcpSocket;
    QString _host_address;
    int _port_number;


};

#endif // TCPSOCKET_H
