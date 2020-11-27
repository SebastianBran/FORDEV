#ifndef __INTERACTION_H__
#define __INTERACTION_H__

class Interaction {
    int idU, idP;
    string date;
    bool share;

public:
    Interaction(int idU, int idP, string date, bool share) : idU(idU), idP(idP), date(date), share(share) {}

    int getIdU();
    int getIdP();
    string getDate();
    bool getShare();
};

int Interaction::getIdU() { return idU; }
int Interaction::getIdP() { return idP; }
string Interaction::getDate() { return date; }
bool Interaction::getShare() { return share; }

#endif