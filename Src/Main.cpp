//
// Created by Kiana on 2024/5/15.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Main.h" resolved

#include "Main.h"
#include "ui_Main.h"

Main::Main(QWidget *parent) :
        QWidget(parent), ui(new Ui::Main) {
    ui->setupUi(this);

    tcp = new MyTCP();
    mysql = new MYSQL_X();
    close_lock = new QTimer(this);

    Error_count = 0;

    connect(ui->init_rfid,&QPushButton::clicked,this,&Main::on_init_RFID);
    connect(ui->open_lock,&QPushButton::clicked,this,&Main::on_open_lock);
    connect(tcp, SIGNAL(sig_get_rfid_card(QString)),this, SLOT(set_now_rfid_card_txt(QString)));
    connect(close_lock, &QTimer::timeout, this, &Main::onTimeout);
    connect(ui->class_re,&QPushButton::clicked,this,&Main::on_class_num_clicked);

    this->setStyleSheet("QWidget { background-color: rgb(180,180,180); }");
    ui->widget->setStyleSheet("QWidget { background-color: rgb(235,235,235); }");
    ui->widget_2->setStyleSheet("QWidget { background-color: rgb(235,235,235); }");

    ui->passwd->setStyleSheet("QWidget { background-color: rgb(255,255,255); }");
    ui->ident->setStyleSheet("QWidget { background-color: rgb(255,255,255); }");
    ui->open_lock->setStyleSheet("QWidget { background-color: rgb(255,255,255); }");
    ui->init_rfid->setStyleSheet("QWidget { background-color: rgb(255,255,255); }");
    ui->class_num->setStyleSheet("QWidget { background-color: rgb(255,255,255); }");
    ui->class_re->setStyleSheet("QWidget { background-color: rgb(255,255,255); }");

}

Main::~Main() {
    delete ui;
}

void Main::on_init_RFID() {
    if(ui->init_rfid->text() != ""){
        tcp->TCP_SEND("@"+ui->ident->text()+"*");
        qDebug() << "init RFID finish";
        mysql->insert_from_id(tcp->getRfidCardId(),ui->ident->text());
    }

}

void Main::on_open_lock() {
    QString passwd = ui->passwd->text();
    if(passwd != "" || passwd.length() != 6){
        if(passwd == "123456")
        {
            tcp->TCP_SEND("@o*");
            qDebug() << "open lock";
            QTimer::singleShot(5000, this, SLOT(onTimeout()));
        }
        if(Error_count < 4){
            Error_count++;
        }else{
            tcp->TCP_SEND("@e*");
            Error_count = 0;
        }
        return;
    }
}

void Main::set_now_rfid_card_txt(QString txt) {
    ui->id_card->setText(txt);
    ui->id_card_ident->setText(mysql->select_from_rfid_id(txt));
    from_rfid_open(txt);
}

void Main::onTimeout() {
    qDebug() << "Auto close lock";
    tcp->TCP_SEND("@c*");
}

void Main::from_rfid_open(QString str) {
    if(mysql->is_save_id(str)){
        QTimer::singleShot(5000, this, SLOT(onTimeout()));
        tcp->TCP_SEND("@o*");
    }else{
        if(Error_count < 4){
            Error_count++;

        }else{
            tcp->TCP_SEND("@e*");
            Error_count = 0;
        }
    }
}

void Main::on_class_num_clicked() {
    QString class_num = ui->class_num->text();
    if(class_num != ""){
        int ret = mysql->insert_class_num(class_num);
        if(ret){
            QMessageBox::information(this,"insert","insert ok!!!");
        }else{
            QMessageBox::information(this,"insert","insert error!!!");
        }
    }
}
