#include "postu.h"

List<Comment*>* PostU::getComments() { return &comments; }
List<Interaction*>* PostU::getInteractions() { return &interactions; }

int PostU::getId() { return id; }
int PostU::getIdU() { return idU; }
QString PostU::getAtName() { return atName; }
QString PostU::getTitle() { return title; }
QString PostU::getContent() { return content; }
int PostU::getReactions() { return reactions; }
QString PostU::getPubDate() { return pubDate; }
int PostU::getRelevance() { return interactions.size(); }

void PostU::addComment(int idUser, int id, int idPub, QString date, QString content) {
    comments.addLast(new Comment(id, idPub, date, content));
    interactions.addLast(new Interaction(idUser, idPub, date, false));
}

void PostU::reaction(int idUser, QString date) {
    reactions++;
    interactions.addLast(new Interaction(idUser, id, date, false));
}

void PostU::addInteraction(int idU, int idP, QString date, bool share) {
    interactions.addLast(new Interaction(idU, idP, date, share));
}
