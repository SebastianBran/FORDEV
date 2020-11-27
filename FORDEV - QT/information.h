#ifndef INFORMATION_H
#define INFORMATION_H

#include <QWidget>
#include "FordevC.h"

namespace Ui {
class Information;
}

class Information : public QWidget
{
    Q_OBJECT
    Fordev_* fordev_;
public:
    explicit Information(Fordev_* fordev_, QWidget *parent = nullptr);
    ~Information();
    void RefreshI();
private:
    Ui::Information *ui;
};

#endif // INFORMATION_H
