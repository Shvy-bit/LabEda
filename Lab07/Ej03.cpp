#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
    
class Node {
public:
    int order;
    std::vector<std::string> values;
    std::vector<std::vector<Node*>> keys; 
    Node* nextKey;
    Node* parent;
    bool isLeaf;

    Node(int order) {
        this->order = order;
        this->nextKey = nullptr;
        this->parent = nullptr;
        this->isLeaf = false;
    }

    ~Node() {
        if (!isLeaf) {
            for (auto& vec : keys) {
                for (Node* child : vec) {
                    delete child;
                }
            }
        }
    }

    void insertAtLeaf(std::string value, Node* key) {
        if (!this->values.empty()) {
            for (size_t i = 0; i < this->values.size(); i++) {
                if (value == this->values[i]) {
                    this->keys[i].push_back(key);
                    break;
                } else if (value < this->values[i]) {
                    this->values.insert(this->values.begin() + i, value);
                    this->keys.insert(this->keys.begin() + i, std::vector<Node*>());
                    this->keys[i].push_back(key);
                    break;
                } else if (i + 1 == this->values.size()) {
                    this->values.push_back(value);
                    this->keys.push_back(std::vector<Node*>());
                    this->keys[i + 1].push_back(key);
                    break;
                }
            }
        } else {
            this->values.push_back(value);
            this->keys.push_back(std::vector<Node*>());
            this->keys[0].push_back(key);
        }
    }
};
    
class BplusTree {
private:        
    void insertInParent(Node* n, std::string value, Node* ndash) {
        if (this->root == n) {
            Node* rootNode = new Node(n->order);
            rootNode->values.push_back(value);
            rootNode->keys.push_back(std::vector<Node*>());
            rootNode->keys.push_back(std::vector<Node*>());
            rootNode->keys[0].push_back(n);
            rootNode->keys[1].push_back(ndash);
            this->root = rootNode;
            n->parent = rootNode;
            ndash->parent = rootNode;
            return;
        }

        Node* parentNode = n->parent;
        for (size_t i = 0; i < parentNode->keys.size(); i++) {
            if (parentNode->keys[i][0] == n) {
                parentNode->values.insert(parentNode->values.begin() + i, value);
                parentNode->keys.insert(parentNode->keys.begin() + i + 1, std::vector<Node*>());
                parentNode->keys[i + 1].push_back(ndash);

                if (parentNode->keys.size() > static_cast<size_t>(parentNode->order)) {
                    Node* parentdash = new Node(parentNode->order);
                    parentdash->parent = parentNode->parent;
                    int mid = static_cast<int>(std::ceil(parentNode->order / 2.0)) - 1;

                    parentdash->values = std::vector<std::string>(parentNode->values.begin() + mid + 1, parentNode->values.end());
                    parentdash->keys = std::vector<std::vector<Node*>>(parentNode->keys.begin() + mid + 1, parentNode->keys.end());

                    std::string value_ = parentNode->values[mid];
                    if (mid == 0) {
                        parentNode->values = std::vector<std::string>(parentNode->values.begin(), parentNode->values.begin() + mid + 1);
                    } else {
                        parentNode->values = std::vector<std::string>(parentNode->values.begin(), parentNode->values.begin() + mid);
                    }
                    parentNode->keys = std::vector<std::vector<Node*>>(parentNode->keys.begin(), parentNode->keys.begin() + mid + 1);

                    for (size_t j = 0; j < parentNode->keys.size(); j++) {
                        parentNode->keys[j][0]->parent = parentNode;
                    }
                    for (size_t j = 0; j < parentdash->keys.size(); j++) {
                        parentdash->keys[j][0]->parent = parentdash;
                    }
                    this->insertInParent(parentNode, value_, parentdash);
                }
                break;
            }
        }
    }
        
