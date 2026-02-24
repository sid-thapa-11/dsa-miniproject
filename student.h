#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

struct Student {
    int id;
    QString name;
    QString department;
    double gpa;
    int age;

    Student() : id(0), name(""), department(""), gpa(0.0), age(0) {}
    Student(int id, QString name, QString dept, double gpa, int age)
        : id(id), name(name), department(dept), gpa(gpa), age(age) {}

    QString toString() const {
        return QString("ID: %1 | Name: %2 | Dept: %3 | GPA: %4 | Age: %5")
            .arg(id).arg(name).arg(department).arg(gpa, 0, 'f', 2).arg(age);
    }
};

#endif // STUDENT_H
