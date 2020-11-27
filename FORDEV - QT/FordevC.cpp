#include "FordevC.h"

Fordev_::~Fordev_() {
    //saveInfo();
    //persons.~List();
    user->~Person();
}

Person* Fordev_::getUser() { return user; }

AVL<Person*, QString>* Fordev_::getPersons() { return persons; }
AVL<PostU*, QString>* Fordev_::getPostsTitle() { return postsTitle; }
AVL<PostU*, int>* Fordev_::getPostsID() { return postsID; }
AVL<PostU*, QString>* Fordev_::getPostsPubDate() { return postsPubDate; }
AVL<PostU*, int>* Fordev_::getPostsReacts() { return postsReacts; }
AVL<PostU*, int>* Fordev_::getPostsRelev() { return postsRelev; }

bool Fordev_::registerPerson(QString email, QString name, QString date) {
    function<bool(Person*)> cmp = [&](Person* aux) { return aux->getEmail() == email; };
    Person* temp = persons->find(email, cmp);

    if (temp == nullptr) {
        Person* per = new Person(persons->size() + 1, email, name, date);
        persons->add(per);
        personsId->add(per);
        user = per;
        return true;
    }
    else return false;
}

bool Fordev_::login(QString email) {
    function<bool(Person*)> cmp = [&](Person* aux) { return aux->getEmail() == email; };
    Person* per = persons->find(email, cmp);
    if (per != nullptr) {
        user = per;
        return true;
    }
    else return false;
}

void Fordev_::logout() { user = nullptr; }

QString Fordev_::getDate() {
    time_t t = time(0);
    struct tm * now = localtime(&t);
    return QString::number(1900 + now->tm_year) + "-" + QString::number(now->tm_mon + 1) + "-" + QString::number(now->tm_mday);
}

bool Fordev_::addFollowUser(QString email) {
    function<bool(Person*)> cmp = [&](Person* aux) { return aux->getEmail() == email; };
    Person* aux = persons->find(email, cmp);
    if (aux != nullptr) {
        if (email != user->getEmail() && !user->noFollow(email)) {
            user->addFollowed(aux);
            return true;
        }
    }
    return false;
}

bool Fordev_::deleteFollowUser(QString email) {
    function<bool(Person*)> a = [&](Person* per) { return per->getEmail() == email; };
    /*lambda que verifica si estamos siguiendo a la persona a la
    que queremos eliminar*/
    if (user->getFollowed()->cmp(a)) {
        user->getFollowed()->removePos(user->getFollowed()->searchPos(a));
        return true;
    }
    else return false;
}

void Fordev_::addPost(QString title, QString content, QString date) {
    int id = postsTitle->size() + 1;
    PostU* post = new PostU(id, user->getId(), user->getName(), title, content, date);

    user->addPost(post);
    postsTitle->add(post);
    postsID->add(post);
    postsPubDate->add(post);
    postsReacts->add(post);
    postsRelev->add(post);
}

void Fordev_::addComment(QString title, QString content, QString date) {
    function<bool(PostU*)> cmp = [&](PostU* aux) { return aux->getTitle() == title; };
    PostU* post = postsTitle->find(title, cmp);

    function<bool(PostU*)> cmp2 = [&](PostU* aux) { return aux->getId() == post->getId(); };
    Person* per = personsId->find(post->getIdU(), [&](Person* aux) {
            return aux->getId() == post->getIdU();
        });

    postsTitle->remove(post->getTitle(), cmp2);
    postsPubDate->remove(post->getPubDate(), cmp2);
    postsReacts->remove(post->getReactions(), cmp2);
    postsID->remove(post->getId(), cmp2);
    postsRelev->remove(post->getRelevance(), cmp2);
    per->removePost(post);

    post->addComment(post->getIdU(), ++idComment, post->getId(), date, content);

    per->addPost(post);
    postsTitle->add(post);
    postsID->add(post);
    postsPubDate->add(post);
    postsReacts->add(post);
    postsRelev->add(post);
}

