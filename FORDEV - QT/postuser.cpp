#include "postuser.h"
#include "ui_postuser.h"

PostUser::PostUser(QString name, QString lastname, QString nickname, QString content, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PostUser)
{
    ui->setupUi(this);
    ui->label_2->setText(name + " " + lastname);
    ui->label_3->setText(nickname);
    ui->plainTextEdit->insertPlainText(content);
}

PostUser::~PostUser()
{
    delete ui;
}
