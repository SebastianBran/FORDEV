#include "mypublications.h"
#include "ui_mypublications.h"

MyPublications::MyPublications(Fordev_* fordev_, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyPublications)
{
    ui->setupUi(this);
    this->fordev_ = fordev_;
    layout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    Refresh();
}

MyPublications::~MyPublications()
{
    delete ui;
}

void MyPublications::showPost(PostU *a) {
    QWidget* postWid = new QWidget(ui->scrollAreaWidgetContents);
    postWid->setMaximumSize(620, 230);
    postWid->setMinimumSize(620, 230);
    postWid->autoFillBackground();
    postWid->setStyleSheet("background-color: rgb(255, 126, 150);");

    QVBoxLayout* vb = new QVBoxLayout(postWid);

    QHBoxLayout* headHb = new QHBoxLayout(postWid);
    QLabel* AtName = new QLabel(a->getAtName(), postWid);
    QLabel* datePost = new QLabel(a->getPubDate(), postWid);
    datePost->setAlignment(Qt::AlignRight);

    headHb->addWidget(AtName);
    headHb->addWidget(datePost);

    QPlainTextEdit* title = new QPlainTextEdit(a->getTitle(), postWid);
    title->setStyleSheet("background-color:white");
    QPlainTextEdit* content = new QPlainTextEdit(a->getContent(), postWid);
    content->setStyleSheet("background-color:white");

    vb->addLayout(headHb);
    vb->addWidget(title);
    vb->addWidget(content);

    QHBoxLayout* hb1 = new QHBoxLayout(postWid);

    QLabel* cantR = new QLabel(QString::number(a->getReactions()), postWid); cantR->setObjectName("contR");
    /*contR->setAlignment(Qt::AlignCenter);*/ //contR->setObjectName("contR");
    QLabel* cantC = new QLabel(QString::number(a->getComments()->size()), postWid); cantC->setObjectName("contC");
    /*contC->setAlignment(Qt::AlignCenter);*/ //contC->setObjectName("contC");
    QLabel* nada = new QLabel(postWid); nada->setObjectName("nada");

    hb1->addWidget(cantR);
    hb1->addWidget(cantC);
    hb1->addWidget(nada);

    vb->addLayout(hb1);

    QHBoxLayout* hb2 = new QHBoxLayout(postWid);

    QString idP = QString::number(a->getId());
    QPushButton* pb1 = new QPushButton("Reaccionar", postWid); pb1->setObjectName(idP + "br");
    QPushButton* pb2 = new QPushButton("Comentar", postWid); pb2->setObjectName(idP + "bc");
    QPushButton* pb3 = new QPushButton("Compartir", postWid); pb3->setObjectName(idP + "bs");

    hb2->addWidget(pb1);
    hb2->addWidget(pb2);
    hb2->addWidget(pb3);

    vb->addLayout(hb2);

    layout->addWidget(postWid);
}

void MyPublications::Refresh() {
    QLayoutItem *pChild;

    while ((pChild = layout->takeAt(0)) != 0) {
        if (pChild->widget()) {
            pChild->widget()->setParent(nullptr);
        }
        delete pChild;
        pChild = nullptr;
    }

    function<void(PostU*, int&)> proc = [&](PostU* a, int &cont) {
        showPost(a);
        cont++;
    };

    fordev_->getUser()->getPostsTitle()->inOrderR(proc);

    layout->addStretch();
}
