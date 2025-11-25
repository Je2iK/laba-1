#include <iostream>
#include <fstream>
#include <sstream>
#include "include/brt.h"
using namespace std;
//Узел может быть либо красным, либо чёрным и имеет двух потомков;
//Корень — как правило чёрный. Это правило слабо влияет на работоспособность модели, так как цвет корня всегда можно изменить с чёрного на красный;
//Все листья, не содержащие данных — чёрные.
//Оба потомка каждого красного узла — чёрные.
//Любой простой путь от узла-предка до листового узла-потомка содержит одинаковое число чёрных узлов.

node_colors BRT::colorOf(Node* n){
    return n ? n->color : BLACK;
}
Node* BRT::findNode(int key){
    Node* cur = root;
    while(cur){
        if(key == cur->key) return cur;
        else if(key < cur->key) cur = cur->l;
        else cur = cur->r;
    }
    return nullptr;
}
Node* BRT::minimum(Node* n){
    if(!n) return nullptr;
    while(n->l) n = n->l;
    return n;
}
void BRT::brtInsert(int key){
    if (findNode(key) != nullptr) {
    cout << "Ключ " << key << " уже существует, пропускаем вставку.\n";
    return;
}

    Node* n = new Node(key);
    n->l = n->r = nullptr; // parent не обнуляем
    
    if (!root) {
        root = n;
    } else {
        Node* cur = root;
        Node* parent = nullptr;

        while (cur) {
            parent = cur;
            if (key < cur->key)
                cur = cur->l;
            else
                cur = cur->r;
        }

        n->parent = parent;
        if (key < parent->key)
            parent->l = n;
        else
            parent->r = n;
    }

    insertCase1(n);
}

void BRT::inorder(){
    inorderRec(root);
    cout << endl;
}

void BRT::inorderRec(Node* n){
    if(!n) return;
    inorderRec(n->l);
    cout << n->key << (n->color == RED ? "R " : "B ");
    inorderRec(n->r);
}
void BRT::brtRemove(int key){
    Node* n = findNode(key);
    if (!n) return;

    if (n->l && n->r){
        Node* succ = minimum(n->r);
        n->key = succ->key;
        n = succ;
    }

    Node* child = (n->l) ? n->l : n->r;

    if (child != nullptr)
        child->parent = n->parent;

    if (n->parent == nullptr)
        root = child;
    else if (n == n->parent->l)
        n->parent->l = child;
    else
        n->parent->r = child;

    if (colorOf(n) == BLACK){
        if (child && colorOf(child) == RED)
            child->color = BLACK;
        else
            deleteCase1(child ? child : n); // начинаем корректировку
    }

    delete n;
}

Node* BRT::grandparent(Node* n){
    if((n != nullptr) && (n->parent != nullptr)) return n->parent->parent;
    else return nullptr;
}
Node* BRT::uncle(Node* n){
    Node *g = grandparent(n);
    if(g == nullptr) return nullptr;
    if(n->parent == g->l) return g->r;
    else return g->l;
}
Node* BRT::brother(Node* n){
    if (!n || !n->parent) return nullptr;
    return (n == n->parent->l) ? n->parent->r : n->parent->l;
}
void BRT::rotateLeft(Node* n){
    Node *pivot = n->r;
    if(pivot == nullptr) return; // защита
    // перенос
    pivot->parent = n->parent;
    if(n->parent != nullptr){
        if(n->parent->l == n) n->parent->l = pivot;
        else n->parent->r = pivot;
    } else {
        // pivot теперь корень
        root = pivot;
    }
    n->r = pivot->l;
    if (pivot->l != nullptr) pivot->l->parent = n;
    n->parent = pivot;
    pivot->l = n;

}
void BRT::rotateRight(Node* n){
    Node *pivot = n->l;
    if(pivot == nullptr) return; // защита
    pivot->parent = n->parent;
    if(n->parent != nullptr){
        if(n->parent->l == n) n->parent->l = pivot;
        else n->parent->r = pivot;
    } else {
        // pivot теперь корень
        root = pivot;
    }
    n->l = pivot->r;
    if (pivot->r != nullptr) pivot->r->parent = n;
    n->parent = pivot;
    pivot->r = n;
}
void BRT::insertCase1(Node* n){ // корень должен быть чёрным
    if(n->parent == nullptr) n->color = BLACK;
    else insertCase2(n);
}
void BRT::insertCase2(Node* n){ // родитель чёрный иначе идём дальше
    if(n->parent->color == BLACK) return;
    else insertCase3(n);
}
void BRT::insertCase3(Node* n){ //Родитель красный, дядя красный, меняем на чёрный, предка перекрашиваем в красный
    Node *u = uncle(n), *g;
    if((u != nullptr) && (u->color == RED)){
        n->parent->color = BLACK;
        u->color = BLACK;
        g = grandparent(n);
        g->color = RED;
        insertCase1(g);
    }
    else insertCase4(n);

}
void BRT::insertCase4(Node* n){ //родитель красный дядя чёрный - поворачиваем узлы
    Node *g = grandparent(n);
    if ((n == n->parent->r) && (n->parent == g->l)){
        rotateLeft(n->parent);
        n = n->l;
    }
    else if ((n == n->parent->l) && (n->parent == g->r)){
        rotateRight(n->parent);
        n = n->r;
    }
    insertCase5(n);
}
void BRT::insertCase5(Node* n){ //родитель красный дядя чёрный, поворачиваем предка
    Node *g = grandparent(n);
    n->parent->color = BLACK;
    g->color = RED;
    // если parent — левый ребёнок grandparent => rotateRight(g) (LL)
    if(n->parent == g->l) rotateRight(g); 
    else rotateLeft(g);
}
void BRT::replace_node(Node* n, Node* child){
    if(child) child->parent = n->parent;
    if (n->parent == nullptr) {
        // n был корнем
        root = child;
    } else if (n == n->parent->l) {
        n->parent->l = child;
    } else {
        n->parent->r = child;
    }
}
void BRT::deleteCase1(Node* n){ //
    if(n->parent != nullptr) deleteCase2(n);
}
void BRT::deleteCase2(Node* n){
    if(!n || !n->parent) return; // защита
    Node *b = brother(n);
    if (colorOf(b) == RED){
        n->parent->color = RED;
        b->color = BLACK;
        if(n == n->parent->l) rotateLeft(n->parent);
        else rotateRight(n->parent);
    }
    deleteCase3(n);
}

