#include "sortingalgorithms.h"

// ===================================================
// BUBBLE SORT by Name - O(n²)
// ===================================================
QVector<Student> SortingAlgorithms::bubbleSortByName(QVector<Student> students) {
    int n = students.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].name.toLower() > students[j + 1].name.toLower()) {
                std::swap(students[j], students[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // Optimization: already sorted
    }
    return students;
}

// ===================================================
// BUBBLE SORT by ID - O(n²)
// ===================================================
QVector<Student> SortingAlgorithms::bubbleSortById(QVector<Student> students) {
    int n = students.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].id > students[j + 1].id) {
                std::swap(students[j], students[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    return students;
}

// ===================================================
// QUICK SORT by GPA (descending) - O(n log n) avg
// ===================================================
int SortingAlgorithms::partitionByGPA(QVector<Student>& arr, int low, int high) {
    double pivot = arr[high].gpa;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].gpa >= pivot) { // descending
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void SortingAlgorithms::quickSortHelper(QVector<Student>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionByGPA(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

QVector<Student> SortingAlgorithms::sortByGPA(QVector<Student> students) {
    if (students.size() <= 1) return students;
    quickSortHelper(students, 0, students.size() - 1);
    return students;
}
