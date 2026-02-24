# Student Record Management System
### DSA Mini Project — C++ with Qt Creator

---

## 📦 Project Structure

```
StudentRecordSystem/
├── StudentRecordSystem.pro   ← Qt project file
├── main.cpp                  ← Application entry point
├── student.h / student.cpp   ← Student data model
├── linkedlist.h / .cpp       ← DSA: Singly Linked List
├── bst.h / .cpp              ← DSA: Binary Search Tree
├── sortingalgorithms.h / .cpp← DSA: Bubble Sort + Quick Sort
├── undostack.h / .cpp        ← DSA: Stack (Undo feature)
├── mainwindow.h / .cpp       ← Qt GUI (Frontend + Logic)
└── README.md                 ← This file
```

---

## 🧠 DSA Concepts Used

### 1. Singly Linked List (`linkedlist.h / .cpp`)
- **Purpose**: Primary storage for all student records
- **Operations**: insertAtEnd, insertAtBeginning, deleteById, searchById, searchByName
- **Complexity**: Insert O(1), Search O(n), Delete O(n)
- **Why**: Dynamic memory allocation — no fixed size needed

### 2. Binary Search Tree / BST (`bst.h / .cpp`)
- **Purpose**: Efficient search of students by ID
- **Operations**: insert, search, delete, inorder traversal
- **Complexity**: Search O(log n) average, O(n) worst
- **Why**: Much faster ID lookup than linear linked list search

### 3. Stack (`undostack.h / .cpp`)
- **Purpose**: Undo system — tracks last 20 operations
- **Operations**: push (O(1)), pop (O(1))
- **LIFO**: Last added action is the first to be undone
- **Actions tracked**: ADD, DELETE, UPDATE

### 4. Sorting Algorithms (`sortingalgorithms.h / .cpp`)
- **Bubble Sort**: Sort by Name A→Z and by ID ascending — O(n²)
- **Quick Sort**: Sort by GPA descending — O(n log n) average
- **Comparison**: Quick Sort is significantly faster for large datasets

---

## ✨ Features

| Feature              | DSA Concept         |
|----------------------|---------------------|
| Add Student          | Linked List Insert  |
| Delete Student       | Linked List Delete  |
| Update Student       | Linked List Update  |
| Search by ID         | BST Search O(log n) |
| Search by Name       | Linked List Search  |
| Sort by Name         | Bubble Sort O(n²)   |
| Sort by GPA          | Quick Sort O(n logn)|
| Sort by ID           | Bubble Sort O(n²)   |
| Undo Last Action     | Stack Pop O(1)      |
| Visualize Structures | All DSA structures  |

---

## 🖥️ How to Open in Qt Creator

1. Open **Qt Creator**
2. Click **File → Open File or Project**
3. Navigate to this folder and select `StudentRecordSystem.pro`
4. Click **Configure Project** (accept defaults)
5. Press **Ctrl+B** to Build
6. Press **Ctrl+R** to Run

> **Requirements**: Qt 5.x or Qt 6.x with Widgets module

---

## 📸 UI Overview

- **Tab 1 – Manage Students**: Add/Update/Delete/Undo with live table
- **Tab 2 – Search & Sort**: BST/Linked List search, 3 sort algorithms
- **Tab 3 – DSA Visualization**: Text visualization of Linked List, BST, and Stack

---

## 🎨 Color Coding in Table
- 🟢 Green  = GPA ≥ 3.5 (Excellent)
- 🟡 Yellow = GPA ≥ 2.5 (Good)
- 🔴 Red    = GPA < 2.5  (Needs Improvement)
