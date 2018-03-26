#include <iostream>
#include <windows.h>

extern int func2();

#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
	QScopedPointer<QCoreApplication> app(new QCoreApplication(argc, argv));
	func2();
	MainWindow window;
	window.show();

	return app->exec();
}
