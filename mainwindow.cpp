#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi();
    connect(m_sizeBox, SIGNAL(valueChanged(int)), m_matrixAWidget, SLOT(changeSize(int)));
    connect(m_sizeBox, SIGNAL(valueChanged(int)), m_matrixBWidget, SLOT(changeSize(int)));
}

void MainWindow::setupUi()
{
    setWindowTitle("QMatrixProduct");
    resize(1280, 720);
    m_centralWidget = new QWidget(this);

    QVBoxLayout *verticalLayout = new QVBoxLayout(m_centralWidget);

    QSplitter *splitter = new QSplitter(m_centralWidget);
    splitter->setOrientation(Qt::Horizontal);

    m_matrixAWidget = new MatrixWidget(splitter);
    m_matrixBWidget = new MatrixWidget(splitter);
    m_matrixAModel = m_matrixAWidget->model();
    m_matrixBModel = m_matrixBWidget->model();
    splitter->addWidget(m_matrixAWidget);
    splitter->addWidget(m_matrixBWidget);

    QHBoxLayout *optionsLayout = new QHBoxLayout();

    QLabel *sizeLabel = new QLabel(m_centralWidget);
    sizeLabel->setText("Size:");
    optionsLayout->addWidget(sizeLabel);

    m_sizeBox = new QSpinBox(m_centralWidget);
    m_sizeBox->setValue(64);
    m_sizeBox->setSingleStep(1);
    m_sizeBox->setMinimum(0);
    m_sizeBox->setMaximum(8192);
    optionsLayout->addWidget(m_sizeBox);

    QSpacerItem *optionsSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding);
    optionsLayout->addItem(optionsSpacer);

    m_algorithmBox = new QComboBox(m_centralWidget);
    m_algorithmBox->addItem("Strassen Algorithm", 0);
    m_algorithmBox->addItem("Winograd-Strassen Algorithm", 1);
    m_algorithmBox->addItem("Standard Algorithm", 2);
    optionsLayout->addWidget(m_algorithmBox);

    m_multiplyButton = new QPushButton(m_centralWidget);
    m_multiplyButton->setText("Multiply...");
    optionsLayout->addWidget(m_multiplyButton);

    verticalLayout->addWidget(splitter);
    verticalLayout->addLayout(optionsLayout);
    setCentralWidget(m_centralWidget);
}
