#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

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
    void serverNewConnect();
    void socketReadData();
    void on_pushButton_Start_clicked();
    void improvisedKeepAliveSocketCheck();

private:
    Ui::MainWindow *m_ui;
    QTcpServer* m_server;
    QTcpSocket* m_clientSocket;
    QTimer *m_timer;

    int m_socketWriteStatus;

};
#endif // MAINWINDOW_H
