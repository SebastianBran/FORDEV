#include "myfollowers.h"
#include "ui_myfollowers.h"

MyFollowers::MyFollowers(Fordev_* fordev_, Information* info, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyFollowers)
{
    ui->setupUi(this);
    this->fordev_ = fordev_;
    this->info = info;
    showFollowers = new ShowFollowers(this->fordev_);
    ui->stackedWidget->addWidget(showFollowers);
    Refresh();
}

MyFollowers::~MyFollowers()
{
    delete ui;
}

void MyFollowers::Refresh() {
    showFollowers->Refresh();
}

void MyFollowers::on_pushButton_pressed()
{
    ui->pushButton->setStyleSheet("background-color: rgb(125, 125, 125); border-radius: 5px;");
}

void MyFollowers::on_pushButton_released()
{
    ui->pushButton->setStyleSheet("background-color: rgb(243, 243, 243); border-radius: 5px;");
}

void MyFollowers::on_pushButton_clicked()
{
    /*if (fordev_->deleteFollowerUser(ui->lineEdit->text())) {
        QLabel* erase = new QLabel(showFollowers);
        erase->setGeometry(0, 0, 541, 441);
        erase->setStyleSheet("background-color: rgb(217, 217, 217);");
        erase->show();
        ui->lineEdit->setText("");
        info->RefreshI();
        Refresh();
        ui->lineEdit->setText("");
        QMessageBox::information(this,tr("Fordev"),tr("Seguido eliminado"));
    }
    else {
        QMessageBox::information(this,tr("Fordev"),tr("No se encontró dicho usuario"));
    }*/
}
