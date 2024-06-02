//
// Created by Kiana on 2024/5/20.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Registered.h" resolved

#include "Registered.h"
#include "ui_Registered.h"


Registered::Registered(QWidget *parent) :
        QWidget(parent), ui(new Ui::Registered) {
    ui->setupUi(this);

    this->setFixedSize(this->size());
    connect(ui->sure,&QPushButton::clicked,this,&Registered::on_pb_registered);
}

Registered::~Registered() {
    delete ui;
}

void Registered::on_pb_registered() {
    qDebug() << "-----------> on_pb_registered";
    QString qq = ui->qq_email->text();
    QString passwd1 = ui->passwd1->text();
    QString passwd2 = ui->passwd2->text();

    if(qq != "" && passwd1 != "" && passwd2 != ""){
        if(passwd1 == passwd2)
        {
            mysql.insert_from_qq(qq,passwd1);
            this->close();
        }else{
            QMessageBox::information(this,"error","The password entered is inconsistent");
        }
    }else{
        QMessageBox::information(this,"error","Please enter complete information");
    }
}
