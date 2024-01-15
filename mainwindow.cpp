#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(!server){
        int port = ui->spnServerPort->value();
        server = new TCPServer(port);
        connect(server, SIGNAL(newClientConnected()), this, SLOT(newClientConnected()));
    }

    auto state = (server->isStareted()) ? "1" : "0";
    ui->lblConnectionStatus->setProperty("state", state);
    style()->polish(ui->lblConnectionStatus);
}

void MainWindow::newClientConnected()
{
    ui->lstConsole->addItem("New Client connected");
}


void MainWindow::on_btnClear_clicked()
{
    ui->lstConsole->clear();
}


void MainWindow::on_btnSendAll_clicked()
{
    auto message = ui->lnMessage->text().trimmed();
    server->sendToAll(message);
}

