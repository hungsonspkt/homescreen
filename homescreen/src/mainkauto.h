#ifndef MAINKAUTO_H
#define MAINKAUTO_H

#include <QObject>
#include <QTimer>
#include <QString>
#include <QUrl>

#include "qlibhomescreen.h"
#include "websocketclient.h"
#include "tcpsocket.h"


class mainkauto : public QObject
{
    Q_OBJECT
public:
    explicit mainkauto(QObject *parent = nullptr);

signals:
    void add_log_to_console(QString _msg);
    void update_data_parameter(long long _odo, int _currentSpeed, int _battery, int _leftSignal, int _rightSignal);

public slots:

private slots:
    void addConsoleLog(QString _msg);
    void testConsole();

    void onReceivedDataTcpSocket(const QString &message);
    void onTcpSocketDisconnected();
    void onTcpSocketConnected();
    void onConnectingTcpSocket(QString _host, int _port);

private:
    QLibHomeScreen* m_lib;
    websocketClient *m_wsclient;
    tcpSocket       *m_tcpSocket;

    QTimer *m_timerRunonStartup;


};

#endif // MAINKAUTO_H
