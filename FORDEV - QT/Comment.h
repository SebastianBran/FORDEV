#ifndef COMMENT_H
#define COMMENT_H

#include <QString>

class Comment
{
    int id, idPub;
    QString date, content;
public:
    Comment(int id, int idPub, QString date, QString content) :
        id(id), idPub(idPub), date(date), content(content) {}

    int getId();
    int getIdPub();
    QString getDate();
    QString getContent();
};

#endif // COMMENT_H
