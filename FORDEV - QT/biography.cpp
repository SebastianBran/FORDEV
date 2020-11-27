#include "biography.h"
#include "ui_biography.h"

Biography::Biography(Fordev_* fordev_, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Biography)
{
    ui->setupUi(this);
    this->fordev_ = fordev_;
    //
    info = new Information(this->fordev_);
    followers = new Followers(this->fordev_, info);
    myPublications = new MyPublications(this->fordev_);
    //
    myFollowed = followers->getMyFollowed();
    //
    ui->Bio_windows->addWidget(info);
    ui->Bio_windows->addWidget(myPublications);
    ui->Bio_windows->addWidget(followers);
}

Biography::~Biography()
{
    delete ui;
}

MyFollowed* Biography::getMyFollowed() { return myFollowed; }
Information* Biography::getInformation() { return info; }

void Biography::on_btn_info_clicked()
{
    ui->Bio_windows->setCurrentIndex(0);
    ui->btn_info->setStyleSheet("background-color: rgb(217, 217, 217); border-radius: 5px; font: 12pt \"Calibri\"; color: rgb(0, 0, 0);");
    ui->btn_segui->setStyleSheet("border-radius: 5px; font: 12pt \"Calibri\"; color: rgb(0, 0, 0);");
    ui->btn_publi->setStyleSheet("border-radius: 5px; font: 12pt \"Calibri\"; color: rgb(0, 0, 0);");
}

void Biography::on_btn_publi_clicked()
{
    ui->Bio_windows->setCurrentIndex(1);
    ui->btn_info->setStyleSheet("border-radius: 5px; font: 12pt \"Calibri\"; color: rgb(0, 0, 0);");
    ui->btn_segui->setStyleSheet("border-radius: 5px; font: 12pt \"Calibri\"; color: rgb(0, 0, 0);");
    ui->btn_publi->setStyleSheet("background-color: rgb(217, 217, 217); border-radius: 5px; font: 12pt \"Calibri\"; color: rgb(0, 0, 0);");
}

void Biography::on_btn_segui_clicked()
{
    ui->Bio_windows->setCurrentIndex(2);
    ui->btn_segui->setStyleSheet("background-color: rgb(217, 217, 217); border-radius: 5px; font: 12pt \"Calibri\"; color: rgb(0, 0, 0);");
    ui->btn_info->setStyleSheet("border-radius: 5px; font: 12pt \"Calibri\"; color: rgb(0, 0, 0);");
    ui->btn_publi->setStyleSheet("border-radius: 5px; font: 12pt \"Calibri\"; color: rgb(0, 0, 0);");
}

