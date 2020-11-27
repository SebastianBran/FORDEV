#ifndef __FORDEV_H__
#define __FORDEV_H__

#include "Person.h"
#include <functional>
#include <string.h>
#include <string>
#include "AVL.h"
#include "Post.h"
#include <fstream>
#include <chrono>

using std::chrono::system_clock;

class Fordev {
    AVL<Person*, string>* persons = new AVL<Person*, string>([](Person* a) { return a->getEmail();});
    AVL<Person*, int>* personsId = new AVL<Person*, int>([](Person* a) { return a->getId();});
    //
    AVL<Post*, string>* postsTitle = new AVL<Post*, string>([](Post* a) { return a->getTitle(); }); // arbol organizado por el titulo de publicacion alfabeticamente
    AVL<Post*, int>* postsID = new AVL<Post*, int>([](Post* a) { return a->getId(); }); //arbol organizado por los ids de las publicaciones
    AVL<Post*, string>* postsPubDate = new AVL<Post*, string>([](Post* a) { return a->getPubDate(); }); //arbol organizado por las fechas de publicacion
    AVL<Post*, int>* postsReacts = new AVL<Post*, int>([](Post* a) { return a->getReactions(); }); //arbol organizado por la cantidad de reacciones
    AVL<Post*, int>* postsRelev = new AVL<Post*, int>([](Post* a) { return a->getRelevance(); }); //arbol organizado por la relevancia
    //
    int idComment = 0;
    int filterPost, typeFilter;
    string wordKey;
    Person* user;
public:
    Fordev() : user(nullptr), filterPost(1), typeFilter(1) { loadInfo(); }
    ~Fordev();

    Person* getUser();

    bool registerPerson(string name, string email, string date);
    bool login(string email);
    void logout();

    string getDate();
    
    /**USER**/
    void infoUser();
    void showUsers();
    void showPersons();
    void showBiografyPerson(string email);

    void addFollowUser(string email);
    void deleteFollowUser(string email);

    /**POSTS**/
    void addPost(string title, string content, string date);
    void addComment(string title, string content, string date);
    void reactPost(string title);
    void sharePost(string title);
    bool searchPost(string title);
    void showPosts();
    void setFilterPost(int filterPost);
    void setWordKey(string wordKey);
    void setTypeFilter(int typeFilter);
    void showBiography(string email);
    
    /**INFORMATION**/
    void saveInfo();
    void loadInfo();
    void loadComents(int id, int idPub, string date, string content);
    void loadFollowers(int idU, int idF);
    void loadInteractions(int idU, int idP, string date, bool share);
};

Fordev::~Fordev() {
    saveInfo();
    user->~Person();
    persons->~AVL();
    personsId->~AVL();
    postsTitle->~AVL();
    postsID->~AVL();
    postsPubDate->~AVL();
    postsReacts->~AVL();
    postsRelev->~AVL();
}

Person* Fordev::getUser() { return user; }

bool Fordev::registerPerson(string email, string name, string date) {
    function<bool(Person*)> cmp = [&](Person* aux) { return aux->getEmail() == email; };
    Person* temp = persons->find(email, cmp);

    if (temp == nullptr) {
        Person* per = new Person(persons->size() + 1, email, name, date);
        persons->add(per);
        personsId->add(per);
        user = per;
        return true;
    }
    else {
        cout << "That email is not available :(" << endl;
        return false;
    }
}

bool Fordev::login(string email) {
    function<bool(Person*)> cmp = [&](Person* aux) { return aux->getEmail() == email; };
    Person* per = persons->find(email, cmp);
    if (per != nullptr) {
        user = per;
        return true;
    }
    else {
        cout << "Email or password invalid" << endl;
        return false;
    }
}

void Fordev::logout() { user = nullptr; }

string Fordev::getDate() {
    time_t t = time(0);
    struct tm * now = localtime(&t);
    return to_string(1900 + now->tm_year) + "-" + to_string(now->tm_mon + 1) + "-" + to_string(now->tm_mday);
}

/**USER**/
void Fordev::infoUser() {
    user->showInfo();
    cout << endl;
}

void Fordev::showUsers() {
    persons->inOrder([&](Person* a, int& cont) { 
        if (a->getEmail() != user->getEmail()) {
            cout << a->getName() << " " << a->getEmail() << endl;
            cont++;
        }    
    });
}