    void removeInternal(std::string value, Node* cursor) {
        if (cursor == root) {
            if (cursor->values.empty()) {
                root = cursor->keys[0][0];
                if (root) root->parent = nullptr;
                cursor->keys[0].clear(); 
                delete cursor;
            }
            return;
        }

        auto it = std::find(cursor->values.begin(), cursor->values.end(), value);
        if (it != cursor->values.end()) {
            int idx = it - cursor->values.begin();
            cursor->values.erase(it);
            cursor->keys.erase(cursor->keys.begin() + idx + 1);
        }

        int minKeys = static_cast<int>(std::ceil(cursor->order / 2.0)) - 1;
        if (cursor->values.size() < static_cast<size_t>(minKeys)) {
            Node* parent = cursor->parent;
            int idxInParent = 0;
            while (parent->keys[idxInParent][0] != cursor) idxInParent++;
                
            if (idxInParent > 0) {
                Node* leftSibling = parent->keys[idxInParent - 1][0];
                if (leftSibling->values.size() > static_cast<size_t>(minKeys)) {
                    cursor->values.insert(cursor->values.begin(), parent->values[idxInParent - 1]);
                    parent->values[idxInParent - 1] = leftSibling->values.back();
                    cursor->keys.insert(cursor->keys.begin(), std::vector<Node*>{leftSibling->keys.back()[0]});
                    cursor->keys[0][0]->parent = cursor;
                    leftSibling->values.pop_back();
                    leftSibling->keys.pop_back();
                    return;
                }
            }               
            if (idxInParent < static_cast<int>(parent->keys.size()) - 1) {
                Node* rightSibling = parent->keys[idxInParent + 1][0];
                if (rightSibling->values.size() > static_cast<size_t>(minKeys)) {
                    cursor->values.push_back(parent->values[idxInParent]);
                    parent->values[idxInParent] = rightSibling->values.front();
                    cursor->keys.push_back(std::vector<Node*>{rightSibling->keys.front()[0]});
                    cursor->keys.back()[0]->parent = cursor;
                    rightSibling->values.erase(rightSibling->values.begin());
                    rightSibling->keys.erase(rightSibling->keys.begin());
                    return;
                }
            }               
            if (idxInParent > 0) {
                Node* leftSibling = parent->keys[idxInParent - 1][0];
                leftSibling->values.push_back(parent->values[idxInParent - 1]);
                for (size_t i = 0; i < cursor->values.size(); i++) {
                    leftSibling->values.push_back(cursor->values[i]);
                }
                for (size_t i = 0; i < cursor->keys.size(); i++) {
                    leftSibling->keys.push_back(cursor->keys[i]);
                    leftSibling->keys.back()[0]->parent = leftSibling;
                }
                std::string parentVal = parent->values[idxInParent - 1];
                cursor->keys.clear();
                delete cursor;
                removeInternal(parentVal, parent);
            } else {
                Node* rightSibling = parent->keys[idxInParent + 1][0];
                cursor->values.push_back(parent->values[idxInParent]);
                for (size_t i = 0; i < rightSibling->values.size(); i++) {
                    cursor->values.push_back(rightSibling->values[i]);
                }
                for (size_t i = 0; i < rightSibling->keys.size(); i++) {
                    cursor->keys.push_back(rightSibling->keys[i]);
                    cursor->keys.back()[0]->parent = cursor;
                }
                std::string parentVal = parent->values[idxInParent];
                rightSibling->keys.clear();
                delete rightSibling;
                removeInternal(parentVal, parent);
            }
        }
    }

public:
    Node* root;

    BplusTree(int order) {
        this->root = new Node(order);
        this->root->isLeaf = true;
    }

    ~BplusTree() {
        delete root;
    }

    Node* search(std::string value) {
        Node* currentNode = this->root;
        while (!currentNode->isLeaf) {
            for (size_t i = 0; i < currentNode->values.size(); i++) {
                if (value == currentNode->values[i]) {
                    currentNode = currentNode->keys[i + 1][0];
                    break;
                } else if (value < currentNode->values[i]) {
                    currentNode = currentNode->keys[i][0];
                    break;
                } else if (i + 1 == currentNode->values.size()) {
                    currentNode = currentNode->keys[i + 1][0];
                    break;
                }
            }
        }
        return currentNode;
    }

    void insert(std::string value, Node* key) {
        Node* oldNode = this->search(value);
        oldNode->insertAtLeaf(value, key);

        if (oldNode->values.size() == static_cast<size_t>(oldNode->order)) {
            Node* newNode = new Node(oldNode->order);
            newNode->isLeaf = true;
            newNode->parent = oldNode->parent;
            int mid = static_cast<int>(std::ceil(oldNode->order / 2.0)) - 1;

            newNode->values = std::vector<std::string>(oldNode->values.begin() + mid + 1, oldNode->values.end());
            newNode->keys = std::vector<std::vector<Node*>>(oldNode->keys.begin() + mid + 1, oldNode->keys.end());
            newNode->nextKey = oldNode->nextKey;

            oldNode->values = std::vector<std::string>(oldNode->values.begin(), oldNode->values.begin() + mid + 1);
            oldNode->keys = std::vector<std::vector<Node*>>(oldNode->keys.begin(), oldNode->keys.begin() + mid + 1);
            oldNode->nextKey = newNode;

            this->insertInParent(oldNode, newNode->values[0], newNode);
        }
    }
        
