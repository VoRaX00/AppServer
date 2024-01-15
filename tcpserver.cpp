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

void TCPServer::sendToAll(QTcpSocket *socket, QString message)
{
    foreach (auto _socket, socketList) {
        if(socket != _socket)
            _socket->write(message.toUtf8());
    }
}

void TCPServer::on_client_connecting()
{
    qDebug() << "a client connected to server";
    auto socket = server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(clientDataReady()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    socketList.append(socket);
    socket->write("Welcom to this Server");
    emit newClientConnected();
}

void TCPServer::clientDisconnected()
{
    emit clientDisconnect();
}

void TCPServer::clientDataReady()
{
    auto socket = qobject_cast<QTcpSocket*>(sender());
    auto data = socket->readAll();
    emit dataReceived(QString(data));
    sendToAll(socket, QString(data));
}
