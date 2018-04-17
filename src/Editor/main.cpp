#include <iostream>

#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QScopedPointer<QApplication> app(new QApplication(argc, argv));
    MainWindow window;
    window.show();
    return app->exec();
}
