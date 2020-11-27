#include "followers.h"
#include "ui_followers.h"

Followers::Followers(Fordev_* fordev_, Information* info, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Followers)
{
    ui->setupUi(this);
    this->fordev_ = fordev_;
    this->info = info;
    myFollowed = new MyFollowed(this->fordev_, this->info);
    ui->swWindows->addWidget(myFollowed);
    //ui->swWindows->addWidget(myFollowers);
}

Followers::~Followers()
{
    delete ui;
}

MyFollowed* Followers::getMyFollowed() { return myFollowed; }
