//
// Created by Kiana on 2024/5/15.
//

#ifndef RFID_WORK_MAIN_H
#define RFID_WORK_MAIN_H

#include <QWidget>
#include <QTimer>
#include <QMessageBox>
#include "MyTCP.h"
#include "MySQL_X.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Main; }
QT_END_NAMESPACE

class Main : public QWidget {
Q_OBJECT

public:
    explicit Main(QWidget *parent = nullptr);

    ~Main() override;
    void from_rfid_open(QString str);

public slots:
    void on_init_RFID();

    void on_open_lock();

    void set_now_rfid_card_txt(QString txt);

    void onTimeout();

    void on_class_num_clicked();

private:
    Ui::Main *ui;

    MYSQL_X *mysql;

    MyTCP *tcp;

    QTimer *close_lock;

    int Error_count;
};


#endif //RFID_WORK_MAIN_H
