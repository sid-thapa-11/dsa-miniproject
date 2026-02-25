#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QFormLayout>
#include <QSplitter>
#include <QFont>
#include <QApplication>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    linkedList = new LinkedList();
    bst        = new BST();
    undoStack  = new UndoStack();

    setupUI();
    applyStyleSheet();
    loadSampleData();
    refreshMainTable();
    updateStatusBar();
}

MainWindow::~MainWindow() {
    delete linkedList;
    delete bst;
    delete undoStack;
}

// ============================================================
// SETUP UI
// ============================================================
void MainWindow::setupUI() {
    setWindowTitle("Student Record Management System - DSA Project");
    setMinimumSize(1100, 700);
    resize(1200, 750);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Title
    QLabel* title = new QLabel("🎓 Student Record Management System");
    title->setObjectName("titleLabel");
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);

    QLabel* subtitle = new QLabel("DSA Concepts: Linked List | Binary Search Tree | Stack | Sorting Algorithms");
    subtitle->setObjectName("subtitleLabel");
    subtitle->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(subtitle);

    tabWidget = new QTabWidget();
    mainLayout->addWidget(tabWidget);

    setupMainTab();
    setupSearchTab();
    setupDSATab();

    // Status bar
    statusLabel = new QLabel("Ready");
    statusBar()->addWidget(statusLabel);
    countLabel = new QLabel("Total Students: 0");
    statusBar()->addPermanentWidget(countLabel);
}

void MainWindow::setupMainTab() {
    mainTab = new QWidget();
    tabWidget->addTab(mainTab, "📋 Manage Students");

    QHBoxLayout* layout = new QHBoxLayout(mainTab);

    // LEFT: Form Panel
    QGroupBox* formGroup = new QGroupBox("Student Details");
    formGroup->setMaximumWidth(300);
    QFormLayout* formLayout = new QFormLayout(formGroup);
    formLayout->setSpacing(10);

    idSpin = new QSpinBox();
    idSpin->setRange(1, 99999);
    idSpin->setValue(1001);

    nameEdit = new QLineEdit();
    nameEdit->setPlaceholderText("Enter full name...");

    deptEdit = new QLineEdit();
    deptEdit->setPlaceholderText("e.g. Computer Science");

    ageSpin = new QSpinBox();
    ageSpin->setRange(16, 60);
    ageSpin->setValue(20);

    gpaSpin = new QDoubleSpinBox();
    gpaSpin->setRange(0.0, 4.0);
    gpaSpin->setSingleStep(0.1);
    gpaSpin->setDecimals(2);
    gpaSpin->setValue(3.0);

    formLayout->addRow("Student ID:", idSpin);
    formLayout->addRow("Full Name:", nameEdit);
    formLayout->addRow("Department:", deptEdit);
    formLayout->addRow("Age:", ageSpin);
    formLayout->addRow("GPA:", gpaSpin);

    // Buttons
    addBtn    = new QPushButton("➕ Add Student");
    updateBtn = new QPushButton("✏️ Update Student");
    deleteBtn = new QPushButton("🗑️ Delete Student");
    clearBtn  = new QPushButton("🔄 Clear Form");
    undoBtn   = new QPushButton("↩️ Undo");
    undoLabel = new QLabel("Nothing to undo");
    undoLabel->setObjectName("undoLabel");
    undoLabel->setWordWrap(true);

    addBtn->setObjectName("addBtn");
    updateBtn->setObjectName("updateBtn");
    deleteBtn->setObjectName("deleteBtn");

    formLayout->addRow(addBtn);
    formLayout->addRow(updateBtn);
    formLayout->addRow(deleteBtn);
    formLayout->addRow(clearBtn);
    formLayout->addRow(undoBtn);
    formLayout->addRow("Last Action:", undoLabel);

    layout->addWidget(formGroup);

    // RIGHT: Table
    QGroupBox* tableGroup = new QGroupBox("Student Records (Linked List Storage)");
    QVBoxLayout* tableLayout = new QVBoxLayout(tableGroup);

    studentTable = new QTableWidget();
    studentTable->setColumnCount(5);
    studentTable->setHorizontalHeaderLabels({"ID", "Name", "Department", "Age", "GPA"});
    studentTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    studentTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    studentTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    studentTable->setAlternatingRowColors(true);
    studentTable->setSortingEnabled(false);

    tableLayout->addWidget(studentTable);
    layout->addWidget(tableGroup);

    // Connections
    connect(addBtn,    &QPushButton::clicked, this, &MainWindow::addStudent);
    connect(updateBtn, &QPushButton::clicked, this, &MainWindow::updateStudent);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::deleteStudent);
    connect(clearBtn,  &QPushButton::clicked, this, &MainWindow::clearForm);
    connect(undoBtn,   &QPushButton::clicked, this, &MainWindow::undoAction);
    connect(studentTable, &QTableWidget::cellClicked, this, &MainWindow::onTableRowSelected);
}

