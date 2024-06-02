//
// Created by Kiana on 2024/5/15.
//

#include "MyTCP.h"

MyTCP::MyTCP(QObject *parent) : QObject(parent) {
    // 创建一个TCP服务器对象，并监听某个端口（例如12345）
    server = new QTcpServer(this);

    connect(server, &QTcpServer::newConnection, this, &MyTCP::onNewConnection);
    if (!server->listen(QHostAddress::Any, 7772)) {
        qDebug() << "Server could not start";
    }else {
        qDebug() << "Server could start";
    }
}

void MyTCP::onNewConnection() {
    // 每当有一个新的连接时，这个槽就会被调用
    clientSocket = server->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &MyTCP::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);

    qDebug() << "user already connect from IP" << clientSocket->peerAddress();
}

void MyTCP::onReadyRead() {
    // 当客户端发送数据时，这个槽就会被调用
    //clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (clientSocket) {
        QByteArray line = clientSocket->readAll();
        qDebug() << "Received: " << line;
        getID(line);
    }
}

void MyTCP::TCP_SEND(QString data) {
    clientSocket->write(data.toStdString().c_str());
}

int MyTCP::getID(QByteArray line) {

    QString str = line;

    QStringList parts = str.split("#");

    if(parts.isEmpty()){
        return 0;
    }else{
        if(parts.at(0) == "i")
        {
            rfid_card_id = parts.at(1);
            emit sig_get_rfid_card(rfid_card_id);
            return 1;
        }
    }
    return 0;
}

const QString &MyTCP::getRfidCardId() const {
    return rfid_card_id;
}



