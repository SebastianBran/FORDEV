#include "login.h"
#include "ui_login.h"

Login::Login(Fordev_*& fordev_, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->fordev_ = fordev_;
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{
    QString email = ui->email->text();

    if (email.length() == 0) {
        QMessageBox::information(this,tr("Fordev"),tr("Complete todos sus datos"));
    }
    else if (fordev_->login(email)) {
        Fordev* start = new Fordev(fordev_);
        start->show();
        Login::close();
    }
    else {
        QMessageBox::information(this, tr("Fordev"), tr("email or password invalid :("));
    }
}

void Login::on_btRegistrate_clicked()
{
    Register* regis = new Register(fordev_);
    regis->show();
    Login::close();
}
