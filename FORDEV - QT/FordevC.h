#ifndef FORDEVC_H
#define FORDEVC_H

#include "Person.h"
#include <functional>
#include <QMessageBox>
#include <fstream>
#include "AVL.h"
#include <chrono>

using std::chrono::system_clock;

using namespace std;

class Fordev_ {
    AVL<Person*, QString>* persons = new AVL<Person*, QString>([](Person* a) { return a->getEmail();});
    AVL<Person*, int>* personsId = new AVL<Person*, int>([](Person* a) { return a->getId();});
    Person* user;
    //
    AVL<PostU*, QString>* postsTitle = new AVL<PostU*, QString>([](PostU* a) { return a->getTitle(); }); // arbol organizado por el titulo de publicacion alfabeticamente
    AVL<PostU*, int>* postsID = new AVL<PostU*, int>([](PostU* a) { return a->getId(); }); //arbol organizado por los ids de las publicaciones
    AVL<PostU*, QString>* postsPubDate = new AVL<PostU*, QString>([](PostU* a) { return a->getPubDate(); }); //arbol organizado por las fechas de publicacion
    AVL<PostU*, int>* postsReacts = new AVL<PostU*, int>([](PostU* a) { return a->getReactions(); }); //arbol organizado por la cantidad de reacciones
    AVL<PostU*, int>* postsRelev = new AVL<PostU*, int>([](PostU* a) { return a->getRelevance(); }); //arbol organizado por la relevancia
    //
    int idComment = 0;
    int filterPost, typeFilter;
    QString wordKey;
public:
    Fordev_() : user(nullptr), filterPost(1), typeFilter(1) { loadInfo(); }
    ~Fordev_();

    Person* getUser();

    AVL<Person*, QString>* getPersons();
    AVL<PostU*, QString>* getPostsTitle();
    AVL<PostU*, int>* getPostsID();
    AVL<PostU*, QString>* getPostsPubDate();
    AVL<PostU*, int>* getPostsReacts();
    AVL<PostU*, int>* getPostsRelev();

    bool registerPerson(QString email, QString name, QString date);
    bool login(QString email);
    void logout();

    QString getDate();

    /**USER**/
    bool addFollowUser(QString email);
    bool deleteFollowUser(QString email);

    /**POSTS**/
    void addPost(QString title, QString content, QString date);
    void addComment(QString title, QString content, QString date);
    void reactPost(QString title);
    void sharePost(QString title);
    bool searchPost(QString title);

    void setFilterPost(int filterPost);
    void setWordKey(QString wordKey);
    void setTypeFilter(int typeFilter);

    /**INFO**/
    void saveInfo();
    void loadInfo();
    void loadComents(int id, int idPub, QString date, QString content);
    void loadFollowers(int idU, int idF);
    void loadInteractions(int idU, int idP, QString date, bool share);
};

#endif
