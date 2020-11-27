#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{    
    Fordev_* fordev_ = new Fordev_();
    /*QDate date(2001,8,13);
    Person* per = new Person("Sebastian", "Bran", "sebas", "123", date);
    QDate date2(2002,5,23);
    Person* per2 = new Person("Paul", "Tunque", "zentix", "123", date2);
    fordev_->registerPerson(per);
    fordev_->registerPerson(per2);*/
    //
    QApplication a(argc, argv);
    Login* z = new Login(fordev_);

    z->show();
    return a.exec();
}
