#ifndef FORDEV_H
#define FORDEV_H

#include <QMainWindow>
#include "biography.h"
#include "home.h"
#include "login.h"
#include "searchperson.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Fordev; }
QT_END_NAMESPACE

class Fordev : public QMainWindow
{
    Q_OBJECT
    Fordev_* fordev_;
    QString aux;
    Biography* bio;
    Home* home;
    SearchPerson* sper;
public:
    Fordev(Fordev_*& fordev_, QWidget *parent = nullptr);
    ~Fordev();

private slots:
    void on_logout_clicked();

    void on_home_clicked();

    void on_biografia_clicked();

    void on_preguntas_clicked();

private:
    Ui::Fordev *ui;
};
#endif // FORDEV_H
