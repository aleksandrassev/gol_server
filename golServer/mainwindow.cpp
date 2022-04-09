#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    setFixedSize(300,300);

    m_ui->lineEdit_Port->setText("12345");
    m_ui->label_Name->setStyleSheet("font-weight: bold; color: black; font-size: 20px");
    m_ui->label_Info->setStyleSheet("font-weight: bold; color: red; font-size: 14px");

    m_server = new QTcpServer();
    connect(m_server, &QTcpServer::newConnection, this, &MainWindow::serverNewConnect);
}

MainWindow::~MainWindow()
{
    m_server -> close();
    m_server -> deleteLater();
    delete m_ui;
}


void MainWindow::on_pushButton_Start_clicked()
{
    if(m_ui->pushButton_Start->text() == ("Start"))
    {
        int port = m_ui->lineEdit_Port->text().toInt();
        if(!m_server->listen(QHostAddress::LocalHost, port))
        {
            m_ui->label_Info->setText(m_server->errorString());
            return;
        }
        m_ui->pushButton_Start->setText("Stop");
        m_ui->label_Info->setStyleSheet("font-weight: bold; color: blue; font-size: 14px");
        m_ui->label_Info->setText("Server started! Waiting for client...");
    }
    else
    {
        if (m_server->isListening())
        {
            m_socket->abort();
            m_server->close();
        }
        m_ui->pushButton_Start->setText("Start");
        m_ui->label_Info->setStyleSheet("font-weight: bold; color: red; font-size: 14px");
        m_ui-> label_Info->setText("Stopped!");
    }
}

void MainWindow::serverNewConnect()
{
    m_socket = m_server->nextPendingConnection();
    QObject::connect(m_socket, &QTcpSocket::readyRead, this, &MainWindow::socketReadData);

    m_ui->pushButton_Start->setEnabled(true);
    m_ui->label_Info->setStyleSheet("font-weight: bold; color: green; font-size: 14px");
    m_ui-> label_Info->setText("Client connected!");

    m_ui->label_socketIP->setStyleSheet("font-weight: bold; color: blue; font-size: 12px");
    QString peerIP = m_socket->peerAddress().toString();
    m_ui->label_socketIP->setText("IP address of the peer:" + peerIP);
}

void MainWindow::socketReadData()
{
    QByteArray buffer;
    buffer = m_socket->readAll();

    if(!buffer.isEmpty())
    {
        QString stringField = buffer;
        Cycle cycle(this, stringField);
        QString nextFieldStr = cycle.nextGeneration();

        m_socket->write(nextFieldStr.toLatin1());
        m_socket->flush();
    }
}

