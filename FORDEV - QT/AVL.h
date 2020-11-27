#ifndef AVL_H
#define AVL_H

#include <functional>

using namespace std;

template <typename T, typename R = T, T NADA = nullptr>
class AVL {
    struct Node {
        T elem;
        Node* left;
        Node* right;
        int height;
        Node (T elem) : elem(elem) , left(nullptr), right(nullptr), height(0) {}
    };

    typedef function<R(T)> ldKey;
    typedef function<void(T, int&)> ldProc;
    typedef function<bool(T)> ldCmp;

    int cont;
    Node* root;
    int len;
    ldKey key;
public:
    AVL (ldKey key = [](T aux) { return aux; }) : key(key), root(nullptr), len(0) {}
    ~AVL() { destroy(root); }

    int height() { return height(root); }
    int size() { return len; }
    void clear() { destroy(root); len = 0; }

    void add(T elem) { add(root, elem); }
    void inOrder(ldProc proc) { cont = 0; inOrder(root, proc); }
    void inOrderR(ldProc proc) { cont = 0; inOrderR(root, proc); }

    void remove(R atrib, ldCmp cmp) { remove(root, atrib, cmp); }

    T find(R atrib, ldCmp cmp) {
        Node*& node = find(root, atrib, cmp);
        return (node == nullptr) ? NADA : node->elem;
    }
private:
    void destroy(Node*& node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
            node = nullptr;
        }
    }

    int height(Node* node) { return node == nullptr? -1: node->height; }

    void add(Node*& node, T elem) {
        if (node == nullptr) {
            node = new Node(elem);
            ++len;
        } else {
            if (key(elem) < key(node->elem)) add(node->left, elem);
            else add(node->right, elem);
            balance(node);
        }
    }

    void remove(Node*& node, R atrib, ldCmp cmp) {
        if (node != nullptr) {
            if (atrib == key(node->elem) && cmp(node->elem)) {
                if (node->left == nullptr) {
                    Node* aux = node;
                    node = node->right;
                    delete aux;
                    len--;
                }
                else {
                    Node*& temp = greater(node->left);
                    node->elem = temp->elem;
                    Node* aux = temp;
                    temp = temp->left;
                    delete aux;
                    len--;
                }
            }
            else {
                if (atrib <= key(node->elem)) remove(node->left, atrib, cmp);
                if (atrib >= key(node->elem)) remove(node->right, atrib, cmp);
                balance(node);
            }
        }
    }

    Node*& greater(Node*& node) {
        if (node->right == nullptr) return node;
        else return greater(node->right);
    }

    void inOrder(Node* node, ldProc proc) {
        if (node != nullptr && cont < 5) {
            inOrder(node->left, proc);
            proc(node->elem, cont);
            inOrder(node->right, proc);
        }
    }

    void inOrderR(Node* node, ldProc proc) {
        if (node != nullptr && cont < 30) {
            inOrderR(node->right, proc);
            proc(node->elem, cont);
            inOrderR(node->left, proc);
        }
    }

    Node* non_existing = nullptr;

    Node*& find(Node*& node, R atrib, ldCmp cmp) {
        if (node == nullptr) return non_existing;
        else if (atrib == key(node->elem) && cmp(node->elem)) return node;
        else if (atrib < key(node->elem)) return find(node->left, atrib, cmp);
        else return find(node->right, atrib, cmp);
    }

    void updateHeight(Node* node) {
        if (node != nullptr) node->height = max(height(node->left), height(node->right)) + 1;
    }

    void rotateLeft(Node*& node) {
        Node* aux = node->right;
        node->right = aux->left;
        updateHeight(node);
        aux->left = node;
        updateHeight(aux);
        node = aux;
    }

    void rotateRight(Node*& node) {
        Node* aux = node->left;
        node->left = aux->right;
        updateHeight(node);
        aux->right = node;
        updateHeight(aux);
        node = aux;
    }

    void balance(Node*& node) {
        int hl = height(node->left);
        int hr = height(node->right);

        if (hr - hl < -1) {
            hl = height(node->left->left);
            hr = height(node->left->right);
            if (hr > hl) rotateLeft(node->left);
            rotateRight(node);
        } else if (hr - hl > 1) {
            hl = height(node->right->left);
            hr = height(node->right->right);
            if (hl > hr) rotateRight(node->right);
            rotateLeft(node);
        } else updateHeight(node);
    }
};

#endif
