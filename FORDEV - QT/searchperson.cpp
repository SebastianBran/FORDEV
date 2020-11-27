#include "searchperson.h"
#include "ui_searchperson.h"

SearchPerson::SearchPerson(Fordev_* fordev_, MyFollowed* myFollowed, Information* information, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchPerson)
{
    ui->setupUi(this);
    this->fordev_ = fordev_;
    this->myFollowed = myFollowed;
    this->information = information;
    //
    layout = new QVBoxLayout(this);
    ui->scrollAreaWidgetContents->setLayout(layout);

    function<void(Person*,int &)> proc = [&](Person* a,int &cont) {
        if(a->getEmail() != fordev_->getUser()->getEmail()) {
            QLabel* circle = new QLabel(QChar(a->getName()[0]), this);
            circle->setGeometry(30, 95, 80, 80);

            circle->setStyleSheet("background-color: rgb(255, 69, 103); border-radius: 39px; font: 38pt \"Calibri\";");
            circle->setMaximumWidth(80);
            circle->setMaximumHeight(80);

            circle->setAlignment(Qt::AlignCenter);

            QLabel* lbl1 = new QLabel(a->getName() , this);

            lbl1->setGeometry(130, 90, 450, 40);
            lbl1->setStyleSheet("font: 20pt \"Calibri\";");

            QLabel* lbl2 = new QLabel(a->getEmail(), this);
            lbl2->setGeometry(130, 90, 450, 40);
            lbl2->setStyleSheet("font: 14pt \"Calibri\";");

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
    };
    fordev_->getPersons()->inOrder(proc);
}

SearchPerson::~SearchPerson()
{
    delete ui;
}

void SearchPerson::on_btn_searchPerson_released()
{
    ui->btn_searchPerson->setStyleSheet("background-color: rgb(217, 217, 217); border-radius: 5px;");
}

void SearchPerson::on_btn_searchPerson_pressed()
{
    ui->btn_searchPerson->setStyleSheet("background-color: rgb(125, 125, 125); border-radius: 5px;");
}

void SearchPerson::on_btn_searchPerson_clicked()
{
    QString email = ui->le_email->text();
    if (fordev_->addFollowUser(email)) {
        QMessageBox::information(this,tr("Fordev"),tr("Usuario seguido"));
        myFollowed->Refresh(); //refresca lista de seguidos
        information->RefreshI(); //refresca informacion
        ui->le_email->setText("");
    } else {
        QMessageBox::information(this,tr("Fordev"),tr("No se encontró dicho usuario"));
    }
}