void MainWindow::setupSearchTab() {
    searchTab = new QWidget();
    tabWidget->addTab(searchTab, "🔍 Search & Sort");

    QVBoxLayout* layout = new QVBoxLayout(searchTab);

    // Search Section
    QGroupBox* searchGroup = new QGroupBox("Search Students (BST - Binary Search Tree)");
    QHBoxLayout* searchLayout = new QHBoxLayout(searchGroup);

    searchEdit = new QLineEdit();
    searchEdit->setPlaceholderText("Enter search query...");

    searchTypeCombo = new QComboBox();
    searchTypeCombo->addItems({"Search by ID (BST O(log n))", "Search by Name (Linked List O(n))"});

    searchBtn      = new QPushButton("🔍 Search");
    clearSearchBtn = new QPushButton("✖ Clear");
    searchBtn->setObjectName("addBtn");

    searchLayout->addWidget(new QLabel("Query:"));
    searchLayout->addWidget(searchEdit);
    searchLayout->addWidget(searchTypeCombo);
    searchLayout->addWidget(searchBtn);
    searchLayout->addWidget(clearSearchBtn);
    layout->addWidget(searchGroup);

    // Search Results
    searchResultTable = new QTableWidget();
    searchResultTable->setColumnCount(5);
    searchResultTable->setHorizontalHeaderLabels({"ID", "Name", "Department", "Age", "GPA"});
    searchResultTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    searchResultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    searchResultTable->setAlternatingRowColors(true);
    QGroupBox* resultGroup = new QGroupBox("Search Results");
    QVBoxLayout* resultLayout = new QVBoxLayout(resultGroup);
    resultLayout->addWidget(searchResultTable);
    layout->addWidget(resultGroup);

    // Sort Section
    QGroupBox* sortGroup = new QGroupBox("Sort Students");
    QHBoxLayout* sortLayout = new QHBoxLayout(sortGroup);

    sortCombo = new QComboBox();
    sortCombo->addItem("Sort by Name A→Z  [Bubble Sort O(n²)]");
    sortCombo->addItem("Sort by GPA High→Low  [Quick Sort O(n log n)]");
    sortCombo->addItem("Sort by ID Ascending  [Bubble Sort O(n²)]");

    sortAlgoLabel = new QLabel("");
    sortAlgoLabel->setObjectName("undoLabel");

    sortBtn = new QPushButton("⬇️ Sort");
    sortBtn->setObjectName("updateBtn");

    QPushButton* showAllBtn = new QPushButton("📋 Show All");
    connect(showAllBtn, &QPushButton::clicked, this, &MainWindow::showAllStudents);

    sortLayout->addWidget(new QLabel("Sort by:"));
    sortLayout->addWidget(sortCombo);
    sortLayout->addWidget(sortBtn);
    sortLayout->addWidget(showAllBtn);
    sortLayout->addWidget(sortAlgoLabel);
    layout->addWidget(sortGroup);

    connect(searchBtn,      &QPushButton::clicked, this, &MainWindow::searchStudent);
    connect(clearSearchBtn, &QPushButton::clicked, this, &MainWindow::clearSearch);
    connect(sortBtn,        &QPushButton::clicked, this, &MainWindow::sortStudents);
}

