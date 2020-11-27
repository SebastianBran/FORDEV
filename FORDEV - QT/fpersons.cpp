#include "fpersons.h"
#include "ui_fpersons.h"

FPersons::FPersons(Fordev_* fordev_, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FPersons)
{
    ui->setupUi(this);
    this->fordev_ = fordev_;

    int i = 0;
    function<void(Person*, int&)> proc = [&](Person* a, int& cont) {
        if(a->getEmail() != fordev_->getUser()->getEmail()) {
            QLabel* circle = new QLabel(QChar(a->getName()[0]), this);
            circle->setGeometry(30, 20 + 95*i, 80, 80);
            circle->setStyleSheet("background-color: rgb(255, 69, 103); border-radius: 40px; font: 38pt \"Calibri\";");
            circle->setAlignment(Qt::AlignCenter);

            QLabel* lbl1 = new QLabel(a->getName(), this);
            lbl1->setGeometry(130, 20 + 90*i, 450, 40);
            lbl1->setStyleSheet("font: 20pt \"Calibri\";");

            QLabel* lbl2 = new QLabel(a->getEmail(), this);
            lbl2->setGeometry(130, 60 + 90*i, 450, 40);
            lbl2->setStyleSheet("font: 14pt \"Calibri\";");
            i++;
        }
    };
    fordev_->getPersons()->inOrder(proc);
}

FPersons::~FPersons()
{
    delete ui;
}
