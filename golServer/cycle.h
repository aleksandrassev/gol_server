#ifndef CYCLE_H
#define CYCLE_H

#include <QObject>
#include <vector>
#include <QDebug>

#include "field.h"

class Cycle : public QObject
{
    Q_OBJECT
public:
    Cycle(QObject *parent = nullptr, QString fieldString = "");
    ~Cycle() override;

    QString next_generation();

private:
    Field m_field;
    Field m_currentField;

    QString fieldToString(Field& field);


};

#endif // CYCLE_H