    void remove(std::string value) {
        if (root == nullptr) return;

        Node* leaf = search(value);
        auto it = std::find(leaf->values.begin(), leaf->values.end(), value);
        
        if (it == leaf->values.end()) {
            std::cout << "La clave '" << value << "' no existe en el arbol." << std::endl;
            return;
        }

        int idx = it - leaf->values.begin();
        leaf->values.erase(it);
        leaf->keys.erase(leaf->keys.begin() + idx);
            
        if (leaf == root) {
            if (leaf->values.empty()) {                 
            }
            return;
        }

        int minKeys = static_cast<int>(std::ceil(leaf->order / 2.0)) - 1;
            
        if (leaf->values.size() < static_cast<size_t>(minKeys)) {
            Node* parent = leaf->parent;
            int idxInParent = 0;
            while (parent->keys[idxInParent][0] != leaf) idxInParent++;
                
            if (idxInParent > 0) {
                Node* leftSibling = parent->keys[idxInParent - 1][0];
                if (leftSibling->values.size() > static_cast<size_t>(minKeys)) {
                    leaf->values.insert(leaf->values.begin(), leftSibling->values.back());
                    leaf->keys.insert(leaf->keys.begin(), leftSibling->keys.back());
                    leftSibling->values.pop_back();
                    leftSibling->keys.pop_back();
                    parent->values[idxInParent - 1] = leaf->values[0];
                    return;
                }
            }
                
            if (idxInParent < static_cast<int>(parent->keys.size()) - 1) {
                Node* rightSibling = parent->keys[idxInParent + 1][0];
                if (rightSibling->values.size() > static_cast<size_t>(minKeys)) {
                    leaf->values.push_back(rightSibling->values.front());
                    leaf->keys.push_back(rightSibling->keys.front());
                    rightSibling->values.erase(rightSibling->values.begin());
                    rightSibling->keys.erase(rightSibling->keys.begin());
                    parent->values[idxInParent] = rightSibling->values[0];
                    return;
                }
            }
                
            if (idxInParent > 0) {
                Node* leftSibling = parent->keys[idxInParent - 1][0];
                for (size_t i = 0; i < leaf->values.size(); i++) {
                    leftSibling->values.push_back(leaf->values[i]);
                    leftSibling->keys.push_back(leaf->keys[i]);
                }
                leftSibling->nextKey = leaf->nextKey;
                std::string parentVal = parent->values[idxInParent - 1];
                delete leaf;
                removeInternal(parentVal, parent);
            } else {
                Node* rightSibling = parent->keys[idxInParent + 1][0];
                for (size_t i = 0; i < rightSibling->values.size(); i++) {
                    leaf->values.push_back(rightSibling->values[i]);
                    leaf->keys.push_back(rightSibling->keys[i]);
                }
                leaf->nextKey = rightSibling->nextKey;
                std::string parentVal = parent->values[idxInParent];
                delete rightSibling;
                removeInternal(parentVal, parent);
            }
        }
    }

    bool find(std::string value, Node* key) {
        Node* leaf = this->search(value);
        for (size_t i = 0; i < leaf->values.size(); i++) {
            if (leaf->values[i] == value) {
                auto& vec = leaf->keys[i];
                if (std::find(vec.begin(), vec.end(), key) != vec.end()) {
                    return true;
                }
            }
        }
        return false;
    }
};
    
void printValues(const std::vector<std::string>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i + 1 < vec.size()) std::cout << ", ";
    }
    std::cout << "]";
}

void printTree(BplusTree* tree) {
    if (!tree || !tree->root || tree->root->values.empty()) {
        std::cout << "Arbol Vacio." << std::endl;
        return;
    }
    std::vector<Node*> lst;
    lst.push_back(tree->root);
    std::vector<int> level;
    level.push_back(0);
    int current_level = 0;
    std::cout << "Nivel 0: ";

    while (!lst.empty()) {
        Node* x = lst[0];
        lst.erase(lst.begin());
        int lev = level[0];
        level.erase(level.begin());

        if (lev != current_level) {
            current_level = lev;
            std::cout << "\nNivel " << current_level << ": ";
        }
        printValues(x->values);
        std::cout << " ";

        if (!x->isLeaf) {
            for (size_t i = 0; i < x->keys.size(); i++) {
                if (!x->keys[i].empty() && x->keys[i][0] != nullptr) {
                    lst.push_back(x->keys[i][0]);
                    level.push_back(lev + 1);
                }
            }
        }
    }
    std::cout << std::endl;
}
    
int main() {
    BplusTree* bplusTree = new BplusTree(3);

    std::cout << "--- 1. INSERTANDO ELEMENTOS ---" << std::endl;
    bplusTree->insert("5", new Node(3));
    bplusTree->insert("15", new Node(3));
    bplusTree->insert("25", new Node(3));
    bplusTree->insert("35", new Node(3));
    bplusTree->insert("45", new Node(3));
    printTree(bplusTree);

    std::cout << "\n--- 2. ELIMINANDO '35' (Borrado simple en hoja) ---" << std::endl;
    bplusTree->remove("35");
    printTree(bplusTree);

    std::cout << "\n--- 3. ELIMINANDO '45' (Causa subdesborde y fusion) ---" << std::endl;
    bplusTree->remove("45");
    printTree(bplusTree);

    delete bplusTree;
    return 0;
}