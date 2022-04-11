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

    m_timer =new QTimer(this);

    m_server = new QTcpServer();
    connect(m_server, &QTcpServer::newConnection, this, &MainWindow::serverNewConnect);
}

MainWindow::~MainWindow()
{
    m_server -> close();
    m_server -> deleteLater();
    delete m_timer;
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
            m_clientSocket->abort();
            m_server->close();
        }
        m_ui->pushButton_Start->setText("Start");
        m_ui->label_Info->setStyleSheet("font-weight: bold; color: red; font-size: 14px");
        m_ui-> label_Info->setText("Stopped!");
    }
}

void MainWindow::serverNewConnect()
{
    m_clientSocket = m_server->nextPendingConnection();
    QObject::connect(m_clientSocket, &QTcpSocket::readyRead, this, &MainWindow::socketReadData);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(improvisedKeepAliveSocketCheck()));
    m_timer->start(3000);

    QString peerIP = m_clientSocket->peerAddress().toString();

    m_ui->pushButton_Start->setEnabled(true);
    m_ui->label_Info->setStyleSheet("font-weight: bold; color: green; font-size: 14px");
    m_ui-> label_Info->setText("Client connected! IP address: " + peerIP);

}

void MainWindow::socketReadData()
{
    QByteArray buffer;
    buffer = m_clientSocket->readAll();

    if(!buffer.isEmpty())
    {
        QString stringField = buffer;
        Cycle cycle(this, stringField);
        QString nextFieldStr = cycle.nextGeneration();

        m_clientSocket->write(nextFieldStr.toLatin1());
        m_clientSocket->flush();
    }
}


void MainWindow::improvisedKeepAliveSocketCheck()
{
    if (m_clientSocket->state() == QAbstractSocket::UnconnectedState)
    {
        m_ui->label_Info->setStyleSheet("font-weight: bold; color: red; font-size: 14px");
        m_ui->label_Info->setText("Client disconnected! Waiting for client...");
    }
}



