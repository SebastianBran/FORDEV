#include "myfollowed.h"
#include "ui_myfollowed.h"

MyFollowed::MyFollowed(Fordev_* fordev_, Information* info, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyFollowed)
{
    ui->setupUi(this);
    this->fordev_ = fordev_;
    this->info = info;
    layout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    Refresh();
}

MyFollowed::~MyFollowed()
{
    delete ui;
}

void MyFollowed::Refresh() {
    QLayoutItem *pChild;

    while ((pChild = layout->takeAt(0)) != 0) {
        if (pChild->widget()) {
            pChild->widget()->setParent(nullptr);
        }
        delete pChild;
        pChild=nullptr;
    }
    int i = 0;

    for (List<Person*>::Iterator it = this->fordev_->getUser()->getFollowed()->begin();
        it != this->fordev_->getUser()->getFollowed()->end(); ++it) {
        Person *a = *it;
        if(a->getEmail() != fordev_->getUser()->getEmail()) {
            QLabel* circle = new QLabel(QChar(a->getName()[0]), this);
            circle->setGeometry(30, 20 + 95*i, 80, 80);
            circle->setStyleSheet("background-color: rgb(255, 69, 103); border-radius: 39px; font: 38pt \"Calibri\";");
            circle->setMaximumWidth(80);
            circle->setMaximumHeight(80);
            circle->setAlignment(Qt::AlignCenter);

            QLabel* lbl1 = new QLabel(a->getName() , this);

            lbl1->setGeometry(130, 20 + 90*i, 450, 40);
            lbl1->setStyleSheet("font: 20pt \"Calibri\";");

            QLabel* lbl2 = new QLabel(a->getEmail(), this);
            lbl2->setGeometry(130, 60 + 90*i, 450, 40);
            lbl2->setStyleSheet("font: 14pt \"Calibri\";");
            i++;

            QHBoxLayout* circ = new QHBoxLayout(this);
            QVBoxLayout* date = new QVBoxLayout(this);

            circ->addWidget(circle);

            circ->addLayout(date);
            date->addWidget(lbl1);
            date->addWidget(lbl2);

            QWidget* wid = new QWidget(this);
            wid->setMaximumSize(415, 100);
            wid->setMinimumSize(415, 100);
            wid->setLayout(circ);
            layout->addWidget(wid);
        }
        i++;
    }

    layout->addStretch();
}

void MyFollowed::on_pushButton_pressed()
{
    ui->pushButton->setStyleSheet("background-color: rgb(125, 125, 125); border-radius: 5px;");
}

void MyFollowed::on_pushButton_released()
{
    ui->pushButton->setStyleSheet("background-color: rgb(243, 243, 243); border-radius: 5px;");
}

void MyFollowed::on_pushButton_clicked()
{
    if (fordev_->deleteFollowUser(ui->lineEdit->text())) {
        ui->lineEdit->setText("");
        info->RefreshI();
        Refresh();
        QMessageBox::information(this,tr("Fordev"),tr("Seguido eliminado"));
    }
    else {
        QMessageBox::information(this,tr("Fordev"),tr("No se encontró dicho usuario"));
    }
}
