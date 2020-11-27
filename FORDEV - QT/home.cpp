#include "home.h"
#include "ui_home.h"

Home::Home(Fordev_* fordev_, Information* information, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home)
{
    //connect(ui->pb_aplicar, SIGNAL(relesed), this, SLOT(refresh()));
    ui->setupUi(this);
    this->fordev_ = fordev_;
    this->information = information;
    layout = new QVBoxLayout(ui->sa_postscontent);
    layout->setDirection(layout->TopToBottom);
    Refresh();
}

Home::~Home()
{
    delete ui;
}

void Home::on_pb_post_clicked()
{
    if (ui->te_title->toPlainText() != "" && ui->te_content->toPlainText() != "") {
        fordev_->addPost(ui->te_title->toPlainText(), ui->te_content->toPlainText(), fordev_->getDate());
        Refresh();
        ui->te_title->clear();
        ui->te_content->clear();
        //layout->update();
    }
}

void Home::on_pb_post_pressed()
{
    ui->pb_post->setStyleSheet("background-color: rgb(125, 125, 125); border-radius: 5px;");
}

void Home::on_pb_post_released()
{
    ui->pb_post->setStyleSheet("background-color: rgb(243, 243, 243); border-radius: 5px;");
}

void Home::showPost(PostU *a) {
    QWidget* postWid = new QWidget(ui->sa_postscontent);
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

    connect(pb1, SIGNAL(released()), this, SLOT(interactionP()));
    connect(pb2, SIGNAL(released()), this, SLOT(interactionP()));
    connect(pb3, SIGNAL(released()), this, SLOT(interactionP()));
    hb2->addWidget(pb1);
    hb2->addWidget(pb2);
    hb2->addWidget(pb3);

    vb->addLayout(hb2);

    layout->addWidget(postWid);
}

void Home::Refresh() {
    if (ui->cb_filters->currentIndex() != 0 && ui->le_wordKey->text() == "") {
        QMessageBox::information(this,tr("Fordev"), tr("Ingrese la palabra clave"));
    }
    else {
        QLayoutItem *pChild;

        while ((pChild = layout->takeAt(0)) != 0) {
            if (pChild->widget()) {
                pChild->widget()->setParent(nullptr);
            }
            delete pChild;
            pChild = nullptr;
        }

        function<void(PostU*, int&)> proc;

        if (ui->cb_filters->currentIndex() == 0) {
            ui->le_wordKey->clear();
            proc = [&](PostU* a, int &cont) {
                showPost(a);
                cont++;
            };
        }
        else if (ui->cb_filters->currentIndex() == 1) {
            proc = [&](PostU* a, int &cont) {
                if (a->getTitle() == ui->le_wordKey->text()) { showPost(a); cont++; }
            };
        }
        else if (ui->cb_filters->currentIndex() == 2) {
            proc = [&](PostU* a, int& cont) {
                bool es = true;
                for (int i = 0; i < min(ui->le_wordKey->text().size(), a->getTitle().size()); i++) {
                    if (ui->le_wordKey->text()[i] != a->getTitle()[i]) {
                        es = false;
                        break;
                    }
                }
                if (es) {
                    showPost(a);
                    cont++;
                }
            };
        }
        else if (ui->cb_filters->currentIndex() == 3) {
            proc = [&](PostU* a, int& cont) {
                bool es = true;
                for (int i = ui->le_wordKey->text().size() - 1, j = a->getTitle().size() - 1;
                     i >= 0 && j >= 0; i--, j--) {
                    if (ui->le_wordKey->text()[i] != a->getTitle()[j]) {
                        es = false;
                        break;
                    }
                }
                if (es) {
                    showPost(a);
                    cont++;
                }
            };
        }
        else if (ui->cb_filters->currentIndex() == 4) {
            proc = [&](PostU* a, int& cont) {
                if (a->getTitle().count(ui->le_wordKey->text()) > 0) {
                    showPost(a);
                    cont++;
                }
            };
        }
        else if (ui->cb_filters->currentIndex() == 5) {
            proc = [&](PostU* a, int& cont) {
                if (a->getTitle().count(ui->le_wordKey->text()) == 0) {
                    showPost(a);
                    cont++;
                }
            };
        }

        if (ui->cb_trends->currentIndex() == 0) fordev_->getPostsPubDate()->inOrderR(proc);
        else if (ui->cb_trends->currentIndex() == 1) fordev_->getPostsReacts()->inOrderR(proc);
        else fordev_->getPostsRelev()->inOrderR(proc);

        //ui->le_wordKey->clear();
    }

    //ui->sa_postscontent->update();
    //fordev_->getPostsReacts()->inOrderR(proc);
    //QMessageBox::information(this,tr("Se puede?"), QString::number(fordev_->getPostsTitle()->size()));
}

void Home::interactionP() {
    QPushButton* btn = (QPushButton*)sender();
    int cantD = btn->objectName().size() - 2;
    int idP = btn->objectName().left(cantD).toInt();
    QString type = btn->objectName().right(2);

    if (type == "br") {
        PostU* post = fordev_->getPostsID()->find(idP, [&](PostU* a) {
                return a->getId() == idP;
        });
        //QMessageBox::information(this,tr("Se puede?"), post->getTitle());

        fordev_->reactPost(post->getTitle());
        //QMessageBox::information(this,tr("Se puede?"), "hola :)");
        /*QWidget* wid = btn->parentWidget();
        QLabel* contR = wid->findChild<QLabel*>("contR");

        QString number = contR->text();
        int aux = number.toInt();
        aux++;
        contR->setText(QString::number(aux));*/
    }
    else if (type == "bc") {

    }

    Refresh();

    /*else if (btn->objectName() == "comment") {

    }*/
}

void Home::on_pb_aplicar_clicked()
{
    Refresh();
}
