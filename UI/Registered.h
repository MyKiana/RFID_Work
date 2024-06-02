//
// Created by Kiana on 2024/5/20.
//

#ifndef RFID_WORK_REGISTERED_H
#define RFID_WORK_REGISTERED_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include "../Src/MySQL_X.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Registered; }
QT_END_NAMESPACE

class Registered : public QWidget {
Q_OBJECT

public:
    explicit Registered(QWidget *parent = nullptr);

    ~Registered() override;
public slots:
    void on_pb_registered();

private:
    Ui::Registered *ui;

    MYSQL_X mysql;

};


#endif //RFID_WORK_REGISTERED_H
