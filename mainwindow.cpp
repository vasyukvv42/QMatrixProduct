#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi();
    connect(sizeBox, SIGNAL(valueChanged(int)), matrixAWidget, SLOT(changeSize(int)));
    connect(sizeBox, SIGNAL(valueChanged(int)), matrixBWidget, SLOT(changeSize(int)));
}

void MainWindow::setupUi()
{
    setWindowTitle(QString("QMatrixProduct"));
    resize(1280, 720);
    centralWidget = new QWidget(this);

    QVBoxLayout *verticalLayout = new QVBoxLayout(centralWidget);

    QSplitter *splitter = new QSplitter(centralWidget);
    splitter->setOrientation(Qt::Horizontal);

    matrixAWidget = new MatrixWidget(splitter);
    matrixBWidget = new MatrixWidget(splitter);
    matrixAModel = matrixAWidget->model();
    matrixBModel = matrixBWidget->model();
    splitter->addWidget(matrixAWidget);
    splitter->addWidget(matrixBWidget);

    QHBoxLayout *optionsLayout = new QHBoxLayout();

    QLabel *sizeLabel = new QLabel(centralWidget);
    sizeLabel->setText(QString("Size:"));
    optionsLayout->addWidget(sizeLabel);

    sizeBox = new QSpinBox(centralWidget);
    sizeBox->setValue(64);
    sizeBox->setSingleStep(1);
    sizeBox->setMinimum(0);
    sizeBox->setMaximum(8192);
    optionsLayout->addWidget(sizeBox);

    QSpacerItem *optionsSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding);
    optionsLayout->addItem(optionsSpacer);

    algorithmBox = new QComboBox(centralWidget);
    algorithmBox->addItem(QString("Strassen Algorithm"), 0);
    algorithmBox->addItem(QString("Winograd-Strassen Algorithm"), 1);
    algorithmBox->addItem(QString("Standard Algorithm"), 2);
    optionsLayout->addWidget(algorithmBox);

    multiplyButton = new QPushButton(centralWidget);
    multiplyButton->setText(QString("Multiply..."));
    optionsLayout->addWidget(multiplyButton);

    verticalLayout->addWidget(splitter);
    verticalLayout->addLayout(optionsLayout);
    setCentralWidget(centralWidget);
}
