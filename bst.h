#ifndef BST_H
#define BST_H

#include "student.h"
#include <QVector>

// ===================================================
// DSA CONCEPT 2: Binary Search Tree (BST)
// Used for efficient searching by Student ID
// Time Complexity: Average O(log n), Worst O(n)
// Space Complexity: O(n)
// ===================================================

struct BSTNode {
    Student data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(Student s) : data(s), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, Student s);
    BSTNode* deleteNode(BSTNode* node, int id);
    BSTNode* findMin(BSTNode* node);
    BSTNode* search(BSTNode* node, int id);
    void inorder(BSTNode* node, QVector<Student>& result);
    void destroyTree(BSTNode* node);

public:
    BST();
    ~BST();

    void insert(Student s);
    void remove(int id);
    Student* search(int id);
    QVector<Student> inorderTraversal(); // Returns sorted by ID
    void rebuild(QVector<Student> students);
    void clear();
};

#endif // BST_H
