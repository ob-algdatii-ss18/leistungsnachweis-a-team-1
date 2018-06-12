#pragma once

#include <QtWidgets>
#include "GraphWidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow() override;

	void setupUi();

private slots:
	void showGraph();
	void dijkstraSearch();
	void BFS();
	void aStarSearch();
	void updateGraphStats(GraphWidget::Graph_t& graph);

private:
	void createMenus();
	void createActions();

private:
	GraphWidget * m_pGraphWidget;
	QVBoxLayout m_vBoxLayout;

	QMenu *m_showMenu;
	QAction *m_showGraphAct;
	QAction *m_aboutAct;
	QAction *m_exitAct;
	QPushButton *m_breadthFirstSearchBtn;
	QPushButton *m_dijkstraSearchBtn;
	QPushButton *m_aStarSearchBtn;
	QPushButton *m_hillBtn;
	QPushButton *m_planarBtn;
	QPushButton *m_waterBtn;
	QPushButton *m_wallBtn;
	QPushButton *m_targetBtn;
	QPushButton *m_srcBtn;
	QLabel *m_numNodes;
	QLabel *m_numEdges;
};
