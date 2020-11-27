#ifndef __POST_H__
#define __POST_H__

#include <string>
#include <iostream>
#include "Comment.h"
#include "List.h"
#include "Interaction.h"

using namespace std;

class Post {
private:
    int id, idU, reactions;
    string atName, title, content, pubDate;

    List<Interaction*> interactions;
    List<Comment*> comments;
public:
    Post(int id, int idU, string atName, string title, 
        string content, string pubDate, int reactions = 0) : 
        id(id), idU(idU), atName(atName), title(title), content(content), 
        pubDate(pubDate), reactions(reactions) {}

    ~Post() {}

    List<Comment*>* getComments();
    List<Interaction*>* getInteractions();

    int getId();
    int getIdU();
    string getAtName();
    string getTitle();
    string getContent();
    int getReactions();
    string getPubDate();
    int getRelevance();

    //void addComment(int idUser, int id, int idPud, string date, string content);
    void addComment(int idUser, int idPub, string date, string content, string atName);
    void reaction(int idUser, string date);
    void addInteraction(int idU, int idP, string date, bool share);
    void showInfo();
};

int Post::getId() { return id; }
int Post::getIdU() { return idU; }
string Post::getAtName() { return atName; }
string Post::getTitle() { return title; }
string Post::getContent() { return content; }
int Post::getReactions() { return reactions; }
string Post::getPubDate() { return pubDate; }
int Post::getRelevance() { return interactions.size(); }

List<Comment*>* Post::getComments() { return &comments; }
List<Interaction*>* Post::getInteractions() { return &interactions; }

/*void Post::addComment(int idUser, int id, int idPub, string date, string content) {
    comments.addLast(new Comment(id, idPub, date, content));
    interactions.addLast(new Interaction(idUser, idPub, date, false));
}*/

void Post::addComment(int idUser, int idPub, string date, string content, string atName) {
    comments.addLast(new Comment(idUser, idPub, date, content, atName));
    interactions.addLast(new Interaction(idUser, idPub, date, false));
}

void Post::reaction(int idUser, string date) { 
    cout << "Have you reacted :D" << endl;
    reactions++;
    interactions.addLast(new Interaction(idUser, id, date, false));
}

void Post::addInteraction(int idU, int idP, string date, bool share) {
    interactions.addLast(new Interaction(idU, idP, date, share));
}

void Post::showInfo() {
    cout << "------------------------------" << endl;
    cout << atName << endl;
    cout << title << endl;
    cout << content << endl;
    cout << pubDate << endl;
    cout << "------------------------------" << endl;
    cout << "REACTIONS (" << reactions << ")    " << "COMMENTS (" << comments.size() << "):" << endl;
    if (comments.size() > 0) cout << "    |--" << endl;
    for (List<Comment*>::Iterator it = comments.begin(); it != comments.end();++it) {
        Comment* aux = *it;
        aux->showInfo(); 
    }
}

#endif