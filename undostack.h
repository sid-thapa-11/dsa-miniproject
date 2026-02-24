#ifndef UNDOSTACK_H
#define UNDOSTACK_H

#include "student.h"
#include <QString>
#include <QStack>

// ===================================================
// DSA CONCEPT 4: Stack
// Used to implement Undo functionality
// LIFO - Last In, First Out
// Time Complexity: Push/Pop O(1)
// ===================================================

enum ActionType { ADD, DELETE_ACTION, UPDATE };

struct Action {
    ActionType type;
    Student studentData;     // For undo: stores old state
    Student previousData;    // For UPDATE undo: stores previous data
    QString description;
};

class UndoStack {
private:
    QStack<Action> stack;
    static const int MAX_UNDO = 20;

public:
    UndoStack();

    void pushAdd(Student s);
    void pushDelete(Student s);
    void pushUpdate(Student oldData, Student newData);

    Action pop();
    Action peek() const;
    bool isEmpty() const;
    int size() const;
    QString topDescription() const;
    void clear();
};

#endif // UNDOSTACK_H