void Fordev::showPersons() {
    persons->inOrder([&](Person* a, int& cont) { a->showInfo(); cont++; });
}

void Fordev::showBiografyPerson(string email) {
    function<bool(Person*)> cmp = [&](Person* aux) { return aux->getEmail() == email; };
    Person* per = persons->find(email, cmp);
    if (per != nullptr) per->showInfo();
    else cout << "Person not found :(" << endl;
}

void Fordev::addFollowUser(string email) {
    function<bool(Person*)> cmp = [&](Person* aux) { return aux->getEmail() == email; };
    Person* aux = persons->find(email, cmp);
    if (aux != nullptr) {
        if (email != user->getEmail() && !user->noFollow(email)) {
            user->addFollowed(aux);
            cout << "Followed user :D" << endl;
        }
    }
    else cout << "Email invalid :(" << endl;
}

void Fordev::deleteFollowUser(string email) {
    function<bool(Person*)> a = [&](Person* per) { return per->getEmail() == email; };
    /*lambda que verifica si estamos siguiendo a la persona a la
    que queremos eliminar*/

    if (user->getFollowed()->cmp(a)) {
        user->getFollowed()->removePos(user->getFollowed()->searchPos(a));
    }
    else {
        cout << "Email invalid :(" << endl;
    }
}

/**POSTS**/
void Fordev::addPost(string title, string content, string date) {
    int id = postsTitle->size() + 1;
    Post* post = new Post(id, user->getId(), user->getName(), title, content, date);

    user->addPost(post);
    postsTitle->add(post);
    postsID->add(post);
    postsPubDate->add(post);
    postsReacts->add(post);
    postsRelev->add(post);
}

void Fordev::addComment(string title, string content, string date) {
    function<bool(Post*)> cmp = [&](Post* aux) { return aux->getTitle() == title; };
    Post* post = postsTitle->find(title, cmp);

    function<bool(Post*)> cmp2 = [&](Post* aux) { return aux->getId() == post->getId(); };
    Person* per = personsId->find(post->getIdU(), [&](Person* aux) { 
            return aux->getId() == post->getIdU();
        });

    postsTitle->remove(post->getTitle(), cmp2);
    postsPubDate->remove(post->getPubDate(), cmp2);
    postsReacts->remove(post->getReactions(), cmp2);
    postsID->remove(post->getId(), cmp2);
    postsRelev->remove(post->getRelevance(), cmp2);
    per->removePost(post);

    //post->addComment(post->getIdU(), ++idComment, post->getId(), date, content);
    post->addComment(user->getId(), post->getId(), date, content, user->getName());

    per->addPost(post);
    postsTitle->add(post);
    postsID->add(post);
    postsPubDate->add(post);
    postsReacts->add(post);
    postsRelev->add(post);
}

void Fordev::sharePost(string title) {
    function<bool(Post*)> cmp = [&](Post* aux) { return aux->getTitle() == title; };
    Post* post = postsTitle->find(title, cmp);
    int id = postsTitle->size() + 1;

    string newHeader = user->getName() + " | Repost from: " + post->getAtName() + " |";
    Post* newPost = new Post(id, user->getId(), newHeader, post->getTitle(), post->getContent(), getDate());
    newPost->addInteraction(user->getId(), newPost->getId(), getDate(), true);

    user->addPost(newPost);
    postsTitle->add(newPost);
    postsID->add(newPost);
    postsPubDate->add(newPost);
    postsReacts->add(newPost);
    postsRelev->add(newPost);

    cout << "Post shared 7u7" << endl;
}

