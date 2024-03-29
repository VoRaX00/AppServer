#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpserver.h"

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
    void on_pushButton_clicked();
    void on_btnClear_clicked();
    void on_btnSendAll_clicked();

    void newClientConnected();
    void clientDisconnected();
    void clientDataReceived(QString message);


private:
    Ui::MainWindow *ui;
    TCPServer* server;
};
#endif // MAINWINDOW_H
