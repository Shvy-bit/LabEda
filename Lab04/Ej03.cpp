#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

int main() {
    Node* head = nullptr;
    Node* temp = nullptr;

    for (int i = 1; i <= 10; i++) {
        Node* newNode = new Node;
        newNode->data = i;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (head == nullptr) {
            head = newNode;
            temp = newNode;
        } else {
            temp->next = newNode;
            newNode->prev = temp;
            temp = newNode;
        }
    }

    Node* current = head;
    while (current != nullptr) {
        cout << "Dato: " << current->data << " [Dir: " << current << "] "
             << "Prev: " << current->prev << " Next: " << current->next << endl;
        current = current->next;
    }

    return 0;
}