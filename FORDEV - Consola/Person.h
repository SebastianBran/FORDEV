#ifndef __PERSON_H__
#define __PERSON_H__

#include "List.h"
#include "AVL.h"
#include <functional>
#include <iostream>
#include "Post.h"

using namespace std;

class Person {
private:
    int id;
    string email, name, date;

    AVL<Post*, string>* postsTitle = new AVL<Post*, string>([](Post* a) { return a->getTitle(); }); 
    AVL<Post*, string>* postsPubDate = new AVL<Post*, string>([](Post* a) { return a->getPubDate(); });
    AVL<Post*, int>* postsReacts = new AVL<Post*, int>([](Post* a) { return a->getReactions(); });
    
    List<Person*> followed;
public:
    Person(int id, string email, string name, string date) : id(id), email(email), name(name), date(date) {} 

    ~Person();

    void setId(int id);
    void setEmail(string email);        
    void setName(string name);
    void setDate(string date);
    
    int getId();
    string getEmail();
    string getName();
    string getDate();
    
    List<Person*>* getFollowed();

    /**AVLS**/
    AVL<Post*, string>* getPostsTitle();
    AVL<Post*, string>* getPostsPubDate();
    AVL<Post*, int>* getPostsReacts();
    /********/

    void addFollowed(Person* a);
    bool noFollow(string nkname);

    void addPost(Post* post);
    void removePost(Post* post);

    void showInfo();
    void showFollowed();
};

Person::~Person() {
    followed.~List();
}

void Person::setId(int id) {this->id = id;}
void Person::setEmail(string email) { this->email = email; }
void Person::setName(string name) { this->name = name; }
void Person::setDate(string date) { this->date = date; }

int Person::getId() { return id; }
string Person::getEmail() { return email; }
string Person::getName() { return name; }
string Person::getDate() { return date; }

List<Person*>* Person::getFollowed() { return &followed; }

/**AVLS**/
AVL<Post*, string>* Person::getPostsTitle() { return postsTitle; }
AVL<Post*, string>* Person::getPostsPubDate() { return postsPubDate; }
AVL<Post*, int>* Person::getPostsReacts() { return postsReacts; }
/********/

void Person::addFollowed(Person* a) { followed.addLast(a); }

bool Person::noFollow(string email) {
    function<bool(Person*)> a = [&](Person* per) { return email == per->getEmail(); };
    return followed.cmp(a);
}

void Person::addPost(Post* post) {
    postsTitle->add(post);
    postsPubDate->add(post);
    postsReacts->add(post);
}

void Person::removePost(Post* post) {
    function<bool(Post*)> cmp = [&](Post* aux) { return aux->getId() == post->getId(); };
    postsTitle->remove(post->getTitle(), cmp);
    postsPubDate->remove(post->getPubDate(), cmp);
    postsReacts->remove(post->getReactions(), cmp);
}

void Person::showInfo() {
    cout << "-----------------" << endl;
    cout << "Id: " << id << endl;
    cout << "Email: " << email << endl;
    cout << "Name: " << name << endl;
    cout << "Date register: " << date<< endl;
    cout << "-----------------" << endl;
    cout << "***** POSTS *******" << endl;
    postsTitle->inOrderR([&](Post* a, int& cont) {
        a->showInfo();
        cont++;
    });
    cout << "*******************" << endl << endl;
}

void Person::showFollowed() {
    for (List<Person*>::Iterator it = followed.begin(); it != followed.end(); ++it) {
        Person* aux = *it;
        aux->showInfo();
    }
}
#endif