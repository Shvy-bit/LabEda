#include <iostream>
using namespace std;
class LinkedList {
    public:
    class Node {
        public:
        int data;
        Node* next;
        Node* prev;
        Node(int d): data(d) {
            next = nullptr;
            prev = nullptr;
        }
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    void insert(int data);
    void printList();
};
void LinkedList::insert(int data) {
    Node* newNode = new Node(data);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}
void LinkedList::printList() {
    Node* current = head;
    cout << "LinkedList: ";
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

int main() {
    LinkedList list;
    for(int i = 1; i <= 10; i++) {
        list.insert(i);
    }
    list.printList();
    return 0;
}