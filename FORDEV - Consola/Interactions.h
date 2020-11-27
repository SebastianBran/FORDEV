#ifndef __INTERACTIONS_H__
#define __INTERACTIONS_H__

#include <iostream>
#include <string>

using namespace std;

class Interactions {
    int idU,idPub;
    string date;
    bool share;
public:
    Interactions(int idU, int idPub, string date, bool share): idU(idU), idPub(idPub), date(date), share(share) {}

    ~Interactions() {}

    int getIdU();
    int getIdPub();
    string getDate();
    bool getShare();

    //void showInteractions();
}; 

int Interactions::getIdU() { return idU; }
int Interactions::getIdPub() { return idPub; }
string Interactions::getDate() { return date; }
bool Interactions::getShare() { return share; }

/*void Interactions::showInteractions() {
  if (share == TRUE) {
    cout << "El usuario " << idUser << " ha compartido la publicacion " << "idPub" << " en la fecha: " << dateshare << endl;
  }
  else {
    cout << "El usuario " << idUser << "no ha compartido la publicacion " << "idPub" << " en la fecha: " << dateshare << endl;
  }
}*/

#endif