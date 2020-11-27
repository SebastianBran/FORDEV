#ifndef MYFOLLOWERS_H
#define MYFOLLOWERS_H

#include <QWidget>
#include "FordevC.h"
#include "showfollowers.h"
#include "myfollowed.h"
#include "information.h"

namespace Ui {
class MyFollowers;
}

class MyFollowers : public QWidget
{
    Q_OBJECT
    Fordev_* fordev_;
    ShowFollowers* showFollowers;
    Information* info;
public:
    explicit MyFollowers(Fordev_* fordev_, Information* info, QWidget *parent = nullptr);
    ~MyFollowers();
    void Refresh();
private slots:
    void on_pushButton_pressed();

    void on_pushButton_released();

    void on_pushButton_clicked();

private:
    Ui::MyFollowers *ui;
};

#endif // MYFOLLOWERS_H
