//
// Created by Kiana on 2024/5/15.
//

#ifndef RFID_WORK_MYTCP_H
#define RFID_WORK_MYTCP_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QDebug>
#include <QStringList>
class MyTCP : public QObject
{
Q_OBJECT
public:
    MyTCP(QObject *parent = nullptr);

    void TCP_SEND(QString data);

    const QString &getRfidCardId() const;

    signals:

    void sig_get_rfid_card(QString str);

public slots:
    void onNewConnection();

    void onReadyRead();



private:

    int getID(QByteArray line);

    QTcpServer *server;

    QTcpSocket *clientSocket;

    QString rfid_card_id;
};

#endif //RFID_WORK_MYTCP_H
