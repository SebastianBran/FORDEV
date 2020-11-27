#ifndef MYPUBLICATIONS_H
#define MYPUBLICATIONS_H

#include <QWidget>
#include <FordevC.h>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QPushButton>

namespace Ui {
class MyPublications;
}

class MyPublications : public QWidget
{
    Q_OBJECT
    Fordev_* fordev_;
    QVBoxLayout* layout;
public:
    explicit MyPublications(Fordev_* fortdev_, QWidget *parent = nullptr);
    ~MyPublications();
    void Refresh();
    void showPost(PostU* a);
private:
    Ui::MyPublications *ui;
};

#endif // MYPUBLICATIONS_H
