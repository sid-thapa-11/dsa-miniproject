#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "student.h"
#include <QVector>

// ===================================================
// DSA CONCEPT 1: Singly Linked List
// Used as the primary data structure to store all students
// Time Complexity: Insert O(1), Delete O(n), Search O(n)
// Space Complexity: O(n)
// ===================================================

struct Node {
    Student data;
    Node* next;
    Node(Student s) : data(s), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    int size;

public:
    LinkedList();
    ~LinkedList();

    void insertAtEnd(Student s);
    void insertAtBeginning(Student s);
    bool deleteById(int id);
    bool updateStudent(int id, Student updated);
    Node* searchById(int id);
    Node* searchByName(const QString& name);
    QVector<Student> getAllStudents() const;
    int getSize() const;
    bool isEmpty() const;
    void clear();
    Node* getHead() const { return head; }
};

#endif // LINKEDLIST_H
