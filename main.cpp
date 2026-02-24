#include "mainwindow.h"
#include <QApplication>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Student Record Management System");
    app.setOrganizationName("DSA Project");
    app.setFont(QFont("Segoe UI", 10));

    MainWindow window;
    window.show();

    return app.exec();
}
