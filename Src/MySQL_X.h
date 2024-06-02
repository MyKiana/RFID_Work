//
// Created by Kiana on 2024/5/16.
//

#ifndef RFID_WORK_MYSQL_X_H
#define RFID_WORK_MYSQL_X_H

#include <QDebug>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>

class MYSQL_X : public QObject {
    Q_OBJECT
public:
    MYSQL_X(QObject *parent = nullptr);

    int insert_from_qq(QString id,QString name);

    int insert_from_id(QString id,QString name);

    int update_from_id(QString id,QString name);

    int is_save_id(QString text);

    QString select_from_rfid_id(QString str);

    int update_id();

    int update_qq();

    bool login_from_qq(QString qq,QString passwd);

    int insert_class_num(QString class_num);

public slots:


private:
    QSqlDatabase db;
};
#endif //RFID_WORK_MYSQL_X_H