void MainWindow::setupDSATab() {
    dsaTab = new QWidget();
    tabWidget->addTab(dsaTab, "🧠 DSA Visualization");

    QVBoxLayout* layout = new QVBoxLayout(dsaTab);

    QLabel* info = new QLabel(
        "Visualize the internal DSA structures used in this system:\n"
        "• Linked List: Primary storage (head → node1 → node2 → ... → NULL)\n"
        "• Binary Search Tree: Fast ID-based searching (O log n average)\n"
        "• Stack: Undo history (LIFO - Last In, First Out)"
    );
    info->setObjectName("subtitleLabel");
    info->setWordWrap(true);
    layout->addWidget(info);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    showLinkedListBtn = new QPushButton("🔗 Show Linked List");
    showBSTBtn        = new QPushButton("🌳 Show BST (Inorder)");
    showStackBtn      = new QPushButton("📚 Show Undo Stack");

    showLinkedListBtn->setObjectName("addBtn");
    showBSTBtn->setObjectName("updateBtn");

    btnLayout->addWidget(showLinkedListBtn);
    btnLayout->addWidget(showBSTBtn);
    btnLayout->addWidget(showStackBtn);
    layout->addLayout(btnLayout);

    dsaDisplay = new QTextEdit();
    dsaDisplay->setReadOnly(true);
    dsaDisplay->setFont(QFont("Courier New", 10));
    dsaDisplay->setObjectName("dsaDisplay");
    layout->addWidget(dsaDisplay);

    connect(showLinkedListBtn, &QPushButton::clicked, [this]() {
        dsaDisplay->setPlainText(generateLinkedListVisualization());
    });
    connect(showBSTBtn, &QPushButton::clicked, [this]() {
        dsaDisplay->setPlainText(generateBSTVisualization());
    });
    connect(showStackBtn, &QPushButton::clicked, [this]() {
        dsaDisplay->setPlainText(generateStackVisualization());
    });
}

// ============================================================
// CRUD OPERATIONS
// ============================================================
void MainWindow::addStudent() {
    int id = idSpin->value();
    if (linkedList->searchById(id)) {
        QMessageBox::warning(this, "Duplicate ID", QString("Student with ID %1 already exists!").arg(id));
        return;
    }
    if (nameEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Please enter the student name.");
        return;
    }

    Student s(id, nameEdit->text().trimmed(), deptEdit->text().trimmed(),
              gpaSpin->value(), ageSpin->value());

    linkedList->insertAtEnd(s);
    bst->insert(s);
    undoStack->pushAdd(s);

    refreshMainTable();
    updateStatusBar();
    undoLabel->setText(undoStack->topDescription());
    statusLabel->setText("✅ Student added successfully.");
    idSpin->setValue(idSpin->value() + 1);
}

void MainWindow::deleteStudent() {
    int row = studentTable->currentRow();
    if (row < 0) {
        QMessageBox::information(this, "Select Row", "Please select a student row to delete.");
        return;
    }

    int id = studentTable->item(row, 0)->text().toInt();
    Node* node = linkedList->searchById(id);
    if (!node) return;

    auto reply = QMessageBox::question(this, "Confirm Delete",
        QString("Delete student '%1' (ID: %2)?").arg(node->data.name).arg(id));
    if (reply != QMessageBox::Yes) return;

    undoStack->pushDelete(node->data);
    linkedList->deleteById(id);
    bst->remove(id);

    refreshMainTable();
    updateStatusBar();
    undoLabel->setText(undoStack->topDescription());
    statusLabel->setText("🗑️ Student deleted.");
}

void MainWindow::updateStudent() {
    int id = idSpin->value();
    Node* existing = linkedList->searchById(id);
    if (!existing) {
        QMessageBox::warning(this, "Not Found", QString("No student with ID %1 found.").arg(id));
        return;
    }
    if (nameEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Name cannot be empty.");
        return;
    }

    Student updated(id, nameEdit->text().trimmed(), deptEdit->text().trimmed(),
                    gpaSpin->value(), ageSpin->value());

    undoStack->pushUpdate(existing->data, updated);
    linkedList->updateStudent(id, updated);
    bst->remove(id);
    bst->insert(updated);

    refreshMainTable();
    updateStatusBar();
    undoLabel->setText(undoStack->topDescription());
    statusLabel->setText("✏️ Student updated successfully.");
}

