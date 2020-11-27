#ifndef POSTUSER_H
#define POSTUSER_H

#include <QWidget>

namespace Ui {
class PostUser;
}

class PostUser : public QWidget
{
    Q_OBJECT

public:
    explicit PostUser(QString name, QString lastname, QString nickname, QString content, QWidget *parent = nullptr);
    ~PostUser();

private:
    Ui::PostUser *ui;
};

#endif // POSTUSER_H
