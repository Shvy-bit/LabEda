#include <iostream>
#include <vector>

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
    void destroyTree(Node<T>* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }    
    void collectElements(Node<T>* node, vector<T>& elements) const {
        if (node == nullptr) return;
        collectElements(node->left, elements);
        elements.push_back(node->key);
        collectElements(node->right, elements);
    }
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() { destroyTree(root); }

    void insert(T key) { root = insert(root, key); }
    vector<T> getElements() const {
        vector<T> elements;
        collectElements(root, elements);
        return elements;
    }
};

template <typename T>
bool tienenMismosElementos(const BinarySearchTree<T>& tree1, const BinarySearchTree<T>& tree2) {
    vector<T> list1 = tree1.getElements();
    vector<T> list2 = tree2.getElements();    
    if (list1.size() != list2.size()) { return false; }     
    for (size_t i = 0; i < list1.size(); ++i) {
        if (list1[i] != list2[i]) { return false; }
    }
    return true;
}

int main() {
    BinarySearchTree<int> arbol1;
    BinarySearchTree<int> arbol2;    
    arbol1.insert(15);
    arbol1.insert(10);
    arbol1.insert(20);
    arbol1.insert(5);    

    arbol2.insert(10);
    arbol2.insert(5);
    arbol2.insert(15);
    arbol2.insert(20);

    cout << "--- Prueba 1 (Mismos elementos) ---" << endl;
    if (tienenMismosElementos(arbol1, arbol2)) {
        cout << "Los dos arboles tienen los mismos elementos." << endl;
    } else {
        cout << "Los dos arboles no tienen los mismos elementos." << endl;
    }    
    arbol2.insert(99);

    cout << "\n--- Prueba 2 (Con un elemento extra en el Arbol 2) ---" << endl;
    if (tienenMismosElementos(arbol1, arbol2)) {
        cout << "Los dos arboles tienen los mismos elementos." << endl;
    } else {
        cout << "Los dos arboles no tienen los mismos elementos." << endl;
    }
    return 0;
}