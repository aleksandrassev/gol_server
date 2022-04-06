#ifndef FIELD_H
#define FIELD_H

#include <QObject>

#include <iostream>

class Field : public QObject
{
    Q_OBJECT
public:
    Field (QObject *parent = nullptr, QString fieldString = "");
     ~Field() override;
    Field (const Field &source);
    Field& operator=(const Field& source);

    int get_row_size() const;
    int get_col_size() const;
    bool get_cell(int row, int col) const;
    void set_cell(int row, int col, bool status);

    int find_alive(int row, int col) const;

private:
    std::vector<std::vector<bool>> m_2Dvector;
    void initializeField(QString& stringField);
};

#endif // FIELD_H
