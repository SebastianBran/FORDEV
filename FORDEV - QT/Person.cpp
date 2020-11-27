#include "Person.h"

Person::~Person() {
    followed.~List();
}

void Person::setId(int id) { this->id = id; }
void Person::setName(QString name) { this->name = name; }
void Person::setEmail(QString email) { this->email = email; }
void Person::setDate(QString date) { this->date = date; }

int Person::getId() { return id; }
QString Person::getEmail() { return email; }
QString Person::getName() { return name; }
QString Person::getDate() { return date; }

List<Person*>* Person::getFollowed() { return &followed; }

/**AVLS**/
AVL<PostU*, QString>* Person::getPostsTitle() { return postsTitle; }
AVL<PostU*, QString>* Person::getPostsPubDate() { return postsPubDate; }
AVL<PostU*, int>* Person::getPostsReacts() { return postsReacts; }
/********/

void Person::addFollowed(Person* a) { followed.addLast(a); }
bool Person::noFollow(QString email) {
    function<bool(Person*)> a = [&](Person* per) { return email == per->getEmail(); };
    return followed.cmp(a);
}

void Person::addPost(PostU* post) {
    postsTitle->add(post);
    postsPubDate->add(post);
    postsReacts->add(post);
}

void Person::removePost(PostU* post) {
    function<bool(PostU*)> cmp = [&](PostU* aux) { return aux->getId() == post->getId(); };
    postsTitle->remove(post->getTitle(), cmp);
    postsPubDate->remove(post->getPubDate(), cmp);
    postsReacts->remove(post->getReactions(), cmp);
}
