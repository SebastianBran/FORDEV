#ifndef SHOWFOLLOWERS_H
#define SHOWFOLLOWERS_H

#include <QWidget>
#include "FordevC.h"

namespace Ui {
class ShowFollowers;
}

class ShowFollowers : public QWidget
{
    Q_OBJECT
    Fordev_* fordev_;
public:
    explicit ShowFollowers(Fordev_* fordev_, QWidget *parent = nullptr);
    ~ShowFollowers();
    void Refresh();
private:
    Ui::ShowFollowers *ui;
};

#endif // SHOWFOLLOWERS_H
