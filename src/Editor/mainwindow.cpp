#include <QtGui/QtGui>
#include "mainwindow.h"
#include "GraphWidget.h"
#include "config.h"
#include "GraphUtils.h"

MainWindow::MainWindow() : m_pGraphWidget(new GraphWidget(Config::NumCellsX, Config::NumCellsY)),
m_breadthFirstSearchBtn(nullptr), m_dijkstraSearchBtn(nullptr), m_aStarSearchBtn(nullptr) {
    setWindowTitle("Editor");
    setupUi();
    this->resize(550, 480);
    setFixedSize(770, 560);
    setWindowIcon(QIcon(":/astar.png"));

    /*
     * Load Stylesheet.
     */
    QFile stylesheet(":/styles.qss");
    if (stylesheet.open(QFile::ReadOnly))
        setStyleSheet(stylesheet.readAll());

    createActions();
    createMenus();

    auto aName = m_dijkstraSearchBtn->objectName();
    connect(m_dijkstraSearchBtn, &QPushButton::clicked, this, [aName, this]() {
        m_pGraphWidget->pathDijkstra();
    });
    aName = m_breadthFirstSearchBtn->objectName();
    connect(m_breadthFirstSearchBtn, &QPushButton::clicked, this, [aName, this]() {
        m_pGraphWidget->pathBFS();
    });
    aName = m_aStarSearchBtn->objectName();
    connect(m_aStarSearchBtn, &QPushButton::clicked, this, [aName, this]() {
        m_pGraphWidget->pathAStar();
    });
    connect(m_pGraphWidget, &GraphWidget::changedGraph, this, &MainWindow::updateGraphStats);

    aName = m_planarBtn->objectName();
    connect(m_planarBtn, &QPushButton::clicked, this, [aName, this]() {
        setPressedButton(m_planarBtn);
        m_pGraphWidget->setCurTerrain(field_type::planar);
    });
    aName = m_wallBtn->objectName();
    connect(m_wallBtn, &QPushButton::clicked, this, [aName, this]() {
        setPressedButton(m_wallBtn);
        m_pGraphWidget->setCurTerrain(field_type::wall);
    });
    aName = m_waterBtn->objectName();
    connect(m_waterBtn, &QPushButton::clicked, this, [aName, this]() {
        setPressedButton(m_waterBtn);
        m_pGraphWidget->setCurTerrain(field_type::water);
    });
    aName = m_hillBtn->objectName();
    connect(m_hillBtn, &QPushButton::clicked, this, [aName, this]() {
        setPressedButton(m_hillBtn);
        m_pGraphWidget->setCurTerrain(field_type::hill);
    });
    aName = m_targetBtn->objectName();
    connect(m_targetBtn, &QPushButton::clicked, this, [aName, this]() {
        setPressedButton(m_targetBtn);
        m_pGraphWidget->setCurTerrain(field_type::target);
    });
    aName = m_srcBtn->objectName();
    connect(m_srcBtn, &QPushButton::clicked, this, [aName, this]() {
        setPressedButton(m_srcBtn);
        m_pGraphWidget->setCurTerrain(field_type::source);
    });
    aName = m_applyBtn->objectName();
    connect(m_applyBtn, &QPushButton::clicked, this, [aName, this]() {
        m_pGraphWidget->createGraph(
                500,
                500,
                m_xDimEd->text().toInt(),
                m_yDimEd->text().toInt());
    });
}

