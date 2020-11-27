#ifndef PERSON_H
#define PERSON_H

#include "List.h"
#include "Stack.h"
#include <QString>
#include <QDate>
#include "postu.h"
#include "AVL.h"

class Person {
    int id;
    QString email, name, date;

    AVL<PostU*, QString>* postsTitle = new AVL<PostU*, QString>([](PostU* a) { return a->getTitle(); });
    AVL<PostU*, QString>* postsPubDate = new AVL<PostU*, QString>([](PostU* a) { return a->getPubDate(); });
    AVL<PostU*, int>* postsReacts = new AVL<PostU*, int>([](PostU* a) { return a->getReactions(); });

    List<Person*> followed;
public:
    Person() {}
    Person(int id, QString email, QString name, QString date) : id(id), email(email), name(name), date(date) {}

    ~Person();

    void setId(int id);
    void setEmail(QString email);
    void setName(QString name);
    void setDate(QString date);

    int getId();
    QString getEmail();
    QString getName();
    QString getDate();

    List<Person*>* getFollowed();

    /**AVLS**/
    AVL<PostU*, QString>* getPostsTitle();
    AVL<PostU*, QString>* getPostsPubDate();
    AVL<PostU*, int>* getPostsReacts();
    /********/

    void addFollowed(Person* a);
    bool noFollow(QString email);

    void addPost(PostU* post);
    void removePost(PostU* post);
};

#endif
