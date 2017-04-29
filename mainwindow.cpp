#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi();
    connect(m_sizeBox, SIGNAL(valueChanged(int)), m_matrixAWidget, SLOT(changeSize(int)));
    connect(m_sizeBox, SIGNAL(valueChanged(int)), m_matrixBWidget, SLOT(changeSize(int)));
    connect(m_multiplyButton, SIGNAL(clicked(bool)), this, SLOT(multiply()));
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
    m_algorithmBox->addItem("Strassen Algorithm");
    m_algorithmBox->addItem("Winograd-Strassen Algorithm");
    m_algorithmBox->addItem("Standard Algorithm");
    optionsLayout->addWidget(m_algorithmBox);

    m_multiplyButton = new QPushButton(m_centralWidget);
    m_multiplyButton->setText("Multiply...");
    optionsLayout->addWidget(m_multiplyButton);

    verticalLayout->addWidget(splitter);
    verticalLayout->addLayout(optionsLayout);
    setCentralWidget(m_centralWidget);
}

void MainWindow::multiply()
{
    MatrixProduct *mp = new MatrixProduct;
    Matrix &A = m_matrixAModel.get()->matrix();
    Matrix &B = m_matrixBModel.get()->matrix();
    MatrixModel *matrixCModel = new MatrixModel();
    Matrix &C = matrixCModel->matrix();
    QString time;
    QElapsedTimer timer;
    timer.start();

    switch (m_algorithmBox->currentIndex()) {
    case 0:
        //TODO: Strassen algorithm
        break;
    case 1:
        //TODO: Winograd-Strassen algorithm
        break;
    case 2:
        C = mp->standardMultiply(A, B);
        break;
    default:
        break;
    }

    auto msecsElapsed = timer.elapsed();
    auto nsecsElapsed = timer.nsecsElapsed();

    if (msecsElapsed < 100)
        time = QString::number(nsecsElapsed) + "ns";
    else
        time = QString::number(msecsElapsed) + "ms";

    ResultsWindow *r = new ResultsWindow(matrixCModel, time, mp);
    r->show();
}
