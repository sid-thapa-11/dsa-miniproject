#include "bst.h"

BST::BST() : root(nullptr) {}

BST::~BST() {
    destroyTree(root);
}

void BST::destroyTree(BSTNode* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

BSTNode* BST::insert(BSTNode* node, Student s) {
    if (!node) return new BSTNode(s);
    if (s.id < node->data.id)
        node->left = insert(node->left, s);
    else if (s.id > node->data.id)
        node->right = insert(node->right, s);
    return node;
}

void BST::insert(Student s) {
    root = insert(root, s);
}

BSTNode* BST::findMin(BSTNode* node) {
    while (node->left)
        node = node->left;
    return node;
}

BSTNode* BST::deleteNode(BSTNode* node, int id) {
    if (!node) return nullptr;
    if (id < node->data.id)
        node->left = deleteNode(node->left, id);
    else if (id > node->data.id)
        node->right = deleteNode(node->right, id);
    else {
        // Node with one or no child
        if (!node->left) {
            BSTNode* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            BSTNode* temp = node->left;
            delete node;
            return temp;
        }
        // Node with two children: get inorder successor
        BSTNode* successor = findMin(node->right);
        node->data = successor->data;
        node->right = deleteNode(node->right, successor->data.id);
    }
    return node;
}

void BST::remove(int id) {
    root = deleteNode(root, id);
}

BSTNode* BST::search(BSTNode* node, int id) {
    if (!node || node->data.id == id) return node;
    if (id < node->data.id) return search(node->left, id);
    return search(node->right, id);
}

Student* BST::search(int id) {
    BSTNode* result = search(root, id);
    if (result) return &result->data;
    return nullptr;
}

void BST::inorder(BSTNode* node, QVector<Student>& result) {
    if (!node) return;
    inorder(node->left, result);
    result.append(node->data);
    inorder(node->right, result);
}

QVector<Student> BST::inorderTraversal() {
    QVector<Student> result;
    inorder(root, result);
    return result;
}

void BST::clear() {
    destroyTree(root);
    root = nullptr;
}

void BST::rebuild(QVector<Student> students) {
    clear();
    for (auto& s : students)
        insert(s);
}
