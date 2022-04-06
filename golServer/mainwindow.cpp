#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    setFixedSize(300,200);

    m_ui->lineEdit_Port->setText("12345");
    m_ui->label_Name->setStyleSheet("font-weight: bold; color: black; font-size: 20px");
}

MainWindow::~MainWindow()
{
    delete m_ui;
}


void MainWindow::on_pushButton_Start_clicked()
{

}


void MainWindow::on_pushButton_Stop_clicked()
{

}

