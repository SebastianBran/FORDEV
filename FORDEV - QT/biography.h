#ifndef BIOGRAPHY_H
#define BIOGRAPHY_H

#include <QWidget>
#include "FordevC.h"
#include "information.h"
#include "followers.h"
#include "mypublications.h"

namespace Ui {
class Biography;
}

class Biography : public QWidget
{
    Q_OBJECT
    Fordev_* fordev_;
    Information* info;
    Followers* followers;
    MyFollowed* myFollowed;
    MyPublications* myPublications;
public:
    explicit Biography(Fordev_* fordev_, QWidget *parent = nullptr);
    ~Biography();
    MyFollowed* getMyFollowed();
    Information* getInformation();
private slots:
    void on_btn_info_clicked();
    void on_btn_segui_clicked();

    void on_btn_publi_clicked();

private:
    Ui::Biography *ui;
};

#endif // BIOGRAPHY_H
