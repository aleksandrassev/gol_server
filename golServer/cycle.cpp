#include "cycle.h"

Cycle::Cycle(QObject *parent, QString fieldString)
    : QObject{parent}, m_field(Field (this, fieldString))
{
}

Cycle::~Cycle()
{
}


QString Cycle::nextGeneration()
{
    m_currentField = m_field;

    for (int j = 0; j < m_currentField.getRowSize(); j++)
    {
        for (int l = 0; l < m_currentField.getColSize(); l++)
        {
            int alive_neib = m_currentField.findAlive(j, l);

            /* 1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
               2. Any live cell with two or three live neighbours lives on to the next generation.
               3. Any live cell with more than three live neighbours dies, as if by overpopulation */
            if (alive_neib < 2 || alive_neib > 3) m_field.setCell(j, l, false);

            /* 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction */
            if (alive_neib == 3) m_field.setCell(j, l, true);
        }
    }
    return (fieldToString(m_field));
}


QString Cycle::fieldToString(Field& field)
{
    QString stringField;

    int row_size = field.getRowSize();
    int col_size = field.getColSize();

    for (int i = 0; i < row_size; i++)
    {
        for (int j = 0; j < col_size; j++)
        {
            stringField += QString::number(field.getCell(i, j));
        }
        stringField += "\n";
    }
    return stringField;
}
