#ifndef MAINKAUTO_H
#define MAINKAUTO_H

#include <QObject>
#include <QTimer>
#include <QString>
#include <QUrl>

#include "qlibhomescreen.h"
#include "websocketclient.h"


class mainkauto : public QObject
{
    Q_OBJECT
public:
    explicit mainkauto(QObject *parent = nullptr);

signals:
    void add_log_to_console(QString _msg);
public slots:

private slots:
    void addConsoleLog(QString _msg);
    void testConsole();

    void onReceivedDataWebsocket(const QString &message);
    void onWebsocketDisconnected();
    void onWebsocketConnected();
private:
    QLibHomeScreen* m_lib;
    websocketClient *m_wsclient;
    QTimer *m_timerTestConsole;


};

#endif // MAINKAUTO_H
