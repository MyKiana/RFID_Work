//
// Created by Kiana on 2024/5/20.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Login.h" resolved

#include "Login.h"
#include "ui_Login.h"


Login::Login(QWidget *parent) :
        QWidget(parent), ui(new Ui::Login) {
    ui->setupUi(this);
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);
    init();
    connect_sig();
}

Login::~Login() {
    delete ui;
}

void Login::connect_sig() {
    connect(ui->ps_registered,&QPushButton::clicked,this,&Login::on_pb_registered);
    connect(ui->ps_login,&QPushButton::clicked,this,&Login::on_pb_login);
}

void Login::init() {
    this->setFixedSize(this->size());
}

void Login::on_pb_login() {
    this->hide();
    if(msql.login_from_qq(ui->li_qq_email->text(),ui->li_passwd->text())){
        ma.show();
    }else{
        QMessageBox::information(this,"Login","Login failed!!!");
        this->show();
    }

}

void Login::on_pb_registered() {
    re.show();
}