void MainWindow::undoAction() {
    if (undoStack->isEmpty()) {
        QMessageBox::information(this, "Undo", "Nothing to undo!");
        return;
    }

    Action action = undoStack->pop();

    if (action.type == ADD) {
        // Undo add = delete the student
        linkedList->deleteById(action.studentData.id);
        bst->remove(action.studentData.id);
        statusLabel->setText("↩️ Undid: Add student");
    }
    else if (action.type == DELETE_ACTION) {
        // Undo delete = re-add
        linkedList->insertAtEnd(action.studentData);
        bst->insert(action.studentData);
        statusLabel->setText("↩️ Undid: Delete student");
    }
    else if (action.type == UPDATE) {
        // Undo update = restore previous data
        linkedList->updateStudent(action.previousData.id, action.previousData);
        bst->remove(action.studentData.id);
        bst->insert(action.previousData);
        statusLabel->setText("↩️ Undid: Update student");
    }

    refreshMainTable();
    updateStatusBar();
    undoLabel->setText(undoStack->isEmpty() ? "Nothing to undo" : undoStack->topDescription());
}

// ============================================================
// SEARCH & SORT
// ============================================================
void MainWindow::searchStudent() {
    QString query = searchEdit->text().trimmed();
    if (query.isEmpty()) {
        QMessageBox::information(this, "Search", "Please enter a search query.");
        return;
    }

    QVector<Student> results;
    int type = searchTypeCombo->currentIndex();

    if (type == 0) {
        // BST Search by ID
        bool ok;
        int id = query.toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Invalid", "Please enter a valid numeric ID.");
            return;
        }
        Student* s = bst->search(id);
        if (s) results.append(*s);
        sortAlgoLabel->setText("BST search: O(log n) average");
    } else {
        // Linked list search by name
        Node* curr = linkedList->getHead();
        while (curr) {
            if (curr->data.name.toLower().contains(query.toLower()))
                results.append(curr->data);
            curr = curr->next;
        }
        sortAlgoLabel->setText("Linked List search: O(n)");
    }

    refreshTable(results);
    // Show results in searchResultTable
    searchResultTable->setRowCount(0);
    for (auto& s : results) {
        int row = searchResultTable->rowCount();
        searchResultTable->insertRow(row);
        searchResultTable->setItem(row, 0, new QTableWidgetItem(QString::number(s.id)));
        searchResultTable->setItem(row, 1, new QTableWidgetItem(s.name));
        searchResultTable->setItem(row, 2, new QTableWidgetItem(s.department));
        searchResultTable->setItem(row, 3, new QTableWidgetItem(QString::number(s.age)));
        searchResultTable->setItem(row, 4, new QTableWidgetItem(QString::number(s.gpa, 'f', 2)));
    }

    statusLabel->setText(results.isEmpty()
        ? "❌ No students found."
        : QString("✅ Found %1 student(s).").arg(results.size()));
}

void MainWindow::clearSearch() {
    searchEdit->clear();
    searchResultTable->setRowCount(0);
    sortAlgoLabel->setText("");
    statusLabel->setText("Search cleared.");
}

void MainWindow::showAllStudents() {
    QVector<Student> all = linkedList->getAllStudents();
    searchResultTable->setRowCount(0);
    for (auto& s : all) {
        int row = searchResultTable->rowCount();
        searchResultTable->insertRow(row);
        searchResultTable->setItem(row, 0, new QTableWidgetItem(QString::number(s.id)));
        searchResultTable->setItem(row, 1, new QTableWidgetItem(s.name));
        searchResultTable->setItem(row, 2, new QTableWidgetItem(s.department));
        searchResultTable->setItem(row, 3, new QTableWidgetItem(QString::number(s.age)));
        searchResultTable->setItem(row, 4, new QTableWidgetItem(QString::number(s.gpa, 'f', 2)));
    }
    sortAlgoLabel->setText(QString("Showing all %1 students").arg(all.size()));
}

