#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi();

    //Connect the buttons and size spin box with their slots
    connect(m_sizeBox, SIGNAL(valueChanged(int)), m_matrixAWidget, SLOT(changeSize(int)));
    connect(m_sizeBox, SIGNAL(valueChanged(int)), m_matrixBWidget, SLOT(changeSize(int)));
    connect(m_multiplyButton, SIGNAL(clicked(bool)), this, SLOT(multiply()));
}

void MainWindow::setupUi()
{
    //Set window title and size
    setWindowTitle("QMatrixProduct");
    resize(1280, 720);
    m_centralWidget = new QWidget(this);

    //Create global vertical layout
    QVBoxLayout *verticalLayout = new QVBoxLayout(m_centralWidget);

    //Create horizontal splitter for 2 MatrixWidgets
    QSplitter *splitter = new QSplitter(m_centralWidget);
    splitter->setOrientation(Qt::Horizontal);

    //Create MatrixWidgets
    m_matrixAWidget = new MatrixWidget(splitter);
    m_matrixBWidget = new MatrixWidget(splitter);
    m_matrixAModel = m_matrixAWidget->model();
    m_matrixBModel = m_matrixBWidget->model();
    splitter->addWidget(m_matrixAWidget);
    splitter->addWidget(m_matrixBWidget);

    //Create horizontal layout for options
    //(boxes and buttons on the bottom of the window
    QHBoxLayout *optionsLayout = new QHBoxLayout();

    //Create label with "Size: " text
    QLabel *sizeLabel = new QLabel(m_centralWidget);
    sizeLabel->setText("Size:");
    optionsLayout->addWidget(sizeLabel);

    //Create spin box that sets matrices size
    m_sizeBox = new QSpinBox(m_centralWidget);
    m_sizeBox->setValue(64);
    m_sizeBox->setSingleStep(1);
    m_sizeBox->setMinimum(0);
    m_sizeBox->setMaximum(8192);
    optionsLayout->addWidget(m_sizeBox);

    //Create empty space between spin box and combo box
    QSpacerItem *optionsSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding);
    optionsLayout->addItem(optionsSpacer);

    //Create combo box that allows to choose from 3 algorithms
    m_algorithmBox = new QComboBox(m_centralWidget);
    m_algorithmBox->addItem("Strassen Algorithm");
    m_algorithmBox->addItem("Winograd-Strassen Algorithm");
    m_algorithmBox->addItem("Standard Algorithm");
    optionsLayout->addWidget(m_algorithmBox);

    //Create multiply button
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
    MatrixModel *matrixCModel = new MatrixModel();
    matrixCModel->setReadOnly(true);

    Matrix &A = m_matrixAModel.get()->matrix();
    Matrix &B = m_matrixBModel.get()->matrix();
    Matrix &C = matrixCModel->matrix();

    setCursor(Qt::WaitCursor);

    //Start timer
    QString time;
    QElapsedTimer timer;
    timer.start();

    switch (m_algorithmBox->currentIndex()) {
    case 0:     //Strassen algorithm
        //TODO: Strassen algorithm
        break;
    case 1:     //Winograd-Strassen algorithm
        //TODO: Winograd-Strassen algorithm
        break;
    case 2:     //Standard algorithm
        C = mp->standardMultiply(A, B);
        break;
    default:
        break;
    }

    //Stop timer
    auto msecsElapsed = timer.elapsed();
    auto nsecsElapsed = timer.nsecsElapsed();

    if (msecsElapsed < 10)     //Time is displayed in nanoseconds
        time = QString::number(nsecsElapsed) + "ns";
    else                        //Or in miliseconds if elapsed time >= 10ms
        time = QString::number(msecsElapsed) + "ms";

    setCursor(Qt::ArrowCursor);
    ResultsWindow *r = new ResultsWindow(matrixCModel, time, mp);
    r->show();
}
