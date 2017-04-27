#include "matrixwidget.h"

MatrixWidget::MatrixWidget(QWidget *parent) : QWidget(parent)
{
    setupUi();
    connect(m_randomizeButton, SIGNAL(clicked(bool)), this, SLOT(randomize()));
    connect(m_importButton, SIGNAL(clicked(bool)), this, SLOT(import()));
}

void MatrixWidget::setupUi()
{
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);

    m_matrixModel = new MatrixModel();

    m_tableView = new QTableView(this);
    m_tableView->setModel(m_matrixModel);
    m_tableView->verticalHeader()->hide();
    m_tableView->horizontalHeader()->hide();
    m_tableView->verticalHeader()->setDefaultSectionSize(40);
    m_tableView->horizontalHeader()->setDefaultSectionSize(40);
    verticalLayout->addWidget(m_tableView);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    QSpacerItem *leftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding);
    buttonsLayout->addItem(leftSpacer);

    m_randomizeButton = new QPushButton(this);
    m_randomizeButton->setText("Randomize");
    buttonsLayout->addWidget(m_randomizeButton);

    m_importButton = new QPushButton(this);
    m_importButton->setText("Import...");
    buttonsLayout->addWidget(m_importButton);

    QSpacerItem *rightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding);
    buttonsLayout->addItem(rightSpacer);

    verticalLayout->addLayout(buttonsLayout);
}

MatrixModel* MatrixWidget::model()
{
    return m_matrixModel;
}

void MatrixWidget::changeSize(int new_size)
{
    m_matrixModel->changeSize(new_size);
}

void MatrixWidget::randomize()
{
    m_matrixModel->randomize();
}

void MatrixWidget::import()
{
    QString filename = QFileDialog::getOpenFileName(this, "Import matrix",
                                                    QDir::homePath(), "Text files (*.txt)");
    m_matrixModel->importFromFile(filename);
}
