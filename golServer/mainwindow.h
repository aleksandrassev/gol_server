#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

#include "cycle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void server_New_Connect();
    void socket_Read_Data();
    void on_pushButton_Start_clicked();

private:
    Ui::MainWindow *m_ui;
    QTcpServer* m_server;
    QTcpSocket* m_socket;
};
#endif // MAINWINDOW_H
