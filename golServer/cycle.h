#ifndef CYCLE_H
#define CYCLE_H

#include <QObject>

class Cycle : public QObject
{
    Q_OBJECT
public:
    explicit Cycle(QObject *parent = nullptr);

signals:

};

#endif // CYCLE_H
