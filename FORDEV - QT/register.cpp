#include "register.h"
#include "ui_register.h"

Register::Register(Fordev_* fordev_, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->fordev_ = fordev_;
}

Register::~Register()
{
    delete ui;
}


void Register::on_pushButton_clicked()
{
    QString name = ui->line_name->text();
    QString email = ui->line_email->text();

    if(name.length() == 0 || email.length() == 0)
    {
        QMessageBox::information(this,tr("Fordev"),tr("Complete todos sus datos"));
    }
    else
    {
        if (fordev_->registerPerson(email, name, "2020-11-23")) {
            Fordev* start = new Fordev(fordev_);
            start->show();
            Register::close();
        }
        else {
             QMessageBox::information(this, tr("Fordev"), tr("Email invalid :("));
        }
    }
}

void Register::on_commandLinkButton_clicked()
{
    Login* login = new Login(fordev_);
    login->show();
    Register::close();
}
