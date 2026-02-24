#include "linkedlist.h"

LinkedList::LinkedList() : head(nullptr), size(0) {}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::insertAtEnd(Student s) {
    Node* newNode = new Node(s);
    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
    }
    size++;
}

void LinkedList::insertAtBeginning(Student s) {
    Node* newNode = new Node(s);
    newNode->next = head;
    head = newNode;
    size++;
}

bool LinkedList::deleteById(int id) {
    if (!head) return false;

    // Special case: head node
    if (head->data.id == id) {
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
        return true;
    }

    Node* prev = head;
    Node* curr = head->next;
    while (curr) {
        if (curr->data.id == id) {
            prev->next = curr->next;
            delete curr;
            size--;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

bool LinkedList::updateStudent(int id, Student updated) {
    Node* node = searchById(id);
    if (node) {
        node->data = updated;
        return true;
    }
    return false;
}

Node* LinkedList::searchById(int id) {
    Node* curr = head;
    while (curr) {
        if (curr->data.id == id)
            return curr;
        curr = curr->next;
    }
    return nullptr;
}

Node* LinkedList::searchByName(const QString& name) {
    Node* curr = head;
    while (curr) {
        if (curr->data.name.toLower().contains(name.toLower()))
            return curr;
        curr = curr->next;
    }
    return nullptr;
}

QVector<Student> LinkedList::getAllStudents() const {
    QVector<Student> result;
    Node* curr = head;
    while (curr) {
        result.append(curr->data);
        curr = curr->next;
    }
    return result;
}

int LinkedList::getSize() const {
    return size;
}

bool LinkedList::isEmpty() const {
    return head == nullptr;
}

void LinkedList::clear() {
    Node* curr = head;
    while (curr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
    head = nullptr;
    size = 0;
}
