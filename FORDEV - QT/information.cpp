#include "information.h"
#include "ui_information.h"

Information::Information(Fordev_* fordev_, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Information)
{
    ui->setupUi(this);
    this->fordev_ = fordev_;
    ui->lbl_name->setText(this->fordev_->getUser()->getName());
    ui->lbl_email->setText(this->fordev_->getUser()->getEmail());
    ui->lbl_cantPosts->setText(QString::number(this->fordev_->getUser()->getPostsTitle()->size()) + " Publicaciones");
    RefreshI();
}

Information::~Information()
{
    delete ui;
}

void Information::RefreshI() {
    ui->lbl_cantFollowed->setText(QString::number(fordev_->getUser()->getFollowed()->size()) + " seguidos");
    ui->lbl_cantPosts->setText(QString::number(this->fordev_->getUser()->getPostsTitle()->size()) + " Publicaciones");
}
