#ifndef SORTINGALGORITHMS_H
#define SORTINGALGORITHMS_H

#include "student.h"
#include <QVector>

// ===================================================
// DSA CONCEPT 3: Sorting Algorithms
// Bubble Sort  - O(n²) time, O(1) space
// Quick Sort   - O(n log n) average, O(n²) worst
// ===================================================

class SortingAlgorithms {
public:
    // Sort by Name (Bubble Sort)
    static QVector<Student> bubbleSortByName(QVector<Student> students);

    // Sort by GPA descending (Quick Sort)
    static QVector<Student> quickSortByGPA(QVector<Student> students, int low, int high);
    static QVector<Student> sortByGPA(QVector<Student> students);

    // Sort by ID (Bubble Sort)
    static QVector<Student> bubbleSortById(QVector<Student> students);

private:
    static int partitionByGPA(QVector<Student>& arr, int low, int high);
    static void quickSortHelper(QVector<Student>& arr, int low, int high);
};

#endif // SORTINGALGORITHMS_H
