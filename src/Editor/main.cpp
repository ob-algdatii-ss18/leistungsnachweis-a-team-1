#include <QApplication>
#include <QScopedPointer>

#include "mainwindow.h"
#include "MazeAsciiVisualizer.h"

#include <Graph.h>
#include <iostream>
#include <Maze.h>

void visitNeighbours(Graph_base<Maze::Field *, no_property>::node_descriptor field, Maze *maze,
                     MazeAsciiVisualizer *mazeVisualizer, QPlainTextEdit *textField,
                     std::map<Graph_base<Maze::Field *, no_property>::node_descriptor, Graph_base<Maze::Field *, no_property>::node_descriptor> *ancestors) {
    maze->getGraph()->get(field)->visit();
    mazeVisualizer->visualize(maze);
    textField->repaint();
    for (auto edge : maze->getGraph()->out_edge_list(field)) {
        if (!maze->getGraph()->get(edge._to)->_visited) {
            (*ancestors)[edge._to] = field;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            visitNeighbours(edge._to, maze, mazeVisualizer, textField, ancestors);
        }
    }
}


int main(int argc, char *argv[]) {
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

    auto maze = new Maze("#############\n"
                         "#S# #   ###E#\n"
                         "# # # #   # #\n"
                         "# # # # ### #\n"
                         "#     # #   #\n"
                         "# ##### # ###\n"
                         "#   #       #\n"
                         "#############\n");

    QScopedPointer<QApplication> app(new QApplication(argc, argv));

    auto textField = new QPlainTextEdit();
    textField->setMinimumWidth(700);
    textField->setMinimumHeight(400);
    auto mazeVisualizer = new MazeAsciiVisualizer(textField);

    mazeVisualizer->visualize(maze);


    auto layout = new QVBoxLayout();
    layout->addWidget(textField);

    auto *window = new QWidget;
    window->setLayout(layout);
    window->show();
    app->processEvents();

    std::map<Graph_base<Maze::Field *, no_property>::node_descriptor, Graph_base<Maze::Field *, no_property>::node_descriptor> ancestors;

    auto tmp = maze->getEnd();
    visitNeighbours(maze->getStart(), maze, mazeVisualizer, textField, &ancestors);
    while (tmp != maze->getStart()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        maze->getGraph()->get(tmp)->setInShortestPath();
        mazeVisualizer->visualize(maze);
        textField->repaint();
        tmp = ancestors[tmp];
    }

    app->exec();
}
