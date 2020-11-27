#ifndef FPERSONS_H
#define FPERSONS_H

#include <QWidget>
#include "FordevC.h"
#include <QPushButton>
#include <QPainter>

namespace Ui {
class FPersons;
}

class FPersons : public QWidget
{
    Q_OBJECT
    Fordev_* fordev_;
public:
    explicit FPersons(Fordev_* fordev_, QWidget *parent = nullptr);
    ~FPersons();
    //virtual void paintEvent(QPaintEvent* event);
private:
    Ui::FPersons *ui;
};

#endif // FPERSONS_H
