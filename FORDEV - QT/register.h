#ifndef REGISTER_H
#define REGISTER_H

#include <ui_register.h>
#include "FordevC.h"
#include "fordev.h"
#include <QMessageBox>

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT
    Fordev_* fordev_;
public:
    explicit Register(Fordev_* fordev_, QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_pushButton_clicked();
    void on_commandLinkButton_clicked();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
