#include "fordev.h"
#include "ui_fordev.h"

Fordev::Fordev(Fordev_*& fordev_, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Fordev)
{
    ui->setupUi(this);
    this->fordev_ = fordev_;
    bio = new Biography(this->fordev_);
    sper = new SearchPerson(this->fordev_, bio->getMyFollowed(), bio->getInformation());
    home = new Home(this->fordev_, bio->getInformation());
    //
    ui->username->setText(fordev_->getUser()->getName());
    ui->windows->addWidget(home);
    ui->windows->addWidget(sper);
    ui->windows->addWidget(bio);
}

Fordev::~Fordev()
{
    delete ui;
}

void Fordev::on_logout_clicked()
{
    //fordev_->saveInfo();
    fordev_->logout();
    Login* login = new Login(fordev_);
    login->show();
    Fordev::close();
}

void Fordev::on_home_clicked()
{
    ui->windows->setCurrentIndex(0);
}

void Fordev::on_preguntas_clicked()
{
    ui->windows->setCurrentIndex(1);
}

void Fordev::on_biografia_clicked()
{
    ui->windows->setCurrentIndex(2);
}


