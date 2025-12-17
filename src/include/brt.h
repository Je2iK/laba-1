#ifndef BRT_H
#define BRT_H
#include <iostream>
#include <vector>
#include "../json.hpp"
using namespace std;
using json = nlohmann::json;
enum node_colors{RED, BLACK};

struct Node{
    int key;
    node_colors color;
    Node *l, *r, *parent;
    
    Node(int k) : key(k), color(RED), l(nullptr), r(nullptr), parent(nullptr){}
};

class BRT{
public:
        Node* root;
        BRT() : root(nullptr){};
        node_colors colorOf(Node* n);
        Node* findNode(int key);
        Node* minimum(Node* n);

        void brtInsert(int key);
        void inorder();
        void inorderRec(Node* n);
        void brtRemove(int key);
        void loadFromFile();
        void saveinorderrec(Node* n, ofstream& file);
        void saveToFile();
        
        vector<pair<int, string>> toVector() const;
        void fromVector(const vector<pair<int, string>>& data);
        json toJson() const;
        void fromJson(const json& j);
private:
        Node* grandparent(Node* n);
        Node* uncle(Node* n);
        Node* brother(Node* n);
        void rotateLeft(Node* n);
        void rotateRight(Node* n);
        void insertCase1(Node* n);
        void insertCase2(Node* n);
        void insertCase3(Node* n);
        void insertCase4(Node* n);
        void insertCase5(Node* n);
        void replace_node(Node* n, Node* child);
        void deleteCase1(Node* n);
        void deleteCase2(Node* n);
        void deleteCase3(Node* n);
        void deleteCase4(Node* n);
        void deleteCase5(Node* n);
        void deleteCase6(Node* n);
        
        void toVectorRec(Node* n, vector<pair<int, string>>& result) const;
        void clear(Node* n);
    };    

#endif
