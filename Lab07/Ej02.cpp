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

    bool find(std::string value, Node* key) {
        Node* leaf = this->search(value);
        for (size_t i = 0; i < leaf->values.size(); i++) {
            if (leaf->values[i] == value) {
                auto& vec = leaf->keys[i];
                if (std::find(vec.begin(), vec.end(), key) != vec.end()) {
                    return true;
                } else {
                    return false;
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
    if (!tree || !tree->root) return;

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

    std::cout << ">> Insertando elementos: 5, 15, 25, 35, 45..." << std::endl;
    bplusTree->insert("5", new Node(3));
    bplusTree->insert("15", new Node(3));
    bplusTree->insert("25", new Node(3));
    bplusTree->insert("35", new Node(3));
    bplusTree->insert("45", new Node(3));

    std::cout << "\n--- ESTRUCTURA ACTUAL DEL ARBOL (POR NIVELES) ---" << std::endl;
    printTree(bplusTree);

    std::cout << "\n--- PRUEBAS DE BUSQUEDA ---" << std::endl;
    Node* searchNode = new Node(3); 
    
    std::string testValue = "25";
    std::cout << "Buscando '" << testValue << "': ";
    if (bplusTree->find(testValue, searchNode)) {
        std::cout << "Encontrado de forma correcta." << std::endl;
    } else {
        std::cout << "No encontrado." << std::endl;
    }

    delete searchNode;
    delete bplusTree;

    return 0;
}