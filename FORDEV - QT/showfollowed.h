#ifndef SHOWFOLLOWED_H
#define SHOWFOLLOWED_H

#include <QWidget>
#include "FordevC.h"

namespace Ui {
class ShowFollowed;
}

class ShowFollowed : public QWidget
{
    Q_OBJECT
    Fordev_* fordev_;
    int cont = 0;
public:
    explicit ShowFollowed(Fordev_* fordev_, QWidget *parent = nullptr);
    ~ShowFollowed();
    void Refresh();
private:
    Ui::ShowFollowed *ui;
};

#endif // SHOWFOLLOWED_H
