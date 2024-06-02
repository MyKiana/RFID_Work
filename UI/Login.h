//
// Created by Kiana on 2024/5/20.
//

#ifndef RFID_WORK_LOGIN_H
#define RFID_WORK_LOGIN_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include "Registered.h"
#include "../Src/Main.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QWidget {
Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);

    ~Login() override;

    void init();

    void connect_sig();

    signals:


public slots:

    void on_pb_login();

    void on_pb_registered();

private:
    Ui::Login *ui;

    MYSQL_X msql;

    Registered re;

    Main ma;
};


#endif //RFID_WORK_LOGIN_H