void Fordev::reactPost(string title) {
    function<bool(Post*)> cmp = [&](Post* aux) { return aux->getTitle() == title; };
    Post* post = postsTitle->find(title, cmp);

    function<bool(Post*)> cmp2 = [&](Post* aux) { return aux->getId() == post->getId(); };
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

bool Fordev::searchPost(string title) {
    function<bool(Post*)> cmp = [&](Post* aux) { return aux->getTitle() == title; };
    Post* p = postsTitle->find(title, cmp);
    if (p != nullptr) return true;
    cout << "Post not found :(" << endl;
    return false;
}

void Fordev::showBiography(string email) {
    function<bool(Person*)> cmp = [&](Person* aux) { return aux->getEmail() == email; };
    Person* per = persons->find(email, cmp);
    if (per != nullptr) {
        per->showInfo();
    } else{
        cout << "Person not found :(" << endl;
    }
}

void Fordev::setFilterPost(int filterPost) { this->filterPost = filterPost; }
void Fordev::setWordKey(string wordKey) { this->wordKey = wordKey; }
void Fordev::setTypeFilter(int typeFilter) { this->typeFilter = typeFilter; }

void Fordev::showPosts() {  
    cout << "Trends: ";
    if (filterPost == 1) cout << "Recent activity" << endl;
    else if (filterPost == 2) cout << "Likes" << endl;
    else if (filterPost == 3) cout << "Relevance" << endl;

    cout << "Filter: ";
    if (typeFilter == 1) cout << "None" << endl;
    else if (typeFilter == 2) cout << "Equal to " << wordKey << endl; 
    else if (typeFilter == 3) cout << "Start with " << wordKey << endl;
    else if (typeFilter == 4) cout << "Finish with " << wordKey << endl;
    else if (typeFilter == 5) cout << "Contained in " << wordKey << endl;
    else if (typeFilter == 6) cout << "Not contained in " << wordKey << endl;

    cout << "***** POSTS *******" << endl;

    function<void(Post*, int&)> b;

    if (typeFilter == 1) {
        b = [&](Post* a, int& cont) { a->showInfo(); cont++; };
    } else if (typeFilter == 2) {
        b = [&](Post* a, int& cont) { 
            if (a->getTitle() == wordKey) { a->showInfo(); cont++; }
        };
    } else if (typeFilter == 3) {
        b = [&](Post* a, int& cont) {
            bool es = true;
            for (int i = 0; i < min(wordKey.size(), a->getTitle().size()); i++) {
                if (wordKey[i] != a->getTitle()[i]) {
                    es = false;
                    break;
                }
            }
            if (es) {
                a->showInfo();
                cont++;
            }
        };
    } else if (typeFilter == 4) {
        b = [&](Post* a, int& cont) {
            bool es = true;
            for (int i = wordKey.size() - 1, j = a->getTitle().size() - 1; i >= 0 && j >= 0; i--, j--) {
                if (wordKey[i] != a->getTitle()[j]) {
                    es = false;
                    break;
                }
            }
            if (es) {
                a->showInfo();
                cont++;
            }
        };
    } else if (typeFilter == 5) {
        b = [&](Post* a, int& cont) {
            bool es = true;
            auto it = a->getTitle().find(wordKey);
            if (it != string::npos) { 
                a->showInfo(); cont++; 
                cont++;
            }
        };
    }
    else if (typeFilter == 6) {
        b = [&](Post* a, int& cont) {
            bool es = true;
            auto it = a->getTitle().find(wordKey);
            if (it == string::npos) {
                a->showInfo();
                cont++;
            }
        };
    }

    if (filterPost == 1) postsPubDate->inOrderR(b);
    else if (filterPost == 2) postsReacts->inOrderR(b);
    else if (filterPost == 3) postsRelev->inOrderR(b);
    cout << "*******************" << endl << endl;
}

////////////////////INFORMATION/////////////////////////

void Fordev::loadComents(int idU, int idP, string date, string content) {
    function<bool(Post*)> cmp = [&](Post* aux) { return aux->getId() == idP; };
    Post* post = postsID->find(idP, cmp);

    function<bool(Post*)> cmp2 = [&](Post* aux) { return aux->getId() == post->getId(); };
    Person* per = personsId->find(post->getIdU(), [&](Person* aux) { 
            return aux->getId() == post->getIdU();
        });
    Person* per2 = personsId->find(idU, [&](Person* aux) { 
            return aux->getId() == idU;
        });    

    postsTitle->remove(post->getTitle(), cmp2);
    postsPubDate->remove(post->getPubDate(), cmp2);
    postsReacts->remove(post->getReactions(), cmp2);
    postsID->remove(post->getId(), cmp2);
    postsRelev->remove(post->getRelevance(), cmp2);
    per->removePost(post);

    //post->addComment(post->getIdU(), id, post->getId(), date, content);
    post->addComment(idU, idP, date, content, per2->getName());

    per->addPost(post);
    postsTitle->add(post);
    postsID->add(post);
    postsPubDate->add(post);
    postsReacts->add(post);
    postsRelev->add(post);
}

void Fordev::loadFollowers(int idU, int idF) {
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

void Fordev::loadInteractions(int idU, int idP, string date, bool share) {
    function<bool(Post*)> cmp = [&](Post* aux) { return aux->getId() == idP; };
    Post* post = postsID->find(idP, cmp);

    function<bool(Post*)> cmp2 = [&](Post* aux) { return aux->getId() == post->getId(); };
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

    string atName = per2->getName() + " | Repost from: " + post->getAtName() + " |";
    Post* newPost = new Post(per2->getId(), postsID->size() + 1, atName, post->getTitle(), post->getContent(), date);

    per2->addPost(newPost);
    postsTitle->add(newPost);
    postsID->add(newPost);
    postsPubDate->add(newPost);
    postsReacts->add(newPost);
    postsRelev->add(newPost);
}

void Fordev::loadInfo() {
    /******USERS*******/
    ifstream fileUsers("users.tsv");

    if (!fileUsers.is_open()) { return; }
    string id, email, name, date;

    getline(fileUsers, id, '\t'); getline(fileUsers, email, '\t'); getline(fileUsers, name, '\t'); getline(fileUsers, date);
    while (getline(fileUsers, id, '\t')) {
        getline(fileUsers, email, '\t'); getline(fileUsers, name, '\t'); getline(fileUsers, date);
        persons->add(new Person(stoi(id), email, name, date));
        personsId->add(new Person(stoi(id), email, name, date));
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

        Post* newP = new Post(stoi(idP), stoi(idUP), per->getName(), 
                        titleP, contentP, pubDateP, stoi(reactionsP));
        
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
    ifstream fileComments("comments.tsv");

    if (!fileComments.is_open()) return;

    string idUC, idPC, dateC, contentC;

    getline(fileComments, idUC, '\t'); getline(fileComments, idPC, '\t');
    getline(fileComments, dateC, '\t'); getline(fileComments, contentC);

    while (getline(fileComments, idUC, '\t')) {
        getline(fileComments, idPC, '\t'); getline(fileComments, dateC, '\t'); 
        getline(fileComments, contentC);

        loadComents(stoi(idUC), stoi(idPC), dateC, contentC);
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

        if (shareI == "TRUE") loadInteractions(stoi(idUI), stoi(idPI), dateI, true);
    }

    fileInteraction.close();
    /*******************/
}

void Fordev::saveInfo() {
    /*******USER & FOLLOWERS********/
    ofstream fileUsers("users.tsv");
    ofstream fileFollowers("followers.tsv");

    if (!fileUsers.is_open()) return;
    if (!fileFollowers.is_open()) return;

    fileUsers << "id\temail\tname\tjoindate\n";
    fileFollowers << "idU\tidF\n";

    personsId->inOrder([&](Person* a, int& cont) { 
        fileUsers << a->getId() << '\t' << a->getEmail() << '\t' << a->getName() << '\t' << a->getDate() << endl;

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
    ofstream fileComments("comments.tsv");
    ofstream fileInteractions("interaction.tsv");

    if (!filePublications.is_open()) return;
    if (!fileComments.is_open()) return;
    if (!fileInteractions.is_open()) return;

    filePublications << "id\tidU\ttitle\tdesc\tpubdate\tnumlikes\n";
    fileComments << "idUser\tidPub\tdate\ttext\n";
    fileInteractions << "idUser\tidPub\tdate\tshare\n";

    postsID->inOrder([&](Post* a, int& cont) {
        filePublications << a->getId() << '\t' << a->getIdU() << '\t' << a->getTitle() << '\t' << a->getContent() << '\t' << a->getPubDate() << '\t' << a->getReactions() << endl;

        for (List<Comment*>::Iterator it = a->getComments()->begin(); it != a->getComments()->end();++it) {
            Comment* aux = *it;
            fileComments << aux->getIdU() << '\t' << aux->getIdPub() << '\t' << aux->getDate() << '\t' << aux->getContent() << endl;
        }

        for (List<Interaction*>::Iterator it = a->getInteractions()->begin(); it != a->getInteractions()->end(); ++it) {
            Interaction* aux = *it;
            string status = (aux->getShare()) ? "TRUE" : "FALSE";
            fileInteractions << aux->getIdU() << '\t' << aux->getIdP() << '\t' << aux->getDate() << '\t' << status << endl;
        } 
    });

    filePublications.close();
    fileComments.close();
    fileInteractions.close();
    /**********************************************/
}

#endif