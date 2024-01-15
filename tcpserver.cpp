#include "tcpserver.h"

TCPServer::TCPServer(int port, QObject *parent)
    : QObject{parent}
{
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(on_client_connecting()));
    isStart = server->listen(QHostAddress::Any, port);
    if(!isStart){
        qDebug() << "Server could not start";
    }
    else{
        qDebug() << "Server started";
    }
}

bool TCPServer::isStareted() const
{
    return isStart;
}

void TCPServer::sendToAll(QString message)
{
    foreach (auto socket, socketList) {
        socket->write(message.toUtf8());
    }
}

void TCPServer::on_client_connecting()
{
    qDebug() << "a client connected to server";
    auto socket = server->nextPendingConnection();
    socketList.append(socket);
    socket->write("Welcom to this Server");
    emit newClientConnected();
}