void Fordev_::reactPost(QString title) {
    function<bool(PostU*)> cmp = [&](PostU* aux) { return aux->getTitle() == title; };
    PostU* post = postsTitle->find(title, cmp);

    function<bool(PostU*)> cmp2 = [&](PostU* aux) { return aux->getId() == post->getId(); };
    Person* per = personsId->find(post->getIdU(), [&](Person* aux) {
            return aux->getId() == post->getIdU();
        });

    postsTitle->remove(post->getTitle(), cmp2);
    postsPubDate->remove(post->getPubDate(), cmp2);
    postsReacts->remove(post->getReactions(), cmp2);
    postsID->remove(post->getId(), cmp2);
    postsRelev->remove(post->getRelevance(), cmp2);
    per->removePost(post);

    post->reaction(user->getId(), getDate());

    per->addPost(post);
    postsTitle->add(post);
    postsID->add(post);
    postsPubDate->add(post);
    postsReacts->add(post);
    postsRelev->add(post);
}

void Fordev_::sharePost(QString title) {
    function<bool(PostU*)> cmp = [&](PostU* aux) { return aux->getTitle() == title; };
    PostU* post = postsTitle->find(title, cmp);
    int id = postsTitle->size() + 1;

    QString newHeader = user->getName() + " | Repost from: " + post->getAtName() + " |";
    PostU* newPost = new PostU(id, user->getId(), newHeader, post->getTitle(), post->getContent(), getDate());

    user->addPost(newPost);
    postsTitle->add(newPost);
    postsID->add(newPost);
    postsPubDate->add(newPost);
    postsReacts->add(newPost);
    postsRelev->add(newPost);
}

bool Fordev_::searchPost(QString title) {
    function<bool(PostU*)> cmp = [&](PostU* aux) { return aux->getTitle() == title; };
    PostU* p = postsTitle->find(title, cmp);
    if (p != nullptr) return true;
    return false;
}

void Fordev_::setFilterPost(int filterPost) { this->filterPost = filterPost; }
void Fordev_::setWordKey(QString wordKey) { this->wordKey = wordKey; }
void Fordev_::setTypeFilter(int typeFilter) { this->typeFilter = typeFilter; }

void Fordev_::loadComents(int id, int idP, QString date, QString content) {
    function<bool(PostU*)> cmp = [&](PostU* aux) { return aux->getId() == idP; };
    PostU* post = postsID->find(idP, cmp);

    function<bool(PostU*)> cmp2 = [&](PostU* aux) { return aux->getId() == post->getId(); };
    Person* per = personsId->find(post->getIdU(), [&](Person* aux) {
            return aux->getId() == post->getIdU();
        });

    postsTitle->remove(post->getTitle(), cmp2);
    postsPubDate->remove(post->getPubDate(), cmp2);
    postsReacts->remove(post->getReactions(), cmp2);
    postsID->remove(post->getId(), cmp2);
    postsRelev->remove(post->getRelevance(), cmp2);
    per->removePost(post);

    ++idComment;
    post->addComment(post->getIdU(), id, post->getId(), date, content);

    per->addPost(post);
    postsTitle->add(post);
    postsID->add(post);
    postsPubDate->add(post);
    postsReacts->add(post);
    postsRelev->add(post);
}

void Fordev_::loadFollowers(int idU, int idF) {
    function<bool(Person*)> cmp = [&](Person* aux) { return aux->getId() == idU; };
    Person* per1 = personsId->find(idU, cmp);
    function<bool(Person*)> cmp2 = [&](Person* aux) { return aux->getId() == idF; };
    Person* per2 = personsId->find(idF, cmp2);
    per1->addFollowed(per2);
    //////
    function<bool(Person*)> cmp3 = [&](Person* aux) { return aux->getEmail() == per1->getEmail(); };
    Person* per3 = persons->find(per1->getEmail(), cmp3);
    function<bool(Person*)> cmp4 = [&](Person* aux) { return aux->getEmail() == per2->getEmail(); };
    Person* per4 = persons->find(per2->getEmail(), cmp4);
    per3->addFollowed(per4);
}

