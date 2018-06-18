#pragma once

#include <QtWidgets>
#include "GraphWidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow() override;

	void setPressedButton(QPushButton* button);
	void setupUi();

private slots:
	void showGraph();
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
	QAction *m_debugGraphAct;
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
	QPushButton *m_applyBtn;
	QPushButton *m_currPressedBtn;
	QLineEdit *m_xDimEd;
	QLineEdit *m_yDimEd;
	QLabel *m_numNodes;
	QLabel *m_numEdges;
	QLabel *m_totalCost;
	QLabel *m_totalTime;
};
