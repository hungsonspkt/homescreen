#include "mainkauto.h"

mainkauto::mainkauto(QObject *parent) : QObject(parent)
{
    m_lib = new QLibHomeScreen(this);
}
