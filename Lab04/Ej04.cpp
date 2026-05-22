#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

int main() {
    Node* head = nullptr;
    Node* temp = nullptr;

    for (int i = 1; i <= 12; i++) {
        Node* newNode = new Node;
        newNode->data = i;

        if (head == nullptr) {
            head = newNode;
            newNode->next = head;
            temp = newNode;
        } else {
            temp->next = newNode;
            newNode->next = head;
            temp = newNode;
        }
    }

    Node* curr = head;
    if (curr != nullptr) {
        do {
            cout << "Dato: " << curr->data
                 << " [Dir: " << curr << " ] "
                 << " -> Next: " << curr->next << endl;
            curr = curr->next;
        } while (curr != head);
    }

    return 0;
}