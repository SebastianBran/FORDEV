#ifndef __STACK_H__
#define __STACK_H__

template <typename T>
class Stack {
    struct Node;

    int len;
    Node* head;
public:
    Stack() : len(0), head(nullptr) {}
    ~Stack();
    
    class Iterator {
    	int i;
    	Node* aux;
	public:
		Iterator(int i = 0, Node* aux = nullptr) : i(i), aux(aux) {}
		
		void operator ++ () { i++; aux = aux->prev; }
		bool operator != (Iterator it) { return i != it.i; }
		T operator * () { return aux->elem; }
	};
	
	Iterator begin() { return Iterator(0, head); }
    Iterator end() { return Iterator(len, nullptr); }

    int size();
    bool empty();

    void push(T elem);
    void pop();
    T top();
};

template <typename T>
struct Stack<T>::Node {
    T elem;
    Node* prev;

    Node(T elem, Node* prev = nullptr) : elem(elem), prev(prev) {}
};

template <typename T>
Stack<T>::~Stack() {
    while (head != nullptr) {
        Node* aux = head;
        head = head->prev;
        delete aux;
    }
}

template <typename T>
int Stack<T>::size() { return len; }

template <typename T>
bool Stack<T>::empty() { return len == 0; }

template <typename T>
void Stack<T>::push (T elem) {
    head = new Node(elem, head);
    len++;
}

template <typename T>
void Stack<T>::pop () {
    if (len > 0) {
        Node* aux = head;
        head = head->prev;
        delete aux;
        len--;
    }
}

template <typename T>
T Stack<T>::top () {
    return head->elem;
}

#endif