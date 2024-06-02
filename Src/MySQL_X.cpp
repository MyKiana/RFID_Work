//
// Created by Kiana on 2024/5/16.
//

#include "MySQL_X.h"

MYSQL_X::MYSQL_X(QObject *parent) : QObject(parent) {
    qDebug() << QSqlDatabase::drivers();
    QSqlDatabase::removeDatabase(QSqlDatabase::database().connectionName());
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("rfid_work");
    db.setUserName("root");
    db.setPassword("123456");
    if(db.open()){
        qDebug() << "yes";
    }
}

int MYSQL_X::insert_from_id(QString id, QString name) {
    db.open();
    update_id();
    QSqlQuery query;
    bool result = query.exec("INSERT INTO rfid_table (rfid_id, name) VALUES ('"+id+"', '"+name+"');");

    if(result){
        qDebug()<<"insert ok";
        return 1;
    }else {
        qDebug() << "insert error";
        return 0;
    }
    db.close();
}
int MYSQL_X::insert_from_qq(QString id, QString name) {
    db.open();
    update_qq();
    QSqlQuery query;
    bool result = query.exec("INSERT INTO user (qq, passwd) VALUES ('"+id+"', '"+name+"');");

    if(result){
        qDebug()<<"insert ok";
        return 1;
    }else {
        qDebug() << "insert error";
        return 0;
    }
    db.close();
}


int MYSQL_X::update_id() {
    QSqlQuery query;
    QString sql = "ALTER TABLE rfid_table AUTO_INCREMENT = 1;";

    if (!query.exec(sql)) {
        // 如果有错误发生
        qDebug() << "Error executing query:";
        return 0;
    } else {
        qDebug() << "AUTO_INCREMENT reset successfully";
        return 1;
    }
}

int MYSQL_X::update_qq() {
    QSqlQuery query;
    QString sql = "ALTER TABLE user AUTO_INCREMENT = 1;";

    if (!query.exec(sql)) {
        // 如果有错误发生
        qDebug() << "Error executing query:";
        return 0;
    } else {
        qDebug() << "AUTO_INCREMENT reset successfully";
        return 1;
    }
}

int MYSQL_X::is_save_id(QString text) {
    db.open();
    QSqlQuery query;
    query.prepare("SELECT EXISTS (SELECT 1 FROM rfid_table WHERE rfid_id = :rfidId)");
    query.bindValue(":rfidId", text);
    if (query.exec()) {
        if (query.next()) {
            bool exists = query.value(0).toBool();
            qDebug() << "RFID ID exists:" << exists;
            if(exists)
                return 1;
        }
    }
    return 0;
}

QString MYSQL_X::select_from_rfid_id(QString str) {
    QSqlQuery query;
    QString sql = "SELECT name FROM rfid_table WHERE rfid_id = :rfidId";
    query.prepare(sql);
    query.bindValue(":rfidId", str);

    // 执行查询
    if (query.exec()) {
        // 检查是否有结果
        if (query.next()) {
            // 读取结果
            QString name = query.value(0).toString();
            qDebug() << "Found name:" << name;
            return name;
        } else {
            qDebug() << "No record found for rfid_id:" << str;
        }
    }
    return "";
}

bool MYSQL_X::login_from_qq(QString qq, QString passwd) {
    db.open();
    // 查询qq是否存在
    QSqlQuery query(db);
    query.prepare("SELECT passwd FROM user WHERE qq = :qq");
    query.bindValue(":qq", qq);

    if (!query.exec()) {
        // 处理查询失败的情况
        qWarning() << "Query failed:" << query.lastError().text();
        return false;
    }

    // 检查查询结果
    if (!query.next()) {
        // 没有找到对应的qq
        return false;
    }

    // 获取查询到的密码（假设是明文存储，如果是加密存储则需要解密）
    QString storedPasswd = query.value(0).toString();

    // 比对密码
    if (passwd != storedPasswd) {
        // 密码不匹配
        return false;
    }

    // 密码匹配
    return true;
}

int MYSQL_X::insert_class_num(QString class_num) {
    db.open();
    update_qq();
    QSqlQuery query;
    bool result = query.exec("INSERT INTO class (classnum) VALUES ('" + class_num + "');");

    if(result){
        qDebug()<<"insert ok";
        return 1;
    }else {
        qDebug() << "insert error";
        return 0;
    }
    db.close();
}
