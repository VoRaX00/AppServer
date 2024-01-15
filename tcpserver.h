#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class TCPServer : public QObject
{
    Q_OBJECT
public:
    explicit TCPServer(int port, QObject *parent = nullptr);
    bool isStareted() const;
    void sendToAll(QString message);
signals:
    void newClientConnected();

private slots:
    void on_client_connecting();

private:
    QTcpServer* server;
    QList<QTcpSocket*> socketList;
    bool isStart;
};

#endif // TCPSERVER_H
