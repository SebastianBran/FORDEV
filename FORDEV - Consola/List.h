#ifndef __LIST_H__
#define __LIST_H__

#include <functional>

using namespace std;

template <typename T>
class List {
    struct Node;
    int len;

    Node* head;
    Node* last;
public:
    List () : len(0), head(nullptr), last(nullptr) {}
    ~List ();

    class Iterator {
        int i;
        Node* aux;
    public:
        Iterator(int i = 0, Node* aux = nullptr) : i(i), aux(aux) {}

        void operator ++ () { i++; aux = aux->next; }
        void operator -- () { i--; aux = aux->prev; }
        bool operator != (Iterator it) { return i != it.i; }
        T operator * () { return aux->elem; }
    };

    Iterator begin() { return Iterator(0, head); }
    Iterator end() { return Iterator(len, last); }

    int size();
    bool empty();
    
    void addFirst(T elem);
    void addPos(T elem, int pos);
    void addLast(T elem);

    void removeFirst();
    void removePos(int pos);
    void removeLast();

    bool cmp(function<bool(T)> a);
    T search(function<bool(T)> a);
    int searchPos(function<bool(T)> a);
};

template <typename T>
struct List<T>::Node {
    T elem;
    Node* next;
    Node* prev;

    Node(T elem, Node* next = nullptr, Node* prev = nullptr) : elem(elem), next(next), prev(prev) {}
};

template <typename T>
int List<T>::size() { return len; }

template <typename T>
bool List<T>::empty() { return len == 0;}

template <typename T>
List<T>::~List () {
    while (head != nullptr) {
        Node* aux = head;
        head = head->next;
        delete aux;
    }
}

template <typename T>
void List<T>::addFirst (T elem) {
    head = new Node(elem, head, nullptr);
    if (len == 0) last = head;
    else head->next->prev = head;
    len++;
}

template <typename T>
void List<T>::addLast (T elem) {
    last = new Node(elem, nullptr, last);
    if (len == 0) head = last;
    else last->prev->next = last;
    len++;
}

template <typename T>
void List<T>::addPos (T elem, int pos) {
    if (pos < 0 || pos > len) return;
    else if (pos == 0) addFirst(elem);
    else if (pos == len) addLast(elem);
    else {
        Node* aux = head;
        for (int i = 1; i < pos; i++) {
            aux = aux->next;
        }
        aux->next = new Node(elem, aux->next, aux);
        aux->next->next->prev = aux->next;
        len++;
    }
}

template <typename T>
void List<T>::removeFirst () {
    if (len > 0) {
        Node* aux = head;
        head = head->next;
        delete aux;
        len--;
    }
}

template <typename T>
void List<T>::removeLast() {
    if (len > 0) {
        Node* aux = last;
        last = last->prev;
        last->next = nullptr;
        delete aux;
        len--;
    }
}

template <typename T>
void List<T>::removePos(int pos) {
    if (pos < 0 || pos >= len) return;
    else if (pos == 0) removeFirst();
    else if (pos == len - 1) removeLast();
    else {
        Node* aux = head;
        for (int i = 1; i < pos; i++) {
            aux = aux->next;
        }
        Node* aux2 = aux->next;
        aux->next = aux2->next;
        aux2->next->prev = aux;
        delete aux2;
        len--;
    }
}

template <typename T>
bool List<T>::cmp(function<bool(T)> a) {
    Node* aux = head;
    for (int i = 0; i < len; i++) {
        if (a(aux->elem)) {
            return true;
        }
        aux = aux->next;
    }

    return false;
}

template <typename T>
T List<T>::search(function<bool(T)> a) {
    Node* aux = head;
    for (int i = 0; i < len; i++) {
        if  (a(aux->elem)) {
            return aux->elem;
        }
        aux = aux->next;
    }

    return nullptr;
}

template <typename T>
int List<T>::searchPos(function<bool(T)> a) {
    Node* aux = head;
    for (int i = 0; i < len; i++) {
        if  (a(aux->elem)) {
            return i;
        }
        aux = aux->next;
    }

    return -1;
}

#endif