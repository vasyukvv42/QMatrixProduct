#include "mainwindow.h"

namespace qmatrixproduct {

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi();

    //Connect the buttons and size spin box with their slots
    connect(m_sizeBox, SIGNAL(valueChanged(int)), m_matrixAWidget, SLOT(onSizeBoxChanged(int)));
    connect(m_sizeBox, SIGNAL(valueChanged(int)), m_matrixBWidget, SLOT(onSizeBoxChanged(int)));
    connect(m_multiplyButton, SIGNAL(clicked(bool)), this, SLOT(onMultiplyButtonClicked()));
}

void MainWindow::setupUi()
{
    //Set window title and size
    setWindowTitle("QMatrixProduct");
    resize(960, 540);
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
    m_sizeBox->setMaximum(4096);
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

void MainWindow::onMultiplyButtonClicked()
{
    MatrixProduct *mp = new MatrixProduct;
    MatrixModel *matrixCModel = new MatrixModel();
    matrixCModel->setReadOnly(true);

    SquareMatrix &A = m_matrixAModel.get()->matrix();
    SquareMatrix &B = m_matrixBModel.get()->matrix();
    SquareMatrix &C = matrixCModel->matrix();

    setCursor(Qt::WaitCursor);

    //Start timer
    QString time;
    QElapsedTimer timer;
    timer.start();

    int algorithmIndex = m_algorithmBox->currentIndex();

    switch (algorithmIndex) {
    case 0:   //Strassen algorithm
        C = mp->strassenMultiply(A, B);
        break;
    case 1:   //Winograd-Strassen algorithm
        C = mp->winogradMultiply(A, B);
        break;
    case 2:   //Standard algorithm
        C = mp->standardMultiply(A, B);
        break;
    default:
        break;
    }

    //Stop timer
    auto nsecsElapsed = timer.nsecsElapsed();
    auto msecsElapsed = timer.elapsed();
    time = (msecsElapsed <= 1) ? QString::number(nsecsElapsed) + "ns"
                               : QString::number(msecsElapsed) + "ms";

    setCursor(Qt::ArrowCursor);

    ResultsWindow *r = new ResultsWindow(matrixCModel, time, mp, algorithmIndex);
    r->show();
}

} // namespace qmatrixproduct