void Fordev_::loadInteractions(int idU, int idP, QString date, bool share) {
    function<bool(PostU*)> cmp = [&](PostU* aux) { return aux->getId() == idP; };
    PostU* post = postsID->find(idP, cmp);

    function<bool(PostU*)> cmp2 = [&](PostU* aux) { return aux->getId() == post->getId(); };
    Person* per = personsId->find(post->getIdU(), [&](Person* aux) {
            return aux->getId() == post->getIdU();
        });

    postsTitle->remove(post->getTitle(), cmp2);
    postsPubDate->remove(post->getPubDate(), cmp2);
    postsReacts->remove(post->getReactions(), cmp2);
    postsID->remove(post->getId(), cmp2);
    postsRelev->remove(post->getRelevance(), cmp2);
    per->removePost(post);

    post->addInteraction(idU, idP, date, share);

    per->addPost(post);
    postsTitle->add(post);
    postsID->add(post);
    postsPubDate->add(post);
    postsReacts->add(post);
    postsRelev->add(post);

    Person* per2 = personsId->find(idU, [&](Person* aux) {
            return aux->getId() == idU;
        });

    QString atName = per2->getName() + " | Repost from: " + post->getAtName() + " |";
    PostU* newPost = new PostU(per2->getId(), postsID->size() + 1, atName, post->getTitle(), post->getContent(), date);

    per2->addPost(newPost);
    postsTitle->add(newPost);
    postsID->add(newPost);
    postsPubDate->add(newPost);
    postsReacts->add(newPost);
    postsRelev->add(newPost);
}

void Fordev_::loadInfo() {
    /******USERS*******/
    ifstream fileUsers("users.tsv");

    if (!fileUsers.is_open()) { return; }
    string id, email, name, date;

    getline(fileUsers, id, '\t'); getline(fileUsers, email, '\t'); getline(fileUsers, name, '\t'); getline(fileUsers, date);
    while (getline(fileUsers, id, '\t')) {
        getline(fileUsers, email, '\t'); getline(fileUsers, name, '\t'); getline(fileUsers, date);
        persons->add(new Person(stoi(id), QString::fromStdString(email), QString::fromStdString(name), QString::fromStdString(date)));
        personsId->add(new Person(stoi(id), QString::fromStdString(email), QString::fromStdString(name), QString::fromStdString(date)));
    }
    fileUsers.close();
    /*******************/

    /*******POSTS*******/
    ifstream filePublications("publications.tsv");

    if (!filePublications.is_open()) return;

    string idP, idUP, titleP, contentP, pubDateP, reactionsP;

    getline(filePublications, idP, '\t'); getline(filePublications, idUP, '\t');
    getline(filePublications, titleP, '\t'); getline(filePublications, contentP, '\t');
    getline(filePublications, pubDateP, '\t'); getline(filePublications, reactionsP);

    //int cont = 0;
    while (getline(filePublications, idP, '\t')) {
        getline(filePublications, idUP, '\t'); getline(filePublications, titleP, '\t');
        getline(filePublications, contentP, '\t'); getline(filePublications, pubDateP, '\t');
        getline(filePublications, reactionsP);

        function<bool(Person*)> cmp = [&](Person* aux) { return aux->getId() == stoi(idUP); };
        Person* per = personsId->find(stoi(idUP), cmp);
        Person* per2 = persons->find(per->getEmail(), cmp);

        PostU* newP = new PostU(stoi(idP), stoi(idUP), per->getName(), QString::fromStdString(titleP),
                                QString::fromStdString(contentP), QString::fromStdString(pubDateP), stoi(reactionsP));

        per->addPost(newP);
        per2->addPost(newP);

        postsTitle->add(newP);
        postsID->add(newP);
        postsPubDate->add(newP);
        postsReacts->add(newP);
        postsRelev->add(newP);
    }

    filePublications.close();
    /*******************/

    /******COMENTS******/
    ifstream fileComments("comment.tsv");

    if (!fileComments.is_open()) return;

    string idC, idPC, dateC, contentC;

    getline(fileComments, idC, '\t'); getline(fileComments, idPC, '\t');
    getline(fileComments, dateC, '\t'); getline(fileComments, contentC);

    while (getline(fileComments, idC, '\t')) {
        getline(fileComments, idPC, '\t'); getline(fileComments, dateC, '\t');
        getline(fileComments, contentC);

        loadComents(stoi(idC), stoi(idPC), QString::fromStdString(dateC), QString::fromStdString(contentC));
    }

    fileComments.close();
    /*******************/

    /*****FOLLOWERS*****/
    string idUF, idFF;

    ifstream fileFollowers("followers.tsv");

    if (!fileFollowers.is_open()) return;

    getline(fileFollowers, idUF, '\t'); getline(fileFollowers, idFF);

    while (getline(fileFollowers, idUF, '\t')) {
        getline(fileFollowers, idFF);

        loadFollowers(stoi(idUF), stoi(idFF));
    }

    fileFollowers.close();
    /*******************/

    /****INTERACTION****/
    string idUI, idPI, dateI, shareI;

    ifstream fileInteraction("interaction.tsv");

    if(!fileInteraction.is_open()) return;

    getline(fileInteraction, idUI, '\t'); getline(fileInteraction, idPI, '\t');
    getline(fileInteraction, dateI, '\t'); getline(fileInteraction, shareI);

    while (getline(fileInteraction, idUI, '\t')) {
        getline(fileInteraction, idPI, '\t'); getline(fileInteraction, dateI, '\t'); getline(fileInteraction, shareI);

        if (shareI == "TRUE") loadInteractions(stoi(idUI), stoi(idPI), QString::fromStdString(dateI), true);
    }

    fileInteraction.close();
    /*******************/
}

