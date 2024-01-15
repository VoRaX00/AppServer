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
    void sendToAll(QTcpSocket* socket, QString message);
signals:
    void newClientConnected();
    void clientDisconnect();
    void dataReceived(QString message);

private slots:
    void on_client_connecting();
    void clientDisconnected();
    void clientDataReady();

private:
    QTcpServer* server;
    QList<QTcpSocket*> socketList;
    bool isStart;
};

#endif // TCPSERVER_H
