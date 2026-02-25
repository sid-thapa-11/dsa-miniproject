#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QGroupBox>
#include <QTabWidget>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QMessageBox>

#include "linkedlist.h"
#include "bst.h"
#include "sortingalgorithms.h"
#include "undostack.h"



class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addStudent();
    void deleteStudent();
    void updateStudent();
    void searchStudent();
    void sortStudents();
    void undoAction();
    void clearSearch();
    void onTableRowSelected();
    void showDSAVisualization();
    void showAllStudents();

private:
    // UI Elements
    QWidget*        centralWidget;
    QTabWidget*     tabWidget;

    // Tab 1: Main Management
    QWidget*        mainTab;
    QTableWidget*   studentTable;
    QLineEdit*      nameEdit;
    QLineEdit*      deptEdit;
    QSpinBox*       idSpin;
    QSpinBox*       ageSpin;
    QDoubleSpinBox* gpaSpin;
    QPushButton*    addBtn;
    QPushButton*    deleteBtn;
    QPushButton*    updateBtn;
    QPushButton*    clearBtn;
    QPushButton*    undoBtn;
    QLabel*         undoLabel;
    QLabel*         statusLabel;
    QLabel*         countLabel;

    // Tab 2: Search & Sort
    QWidget*        searchTab;
    QLineEdit*      searchEdit;
    QComboBox*      searchTypeCombo;
    QPushButton*    searchBtn;
    QPushButton*    clearSearchBtn;
    QTableWidget*   searchResultTable;
    QComboBox*      sortCombo;
    QPushButton*    sortBtn;
    QLabel*         sortAlgoLabel;

    // Tab 3: DSA Visualization
    QWidget*        dsaTab;
    QTextEdit*      dsaDisplay;
    QPushButton*    showLinkedListBtn;
    QPushButton*    showBSTBtn;
    QPushButton*    showStackBtn;

    // DSA Backend
    LinkedList* linkedList;
    BST*        bst;
    UndoStack*  undoStack;

    // Helpers
    void setupUI();
    void setupMainTab();
    void setupSearchTab();
    void setupDSATab();
    void applyStyleSheet();
    void refreshTable(QVector<Student> students);
    void refreshMainTable();
    void updateStatusBar();
    void loadFormFromRow(int row);
    void clearForm();
    QString generateLinkedListVisualization();
    QString generateBSTVisualization();
    QString generateStackVisualization();
    void loadSampleData();
};

#endif // MAINWINDOW_H