void MainWindow::sortStudents() {
    QVector<Student> students = linkedList->getAllStudents();
    QVector<Student> sorted;
    int idx = sortCombo->currentIndex();

    if (idx == 0) {
        sorted = SortingAlgorithms::bubbleSortByName(students);
        sortAlgoLabel->setText("Bubble Sort by Name — O(n²) time, O(1) space");
    } else if (idx == 1) {
        sorted = SortingAlgorithms::sortByGPA(students);
        sortAlgoLabel->setText("Quick Sort by GPA — O(n log n) avg time, O(log n) space");
    } else {
        sorted = SortingAlgorithms::bubbleSortById(students);
        sortAlgoLabel->setText("Bubble Sort by ID — O(n²) time, O(1) space");
    }

    searchResultTable->setRowCount(0);
    for (auto& s : sorted) {
        int row = searchResultTable->rowCount();
        searchResultTable->insertRow(row);
        searchResultTable->setItem(row, 0, new QTableWidgetItem(QString::number(s.id)));
        searchResultTable->setItem(row, 1, new QTableWidgetItem(s.name));
        searchResultTable->setItem(row, 2, new QTableWidgetItem(s.department));
        searchResultTable->setItem(row, 3, new QTableWidgetItem(QString::number(s.age)));
        searchResultTable->setItem(row, 4, new QTableWidgetItem(QString::number(s.gpa, 'f', 2)));
    }

    statusLabel->setText("✅ Sorted successfully.");
}

// ============================================================
// TABLE HELPERS
// ============================================================
void MainWindow::refreshMainTable() {
    QVector<Student> students = linkedList->getAllStudents();
    refreshTable(students);
}

void MainWindow::refreshTable(QVector<Student> students) {
    studentTable->setRowCount(0);
    for (auto& s : students) {
        int row = studentTable->rowCount();
        studentTable->insertRow(row);
        studentTable->setItem(row, 0, new QTableWidgetItem(QString::number(s.id)));
        studentTable->setItem(row, 1, new QTableWidgetItem(s.name));
        studentTable->setItem(row, 2, new QTableWidgetItem(s.department));
        studentTable->setItem(row, 3, new QTableWidgetItem(QString::number(s.age)));
        studentTable->setItem(row, 4, new QTableWidgetItem(QString::number(s.gpa, 'f', 2)));

        // Color code GPA
        QColor rowColor = (s.gpa >= 3.5) ? QColor(200, 255, 200) :
                          (s.gpa >= 2.5) ? QColor(255, 255, 200) :
                                           QColor(255, 200, 200);
        for (int c = 0; c < 5; c++)
            studentTable->item(row, c)->setBackground(rowColor);
    }
}

void MainWindow::updateStatusBar() {
    countLabel->setText(QString("Total Students: %1").arg(linkedList->getSize()));
}

void MainWindow::onTableRowSelected() {
    int row = studentTable->currentRow();
    if (row < 0) return;
    loadFormFromRow(row);
}

void MainWindow::loadFormFromRow(int row) {
    idSpin->setValue(studentTable->item(row, 0)->text().toInt());
    nameEdit->setText(studentTable->item(row, 1)->text());
    deptEdit->setText(studentTable->item(row, 2)->text());
    ageSpin->setValue(studentTable->item(row, 3)->text().toInt());
    gpaSpin->setValue(studentTable->item(row, 4)->text().toDouble());
}

void MainWindow::clearForm() {
    nameEdit->clear();
    deptEdit->clear();
    ageSpin->setValue(20);
    gpaSpin->setValue(3.0);
    studentTable->clearSelection();
}

void MainWindow::showDSAVisualization() {
    dsaDisplay->setPlainText(generateLinkedListVisualization());
}

