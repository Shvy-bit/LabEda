#include <iostream>

using namespace std;

template <typename T>
struct Node {
    T key;
    Node* left;
    Node* right;
    
    Node(T val) : key(val), left(nullptr), right(nullptr) {}
};

template <typename T = int>
class BinarySearchTree {
private:
    Node<T>* root;
    
    Node<T>* insert(Node<T>* node, T key) {
        if (node == nullptr) {
            return new Node<T>(key);
        }
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        }
        return node;
    }
    
    void inorder(Node<T>* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }
    
    void destroyTree(Node<T>* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}
    
    ~BinarySearchTree() {
        destroyTree(root);
    }

    void insert(T key) {
        root = insert(root, key);
    }

    void displayInorder() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    BinarySearchTree<int> arbol;
    
    arbol.insert(50);
    arbol.insert(30);
    arbol.insert(70);
    arbol.insert(20);
    arbol.insert(40);

    cout << "Elementos del BST en orden ascendente (Inorder):" << endl;
    arbol.displayInorder();

    return 0;
}