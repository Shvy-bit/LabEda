#include <iostream>

using namespace std;
template<typename T>
struct Node {
    T key;
    Node *parent, *left, *right;
    int h;
    Node(T data): key(data), parent(nullptr), left(nullptr), right(nullptr), h(0) {}
};
template<typename T = int>
class BinarySearchTree {
    private:
    Node<T>* root; 

    Node<T>* insertNode(Node<T>* node, T key) {
        if (node == nullptr) {
            return new Node<T>(key);
        }
        if (key < node->key) {
            Node<T>* leftChild = insertNode(node->left, key);
            node->left = leftChild;
            leftChild->parent = node;
        } else if (key > node->key) {
            Node<T>* rightChild = insertNode(node->right, key);
            node->right = rightChild;
            rightChild->parent = node;
        }
        return node;
    }

    void deleteSubTree(Node<T>* node) {
        if (node != nullptr) {
            deleteSubTree(node->left);
            deleteSubTree(node->right);
            delete node;
        }
    }

    public:
    BinarySearchTree() : root(nullptr) {}
    
    ~BinarySearchTree() {
        deleteSubTree(root);
    }

    void insert(T key) {
        root = insertNode(root, key);
    }

    T obtenerSegundoMasGrande() {
        if (root == nullptr || (root->left == nullptr && root->right == nullptr)) {
            throw runtime_error("El árbol debe tener al menos dos elementos.");
        }

        Node<T>* curr = root;
        Node<T>* parent = nullptr;

        while (curr->right != nullptr) {
            parent = curr;
            curr = curr->right;
        }

        if (curr->left != nullptr) {
            curr = curr->left;
            while (curr->right != nullptr) {
                curr = curr->right;
            }
            return curr->key;
        }

        return parent->key;
    }
};

int main() {
    BinarySearchTree<int> bst;

    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(60);
    bst.insert(80);
    bst.insert(65);


    try {
        cout << "El segundo valor mas grande del arbol es: " 
             << bst.obtenerSegundoMasGrande() << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}