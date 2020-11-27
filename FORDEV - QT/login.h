#ifndef LOGIN_H
#define LOGIN_H

#include "fordev.h"
#include "register.h"
#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT
    Fordev_* fordev_;

public:
    explicit Login(Fordev_*& fordev_, QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_loginButton_clicked();
    void on_btRegistrate_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