void BRT::deleteCase3(Node* n){
    if(!n || !n->parent) return;
    Node *b = brother(n);
    if (colorOf(n->parent) == BLACK &&
        colorOf(b) == BLACK &&
        colorOf(b ? b->l : nullptr) == BLACK &&
        colorOf(b ? b->r : nullptr) == BLACK) {
        if (b) b->color = RED;
        deleteCase1(n->parent);
    }
    else deleteCase4(n);
}

void BRT::deleteCase4(Node* n){
    if(!n || !n->parent) return;
    Node *b = brother(n);
    if (colorOf(n->parent) == RED &&
        colorOf(b) == BLACK &&
        colorOf(b ? b->l : nullptr) == BLACK &&
        colorOf(b ? b->r : nullptr) == BLACK) {
        if (b) b->color = RED;
        n->parent->color = BLACK;
    }
    else deleteCase5(n);
}

void BRT::deleteCase5(Node* n){
    if(!n || !n->parent) return;
    Node *b = brother(n);
    if (colorOf(b) == BLACK){
        if((n == n->parent->l) &&
           (colorOf(b ? b->r : nullptr) == BLACK) &&
           (colorOf(b ? b->l : nullptr) == RED)){
            b->color = RED;
            if(b->l) b->l->color = BLACK;
            rotateRight(b);
        }
        else if((n == n->parent->r) &&
                (colorOf(b ? b->l : nullptr) == BLACK) &&
                (colorOf(b ? b->r : nullptr) == RED)){
            b->color = RED;
            if(b->r) b->r->color = BLACK;
            rotateLeft(b);
        }
    }
    deleteCase6(n);
}

void BRT::deleteCase6(Node* n){
    if(!n || !n->parent) return;
    Node *b = brother(n);
    if(!b) return;
    b->color = n->parent->color;
    n->parent->color = BLACK;
    if(n == n->parent->l){
        if(b->r) b->r->color = BLACK;
        rotateLeft(n->parent);
    }
    else{
        if(b->l) b->l->color = BLACK;
        rotateRight(n->parent);
    }
}
void BRT::loadFromFile(){
    ifstream file("txt/brt.txt");
    if(!file.is_open()){
        cerr << "Не удалось открыть файл brt.txt" << endl;
        return; 
    }
    int key; 
    char color;
    while (file >> key >> color) {
        brtInsert(key); // цвет не используем, балансировка всё исправит
    }
    file.close();
}
void BRT::saveinorderrec(Node* n, ofstream& file){
    if(!n) return;
    saveinorderrec(n->l, file);
    file << n->key << " " << (n->color == RED ? "R" : "B") << "\n";
    saveinorderrec(n->r, file);
}
void BRT::saveToFile(){
    ofstream file("txt/brt.txt");
    if(!file.is_open()){
        cerr << "Не удалось создать файл brt.txt" << endl;
        return; 
    }
    saveinorderrec(root, file);
    file.close();
}

