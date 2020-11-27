#include "showfollowers.h"
#include "ui_showfollowers.h"

ShowFollowers::ShowFollowers(Fordev_* fordev_, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowFollowers)
{
    ui->setupUi(this);
    this->fordev_ = fordev_;
    Refresh();
}

ShowFollowers::~ShowFollowers()
{
    delete ui;
}

void ShowFollowers::Refresh() {
    /*int i = 0;
    for (List<Person*>::Iterator it = this->fordev_->getUser()->getFollower()->begin();
         it != this->fordev_->getUser()->getFollower()->end(); ++it) {
        Person* aux = *it;

        QLabel* circle = new QLabel(QChar(aux->getName()[0]), this);
        circle->setGeometry(10, 20 + 95*i, 80, 80);
        circle->setStyleSheet("background-color: rgb(255, 69, 103); border-radius: 40px; font: 38pt \"Calibri\";");
        circle->setAlignment(Qt::AlignCenter);
        circle->show();

        QLabel* lbl1 = new QLabel(aux->getName() + " " + aux->getLastName(), this);
        lbl1->setGeometry(110, 20 + 95*i, 450, 40);
        lbl1->setStyleSheet("font: 20pt \"Calibri\";");
        lbl1->show();

        QLabel* lbl2 = new QLabel("@" + aux->getEmail(), this);
        lbl2->setGeometry(110, 60 + 95*i, 450, 40);
        lbl2->setStyleSheet("font: 14pt \"Calibri\";");
        lbl2->show();
        i++;
    }*/
}