void Fordev_::saveInfo() {
    /*******USER & FOLLOWERS********/
    ofstream fileUsers("users.tsv");
    ofstream fileFollowers("followers.tsv");

    if (!fileUsers.is_open()) return;
    if (!fileFollowers.is_open()) return;

    fileUsers << "id\temail\tname\tjoindate\n";
    fileFollowers << "idU\tidF\n";

    personsId->inOrder([&](Person* a, int& cont) {
        fileUsers << a->getId() << '\t' << a->getEmail().toStdString() << '\t' << a->getName().toStdString() << '\t' << a->getDate().toStdString() << endl;

        for(List<Person*>::Iterator it = a->getFollowed()->begin(); it != a->getFollowed()->end(); ++it) {
            Person* aux = *it;
            fileFollowers << a->getId() << '\t' << aux->getId() << endl;
        }
    });

    fileUsers.close();
    fileFollowers.close();
    /*******************************/

    /*******POSTS & COMMENTS & INTERACTION*******/
    ofstream filePublications("publications.tsv");
    ofstream fileComments("comment.tsv");
    ofstream fileInteractions("interaction.tsv");

    if (!filePublications.is_open()) return;
    if (!fileComments.is_open()) return;
    if (!fileInteractions.is_open()) return;

    filePublications << "id\tidU\ttitle\tdesc\tpubdate\tnumlikes\n";
    fileComments << "id\tidPub\tdate\ttext\n";
    fileInteractions << "idUser\tidPub\tdate\tshare\n";

    postsID->inOrder([&](PostU* a, int& cont) {
        filePublications << a->getId() << '\t' << a->getIdU() << '\t' << a->getTitle().toStdString() << '\t' << a->getContent().toStdString() << '\t' << a->getPubDate().toStdString() << '\t' << a->getReactions() << endl;

        for (List<Comment*>::Iterator it = a->getComments()->begin(); it != a->getComments()->end();++it) {
            Comment* aux = *it;
            fileComments << aux->getId() << '\t' << aux->getIdPub() << '\t' << aux->getDate().toStdString() << '\t' << aux->getContent().toStdString() << endl;
        }

        for (List<Interaction*>::Iterator it = a->getInteractions()->begin(); it != a->getInteractions()->end(); ++it) {
            Interaction* aux = *it;
            string status = (aux->getShare()) ? "TRUE" : "FALSE";
            fileInteractions << aux->getIdU() << '\t' << aux->getIdP() << '\t' << aux->getDate().toStdString() << '\t' << status << endl;
        }
    });

    filePublications.close();
    fileComments.close();
    fileInteractions.close();
    /**********************************************/
}