// ============================================================
// DSA VISUALIZATION TEXT GENERATORS
// ============================================================
QString MainWindow::generateLinkedListVisualization() {
    QString result;
    result += "═══════════════════════════════════════════════════════\n";
    result += "           LINKED LIST VISUALIZATION\n";
    result += "═══════════════════════════════════════════════════════\n\n";
    result += "Structure: HEAD → [Node1] → [Node2] → ... → NULL\n";
    result += "Each node contains: Student data + pointer to next node\n\n";
    result += "Time Complexity: Insert O(1), Search O(n), Delete O(n)\n";
    result += "Space Complexity: O(n)\n\n";
    result += "─────────────────────────────────────────────────────\n";

    if (linkedList->isEmpty()) {
        result += "HEAD → NULL  (Empty List)\n";
        return result;
    }

    result += "HEAD\n  |\n  ↓\n";
    Node* curr = linkedList->getHead();
    int nodeNum = 1;
    while (curr) {
        result += QString("┌─────────────────────────────┐\n");
        result += QString("│ Node #%1                     │\n").arg(nodeNum);
        result += QString("│  ID:   %1\n").arg(curr->data.id);
        result += QString("│  Name: %1\n").arg(curr->data.name);
        result += QString("│  GPA:  %1\n").arg(curr->data.gpa, 0, 'f', 2);
        result += QString("│  Next: %1\n").arg(curr->next ? QString("→ Node #%1").arg(nodeNum+1) : "NULL");
        result += QString("└─────────────────────────────┘\n");
        if (curr->next) result += "  |\n  ↓\n";
        curr = curr->next;
        nodeNum++;
    }
    result += "\n  → NULL (End of List)\n";
    result += QString("\nTotal Nodes: %1\n").arg(linkedList->getSize());
    return result;
}

QString MainWindow::generateBSTVisualization() {
    QString result;
    result += "═══════════════════════════════════════════════════════\n";
    result += "       BINARY SEARCH TREE - INORDER TRAVERSAL\n";
    result += "═══════════════════════════════════════════════════════\n\n";
    result += "Property: Left child ID < Parent ID < Right child ID\n";
    result += "Inorder traversal gives students sorted by ID!\n\n";
    result += "Time Complexity: Search O(log n) avg, O(n) worst\n";
    result += "Space Complexity: O(n)\n\n";
    result += "─────────────────────────────────────────────────────\n";
    result += "Inorder Traversal (Sorted by ID):\n\n";

    QVector<Student> sorted = bst->inorderTraversal();
    if (sorted.isEmpty()) {
        result += "  (Empty BST)\n";
        return result;
    }

    for (int i = 0; i < sorted.size(); i++) {
        auto& s = sorted[i];
        result += QString("[%1] ID: %2 | %3 | GPA: %4\n")
            .arg(i+1).arg(s.id, 5).arg(s.name, -20).arg(s.gpa, 0, 'f', 2);
    }

    result += "\n─────────────────────────────────────────────────────\n";
    result += "BST Search Example:\n";
    result += "  To find ID=1003: Start at root → Compare → Go Left/Right\n";
    result += "  Much faster than linear search for large datasets!\n";
    return result;
}

QString MainWindow::generateStackVisualization() {
    QString result;
    result += "═══════════════════════════════════════════════════════\n";
    result += "              UNDO STACK VISUALIZATION\n";
    result += "═══════════════════════════════════════════════════════\n\n";
    result += "Structure: LIFO (Last In, First Out)\n";
    result += "TOP of stack is always the most recent action.\n\n";
    result += "Time Complexity: Push/Pop O(1)\n";
    result += "Space Complexity: O(n), max 20 actions\n\n";
    result += "─────────────────────────────────────────────────────\n";

    if (undoStack->isEmpty()) {
        result += "  Stack is EMPTY - no actions to undo\n";
        result += "\n  ┌─────────────────────┐\n";
        result += "  │       EMPTY          │  ← TOP\n";
        result += "  └─────────────────────┘\n";
        return result;
    }

    result += QString("Stack Size: %1 actions\n\n").arg(undoStack->size());
    result += "  ┌─────────────────────┐  ← TOP (Most Recent)\n";
    result += QString("  │ %1\n").arg(undoStack->topDescription());
    result += "  ├─────────────────────┤\n";
    result += "  │    ... older ...    │\n";
    result += "  └─────────────────────┘  ← BOTTOM\n\n";
    result += "Press 'Undo' button to pop and reverse the top action.\n";
    return result;
}

