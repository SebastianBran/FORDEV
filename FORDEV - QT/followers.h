#ifndef FOLLOWERS_H
#define FOLLOWERS_H

#include <QWidget>
#include "myfollowed.h"
#include "information.h"

namespace Ui {
class Followers;
}

class Followers : public QWidget
{
    Q_OBJECT
    Fordev_* fordev_;
    MyFollowed* myFollowed;
    Information* info;
public:
    explicit Followers(Fordev_* fordev_, Information* info, QWidget *parent = nullptr);
    ~Followers();
    MyFollowed* getMyFollowed();
private slots:

private:
    Ui::Followers *ui;
};

#endif // FOLLOWERS_H
