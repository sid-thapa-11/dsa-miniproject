#include "undostack.h"

UndoStack::UndoStack() {}

void UndoStack::pushAdd(Student s) {
    if (stack.size() >= MAX_UNDO) stack.removeFirst();
    Action a;
    a.type = ADD;
    a.studentData = s;
    a.description = QString("Add student: %1 (ID: %2)").arg(s.name).arg(s.id);
    stack.push(a);
}

void UndoStack::pushDelete(Student s) {
    if (stack.size() >= MAX_UNDO) stack.removeFirst();
    Action a;
    a.type = DELETE_ACTION;
    a.studentData = s;
    a.description = QString("Delete student: %1 (ID: %2)").arg(s.name).arg(s.id);
    stack.push(a);
}

void UndoStack::pushUpdate(Student oldData, Student newData) {
    if (stack.size() >= MAX_UNDO) stack.removeFirst();
    Action a;
    a.type = UPDATE;
    a.studentData = newData;
    a.previousData = oldData;
    a.description = QString("Update student ID: %1").arg(oldData.id);
    stack.push(a);
}

Action UndoStack::pop() {
    return stack.pop();
}

Action UndoStack::peek() const {
    return stack.top();
}

bool UndoStack::isEmpty() const {
    return stack.isEmpty();
}

int UndoStack::size() const {
    return stack.size();
}

QString UndoStack::topDescription() const {
    if (stack.isEmpty()) return "Nothing to undo";
    return stack.top().description;
}

void UndoStack::clear() {
    stack.clear();
}
