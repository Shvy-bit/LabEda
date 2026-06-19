#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class BPlusNode {
public:
    bool isLeaf;
    vector<int> keys;
    BPlusNode* next; 
    vector<BPlusNode*> children; 

    BPlusNode(bool leaf) {
        isLeaf = leaf;
        next = nullptr;
    }
};

class BPlusTree {
private:
    BPlusNode* root;
    int order; 
    
    void insertInternal(int x, BPlusNode* parent, BPlusNode* child);
    BPlusNode* findParent(BPlusNode* cursor, BPlusNode* child);

public:
    BPlusTree(int _order) {
        root = nullptr;
        order = _order;
    }

    void insert(int x);
    bool search(int x);
    void printTree();
};


bool BPlusTree::search(int x) {
    if (root == nullptr) { return false; }

    BPlusNode* cursor = root;
    while (!cursor->isLeaf) {
        int idx = upper_bound(cursor->keys.begin(), cursor->keys.end(), x) - cursor->keys.begin();
        cursor = cursor->children[idx];
    }
    return binary_search(cursor->keys.begin(), cursor->keys.end(), x);
}

void BPlusTree::insert(int x) {
    if (root == nullptr) {
        root = new BPlusNode(true);
        root->keys.push_back(x);
        return;
    }

    BPlusNode* cursor = root;
    BPlusNode* parent = nullptr;
    
    while (!cursor->isLeaf) {
        parent = cursor;
        int idx = upper_bound(cursor->keys.begin(), cursor->keys.end(), x) - cursor->keys.begin();
        cursor = cursor->children[idx];
    }
    
    auto it = lower_bound(cursor->keys.begin(), cursor->keys.end(), x);
    cursor->keys.insert(it, x);
    
    if (cursor->keys.size() > order) {
        BPlusNode* newLeaf = new BPlusNode(true);
                
        int size = (order + 1) / 2;
                
        newLeaf->keys.assign(cursor->keys.begin() + size, cursor->keys.end());
        cursor->keys.erase(cursor->keys.begin() + size, cursor->keys.end());
        
        newLeaf->next = cursor->next;
        cursor->next = newLeaf;
        
        if (cursor == root) {
            BPlusNode* newRoot = new BPlusNode(false);
            newRoot->keys.push_back(newLeaf->keys[0]);
            newRoot->children.push_back(cursor);
            newRoot->children.push_back(newLeaf);
            root = newRoot;
        } else {            
            insertInternal(newLeaf->keys[0], parent, newLeaf);
        }
    }
}

void BPlusTree::insertInternal(int x, BPlusNode* parent, BPlusNode* child) {
    auto it = lower_bound(parent->keys.begin(), parent->keys.end(), x);
    int idx = it - parent->keys.begin();
    
    parent->keys.insert(it, x);
    parent->children.insert(parent->children.begin() + idx + 1, child);
    
    if (parent->keys.size() > order) {
        BPlusNode* newInternal = new BPlusNode(false);
        int size = (order + 1) / 2;
        
        int promotionKey = parent->keys[size];
        
        newInternal->keys.assign(parent->keys.begin() + size + 1, parent->keys.end());
        newInternal->children.assign(parent->children.begin() + size + 1, parent->children.end());
        
        parent->keys.erase(parent->keys.begin() + size, parent->keys.end());
        parent->children.erase(parent->children.begin() + size + 1, parent->children.end());

        if (parent == root) {
            BPlusNode* newRoot = new BPlusNode(false);
            newRoot->keys.push_back(promotionKey);
            newRoot->children.push_back(parent);
            newRoot->children.push_back(newInternal);
            root = newRoot;
        } else {
            insertInternal(promotionKey, findParent(root, parent), newInternal);
        }
    }
}

BPlusNode* BPlusTree::findParent(BPlusNode* cursor, BPlusNode* child) {
    BPlusNode* parent = nullptr;
    if (cursor->isLeaf || cursor->children[0]->isLeaf) {
        return nullptr;
    }
    for (auto* ch : cursor->children) {
        if (ch == child) { return cursor; }
        else {
            parent = findParent(ch, child);
            if (parent != nullptr) return parent;
        }
    }
    return parent;
}

void BPlusTree::printTree() {
    if (root == nullptr) return;
    BPlusNode* cursor = root;
    while (!cursor->isLeaf) {
        cursor = cursor->children[0];
    }
    cout << "Hojas en orden secuencial: ";
    while (cursor != nullptr) {
        for (int k : cursor->keys) {
            cout << k << " ";
        }
        cout << " | ";
        cursor = cursor->next;
    }
    cout << endl;
}

int main() {    
    BPlusTree tree(3);

    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(6);
    tree.insert(12);
    tree.insert(30);

    tree.printTree();
    
    int target = 12;
    if (tree.search(target)) {
        cout << "El elemento " << target << " existe en el arbol." << endl;
    } else {
        cout << "El elemento " << target << " NO existe." << endl;
    }

    return 0;
}