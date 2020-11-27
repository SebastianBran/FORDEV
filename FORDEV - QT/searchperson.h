#ifndef SEARCHPERSON_H
#define SEARCHPERSON_H

#include <QWidget>
#include "FordevC.h"
#include "myfollowed.h"
#include "information.h"
#include <QVBoxLayout>

namespace Ui {
class SearchPerson;
}

class SearchPerson : public QWidget
{
    Q_OBJECT
    Fordev_* fordev_;
    MyFollowed* myFollowed;
    Information* information;
    QVBoxLayout* layout;

public:
    explicit SearchPerson(Fordev_* fordev_, MyFollowed* myFollowed, Information* information, QWidget *parent = nullptr);
    ~SearchPerson();

private slots:
    void on_btn_searchPerson_released();
    void on_btn_searchPerson_pressed();
    void on_btn_searchPerson_clicked();

private:
    Ui::SearchPerson *ui;
};

#endif // SEARCHPERSON_H
