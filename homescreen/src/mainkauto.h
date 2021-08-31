#ifndef MAINKAUTO_H
#define MAINKAUTO_H

#include <QObject>
#include <QTimer>
#include <QString>

#include "qlibhomescreen.h"


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

private:
    QLibHomeScreen* m_lib;
    QTimer *m_timerTestConsole;


};

#endif // MAINKAUTO_H
