#include <iostream>

extern int func2();

#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QScopedPointer<QApplication> app(new QApplication(argc, argv));
    func2();
    MainWindow window;
    window.show();

    return app->exec();
}
