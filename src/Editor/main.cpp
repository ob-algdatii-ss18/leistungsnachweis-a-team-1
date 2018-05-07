#include <QApplication>
#include <QScopedPointer>

#include "mainwindow.h"

#include <Graph.h>
#include <iostream>

int main(int argc, char* argv[]) {
    Weighted_graph<double> g;
    g.add_node();
    g.add_node();
    g.add_node();
    g.add_node();

    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(3, 2);
    auto ei = g.edges();
    auto i = ei.first;
    for (; i != ei.second; ++i) {
        std::cout << *i << std::endl;
    }

    QScopedPointer<QApplication> app(new QApplication(argc, argv));
    MainWindow editor;
    editor.show();
    app->exec();
}
