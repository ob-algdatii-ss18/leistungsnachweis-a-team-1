#include <QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QScopedPointer<QApplication> app(new QApplication(argc, argv));
    MainWindow editor;
    editor.show();
    app->exec();
}
