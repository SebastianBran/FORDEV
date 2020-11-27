#ifndef INTERACTION_H
#define INTERACTION_H

#include <QString>

class Interaction
{
    int idU, idP;
    QString date;
    bool share;
public:
    Interaction(int idU, int idP, QString date, bool share) : idU(idU), idP(idP), date(date), share(share) {}

    int getIdU();
    int getIdP();
    QString getDate();
    bool getShare();
};

#endif // INTERACTION_H