void MainWindow::setupUi() {
    m_aStarSearchBtn = new QPushButton("A Star");
    m_breadthFirstSearchBtn = new QPushButton("Breitensuche");
    m_dijkstraSearchBtn = new QPushButton("Dijkstra");
    m_wallBtn = new QPushButton("Wand");
    m_planarBtn = new QPushButton("Ebene");
    m_waterBtn = new QPushButton("Wasser");
    m_hillBtn = new QPushButton("Gebirge");
    m_srcBtn = new QPushButton("Start");
    m_targetBtn = new QPushButton("End");
    m_currPressedBtn = m_planarBtn;
    m_planarBtn->setCheckable(true);
    m_numEdges = new QLabel(QString::number(m_pGraphWidget->numEdges()));
    m_numNodes = new QLabel(QString::number(m_pGraphWidget->numNodes()));
    m_totalCost = new QLabel("0");
    m_totalTime = new QLabel("0");
    m_applyBtn = new QPushButton("Anwenden");
    QRegExp re("[0-9]+");
    QRegExpValidator *validator = new QRegExpValidator(re, this);
    m_xDimEd = new QLineEdit;
    m_yDimEd = new QLineEdit;
    m_xDimEd->setValidator(validator);
    m_yDimEd->setValidator(validator);
    m_xDimEd->setText(QString::number(Config::NumCellsX));
    m_yDimEd->setText(QString::number(Config::NumCellsY));
    QHBoxLayout *hboxLayout = new QHBoxLayout;
    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    QVBoxLayout *mainVBox = new QVBoxLayout;
    QHBoxLayout *mapLayout = new QHBoxLayout;
    QHBoxLayout *lay = new QHBoxLayout;
    QHBoxLayout *lay1 = new QHBoxLayout;
    QHBoxLayout *lay2 = new QHBoxLayout;
    QHBoxLayout *lay3 = new QHBoxLayout;
    QHBoxLayout *lay4 = new QHBoxLayout;
    QHBoxLayout *lay5 = new QHBoxLayout;
    QHBoxLayout *lay6 = new QHBoxLayout;
    vBoxLayout->addWidget(new QLabel("Map-Dimension:"));
    vBoxLayout->addLayout(mapLayout);
    vBoxLayout->addWidget(new QLabel("Such-Algorithmen"));
    vBoxLayout->addWidget(m_breadthFirstSearchBtn);
    vBoxLayout->addWidget(m_dijkstraSearchBtn);
    vBoxLayout->addWidget(m_aStarSearchBtn);
    vBoxLayout->addWidget(new QLabel("Feld Typen:"));
    lay->addWidget(m_planarBtn);
    lay->addWidget(m_waterBtn);
    lay1->addWidget(m_hillBtn);
    lay1->addWidget(m_wallBtn);
    lay2->addWidget(m_srcBtn);
    lay2->addWidget(m_targetBtn);
    lay3->addWidget(new QLabel("Knoten:"));
    lay3->addWidget(m_numNodes);
    lay4->addWidget(new QLabel("Kanten:"));
    lay4->addWidget(m_numEdges);
    lay5->addWidget(new QLabel("Gesamt Kosten:"));
    lay5->addWidget(m_totalCost);
    lay6->addWidget(new QLabel("Gesamt Zeit:"));
    lay6->addWidget(m_totalTime);
    vBoxLayout->addLayout(lay);
    vBoxLayout->addLayout(lay1);
    vBoxLayout->addLayout(lay2);
    vBoxLayout->addWidget(new QLabel("Graph Stats:"));
    vBoxLayout->addLayout(lay3);
    vBoxLayout->addLayout(lay4);
    vBoxLayout->addLayout(lay5);
    vBoxLayout->addLayout(lay6);
    vBoxLayout->setAlignment(Qt::AlignTop);
    vBoxLayout->setSpacing(5);

    mapLayout->addWidget(new QLabel("x:"));
    mapLayout->addWidget(m_xDimEd);
    mapLayout->addWidget(new QLabel("y:"));
    mapLayout->addWidget(m_yDimEd);
    mapLayout->addWidget(m_applyBtn);

    mainVBox->addWidget(m_pGraphWidget);
    mainVBox->setContentsMargins(0, 0, 0, 0);

    hboxLayout->addLayout(mainVBox);
    hboxLayout->addLayout(vBoxLayout);
    hboxLayout->setAlignment(Qt::AlignTop);
    hboxLayout->setSpacing(10);
    hboxLayout->setContentsMargins(5, 5, 5, 5);
    QWidget* myWidget = new QWidget(this);
    myWidget->setLayout(hboxLayout);
    this->setCentralWidget(myWidget);
    this->layout()->setContentsMargins(0, 0, 0, 0);
    this->layout()->setSpacing(0);
}

MainWindow::~MainWindow() {
    if (m_pGraphWidget) {
        delete m_pGraphWidget;
        m_pGraphWidget = nullptr;
    }
}

void MainWindow::createMenus() {
    menuBar()->addAction(m_showGraphAct);
    menuBar()->addAction(m_debugGraphAct);
    menuBar()->addAction(m_aboutAct);
    menuBar()->addAction(m_exitAct);
}

void MainWindow::createActions() {
    m_showGraphAct = new QAction(tr("&Graph"), this);
    m_showGraphAct->setStatusTip("Zeigt Kanten und Ecken des Graphen");
    connect(m_showGraphAct, &QAction::triggered, this, &MainWindow::showGraph);


    m_aboutAct = new QAction(tr("&About"), this);
    m_aboutAct->setStatusTip("Zeige about Informationen an");
    auto aName = m_aboutAct->objectName();
    connect(m_aboutAct, &QAction::triggered, this, [aName,this]() {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("About");
        msgBox.setText("Von: Ömer Ergan, Paul Masch, Chikita Hans, Jannes Kretschmer<br>"
                       "<b>Algorithmen und Datenstrukturen II</b><br>"
                       "Hochschule München 2018 "
                       "<a style=color:dodgerblue href=\"https://github.com/ob-algdatii-ss18/leistungsnachweis-a-team-1\">Github</a>");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    });

    m_debugGraphAct = new QAction(tr("&Debug"), this);
    m_debugGraphAct->setStatusTip("Show debug info");
    connect(m_debugGraphAct, &QAction::triggered, this, [aName,this]() {
        m_pGraphWidget->printGraph();
    });

    m_exitAct = new QAction(tr("&Exit"), this);
    m_exitAct->setStatusTip("Beendet das Programm");

    aName = m_exitAct->objectName();
    connect(m_exitAct, &QAction::triggered, this, [aName,this]() {
        QApplication::quit();
    });
}

void MainWindow::showGraph() {
    m_pGraphWidget->showGraph(!m_pGraphWidget->isGraphVisible());
}

void MainWindow::updateGraphStats(GraphWidget::Graph_t &graph) {
    m_numEdges->setText(QString::number(graph.num_edges()));
    m_numNodes->setText(QString::number(graph.num_nodes()));
    m_totalCost->setText(QString::number(m_pGraphWidget->getTotalCost()));
    m_totalTime->setText(QString::number(m_pGraphWidget->getTotalTime()) + QString("ns"));
}

void MainWindow::setPressedButton(QPushButton *button) {
    if (button == m_currPressedBtn || m_currPressedBtn == nullptr) {
        return;
    }

    m_currPressedBtn->setChecked(false);
    button->setCheckable(true);
    m_currPressedBtn = button;
}

