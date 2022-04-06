#include "field.h"

Field::Field(QObject *parent, QString stringField)
    : QObject{parent}
{
    initializeField(stringField);
}

Field::~Field()
{
}

Field::Field (const Field &source)
    :m_2Dvector(source.m_2Dvector)
{
}

Field& Field::operator=(const Field& source)
{
    if (this == &source) return *this;

    m_2Dvector = source.m_2Dvector;

    return *this;
}

int Field::get_row_size() const
{
  return (m_2Dvector.size());
}

int Field::get_col_size() const
{
  return (m_2Dvector[0].size());
}

bool Field::get_cell(int row, int col) const
{
  return m_2Dvector[row][col];
}

void Field::set_cell(int row, int col, bool status)
{
  m_2Dvector[row][col] = status;
}

int Field::find_alive(int row, int col) const
{
  int alive_neib = 0;
  for (int i = -1; i <= 1; i++)
  {
    for (int j = -1; j <= 1; j++)
    {
      int row_mod = (row + i + get_row_size()) % get_row_size();
      int col_mod = (col + j + get_col_size()) % get_col_size();

      if (m_2Dvector[row_mod][col_mod])
        alive_neib++;
    }
  }
  return (alive_neib - m_2Dvector[row][col]);
}


void Field::initializeField(QString& stringField)
{
    std::vector<bool> line;
    for (auto i : stringField)
    {
        if (i != '\n')
        {
            line.push_back(i.digitValue());
        }
        else
        {
            m_2Dvector.push_back(line);
            line.clear();
        }
    }
}
