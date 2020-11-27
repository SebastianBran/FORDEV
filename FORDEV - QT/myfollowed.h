#ifndef MYFOLLOWED_H
#define MYFOLLOWED_H

#include <QWidget>
#include "FordevC.h"
#include "showfollowed.h"
#include "myfollowers.h"
#include "information.h"
#include <QVBoxLayout>

namespace Ui {
class MyFollowed;
}

class MyFollowed : public QWidget
{
    Q_OBJECT
    Fordev_* fordev_;
    ShowFollowed* showFollowed;
    Information* info;
    QVBoxLayout* layout;
public:
    explicit MyFollowed(Fordev_* fordev_, Information* info, QWidget* parent = nullptr);
    ~MyFollowed();
    void Refresh();
private slots:
    void on_pushButton_pressed();

    void on_pushButton_released();

    void on_pushButton_clicked();

private:
    Ui::MyFollowed *ui;
};

#endif // MYFOLLOWED_H
