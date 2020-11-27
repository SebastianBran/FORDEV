#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include "postuser.h"
#include "FordevC.h"
#include "information.h"
#include <QVBoxLayout>
#include <QPlainTextEdit>

namespace Ui {
class Home;
}

class Home : public QWidget
{
    Q_OBJECT
    Fordev_* fordev_;
    Information* information;
    int indice = 0;
    QVBoxLayout* layout;
public:
    explicit Home(Fordev_* fordev_, Information* information, QWidget *parent = nullptr);
    ~Home();
    void Refresh();
    void showPost(PostU* a);
private slots:
    void on_pb_post_clicked();
    void on_pb_post_pressed();
    void on_pb_post_released();
    void interactionP();

    void on_pb_aplicar_clicked();

private:
    Ui::Home *ui;
};

#endif // HOME_H
