#include "mainkauto.h"

mainkauto::mainkauto(QObject *parent) : QObject(parent)
{
    m_lib = new QLibHomeScreen(this);

    m_timerTestConsole = new QTimer(this);
    connect(m_timerTestConsole,SIGNAL(timeout()),this,SLOT(testConsole()));
    m_timerTestConsole->start(1000);
}

void mainkauto::addConsoleLog(QString _msg)
{
    emit add_log_to_console(_msg);
}

void mainkauto::testConsole()
{
    addConsoleLog("Test console: Hello K-Auto!!");
}
