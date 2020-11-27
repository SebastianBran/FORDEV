#ifndef __COMMENT_H__
#define __COMMENT_H__

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Comment {
    int idU, idPub;
    string date, content, atName;
public:
    //Comment(int idU, int idPub, string date, string content) : idU(idU), idPub(idPub), date(date), content(content) {}
    Comment(int idU, int idPub, string date, string content, string atName) : 
            idU(idU), idPub(idPub), date(date), content(content), atName(atName) {}

    ~Comment() {}

    int getIdU();
    int getIdPub();
    string getDate();
    string getContent();

    void showInfo();
};

int Comment::getIdU() { return idU; }
int Comment::getIdPub() { return idPub; }
string Comment::getDate() { return date; }
string Comment::getContent() { return content; }

void Comment::showInfo() {
    cout << "    " << atName << " | " << date << endl;
    cout << "    " << content << endl;
    cout << "    " << "|--" << endl;
}

#endif