// ============================================================
// SAMPLE DATA
// ============================================================
void MainWindow::loadSampleData() {
    QVector<Student> samples = {
        {1001, "Alice Johnson",   "Computer Science",    3.85, 20},
        {1002, "Bob Martinez",    "Mathematics",         3.20, 22},
        {1003, "Clara Smith",     "Physics",             3.60, 21},
        {1004, "David Lee",       "Computer Science",    2.90, 23},
        {1005, "Emma Wilson",     "Electrical Eng.",     3.75, 20},
        {1006, "Frank Brown",     "Civil Engineering",   2.50, 24},
        {1007, "Grace Kim",       "Biotechnology",       3.95, 19},
    };

    for (auto& s : samples) {
        linkedList->insertAtEnd(s);
        bst->insert(s);
    }
}

// ============================================================
// STYLESHEET
// ============================================================
void MainWindow::applyStyleSheet() {
    qApp->setStyleSheet(R"(
        QMainWindow {
            background-color: #f0f4f8;
        }
        #titleLabel {
            font-size: 22px;
            font-weight: bold;
            color: #1a365d;
            padding: 8px;
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #667eea, stop:1 #764ba2);
            color: white;
            border-radius: 8px;
        }
        #subtitleLabel {
            font-size: 11px;
            color: #4a5568;
            padding: 4px;
            background-color: #edf2f7;
            border-radius: 4px;
        }
        QGroupBox {
            font-weight: bold;
            font-size: 12px;
            color: #2d3748;
            border: 2px solid #bee3f8;
            border-radius: 8px;
            margin-top: 8px;
            padding-top: 8px;
            background-color: #ffffff;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 5px;
            color: #2b6cb0;
        }
        QTableWidget {
            border: 1px solid #bee3f8;
            border-radius: 6px;
            background-color: #ffffff;
            gridline-color: #e2e8f0;
        }
        QTableWidget::item:selected {
            background-color: #bee3f8;
            color: #1a365d;
        }
        QHeaderView::section {
            background-color: #2b6cb0;
            color: white;
            padding: 6px;
            font-weight: bold;
            border: none;
        }
        QLineEdit, QSpinBox, QDoubleSpinBox, QComboBox {
            border: 2px solid #bee3f8;
            border-radius: 5px;
            padding: 5px 8px;
            font-size: 12px;
            background-color: #ffffff;
        }
        QLineEdit:focus, QSpinBox:focus, QDoubleSpinBox:focus {
            border-color: #667eea;
        }
        QPushButton {
            padding: 8px 14px;
            border-radius: 6px;
            font-size: 12px;
            font-weight: bold;
            border: none;
            background-color: #718096;
            color: white;
        }
        QPushButton:hover { background-color: #4a5568; }
        #addBtn {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #48bb78, stop:1 #38a169);
        }
        #addBtn:hover { background-color: #276749; }
        #updateBtn {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #667eea, stop:1 #764ba2);
        }
        #updateBtn:hover { background-color: #553c9a; }
        #deleteBtn {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #fc8181, stop:1 #e53e3e);
        }
        #deleteBtn:hover { background-color: #9b2c2c; }
        QTabWidget::pane {
            border: 2px solid #bee3f8;
            border-radius: 8px;
            background-color: #f7fafc;
        }
        QTabBar::tab {
            background-color: #e2e8f0;
            color: #4a5568;
            padding: 10px 18px;
            font-size: 12px;
            font-weight: bold;
            border-radius: 6px 6px 0 0;
        }
        QTabBar::tab:selected {
            background-color: #2b6cb0;
            color: white;
        }
        #undoLabel {
            color: #718096;
            font-size: 10px;
            font-style: italic;
        }
        #dsaDisplay {
            background-color: #1a202c;
            color: #68d391;
            font-family: "Courier New", monospace;
            font-size: 11px;
            border: 2px solid #2d3748;
            border-radius: 6px;
        }
        QStatusBar {
            background-color: #2b6cb0;
            color: white;
            font-size: 11px;
        }
    )");
}