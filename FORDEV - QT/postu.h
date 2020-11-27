#ifndef POSTU_H
#define POSTU_H

#include <QString>
#include "List.h"
#include "Interaction.h"
#include "Comment.h"

class PostU
{
    int id, idU, reactions;
    QString atName, title, content, pubDate;

    List<Interaction*> interactions;
    List<Comment*> comments;
public:
    PostU(int id, int idU, QString atName, QString title,
        QString content, QString pubDate, int reactions = 0) :
        id(id), idU(idU), atName(atName), title(title), content(content),
        pubDate(pubDate), reactions(reactions) {}

    List<Comment*>* getComments();
    List<Interaction*>* getInteractions();

    int getId();
    int getIdU();
    QString getAtName();
    QString getTitle();
    QString getContent();
    int getReactions();
    QString getPubDate();
    int getRelevance();

    void addComment(int idUser, int id, int idPud, QString date, QString content);
    void reaction(int idUser, QString date);
    void addInteraction(int idU, int idP, QString date, bool share);
};

#endif // POSTU_H
