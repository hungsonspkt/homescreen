#ifndef MAINKAUTO_H
#define MAINKAUTO_H

#include <QObject>
#include "qlibhomescreen.h"

class mainkauto : public QObject
{
    Q_OBJECT
public:
    explicit mainkauto(QObject *parent = nullptr);

signals:

public slots:

private slots:

private:
    QLibHomeScreen* m_lib;
};

#endif // MAINKAUTO_H
