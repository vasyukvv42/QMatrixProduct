#include "matrixwidget.h"

MatrixWidget::MatrixWidget(QWidget *parent) : QWidget(parent)
{
    setupUi();
}

void MatrixWidget::setupUi()
{
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);

    matrixModel = new MatrixModel();

    tableView = new QTableView(this);
    tableView->setModel(matrixModel);
    tableView->verticalHeader()->hide();
    tableView->horizontalHeader()->hide();
    tableView->verticalHeader()->setDefaultSectionSize(40);
    tableView->horizontalHeader()->setDefaultSectionSize(40);
    verticalLayout->addWidget(tableView);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    QSpacerItem *leftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding);
    buttonsLayout->addItem(leftSpacer);

    randomizeButton = new QPushButton(this);
    randomizeButton->setText(QString("Randomize"));
    buttonsLayout->addWidget(randomizeButton);

    importButton = new QPushButton(this);
    importButton->setText(QString("Import..."));
    buttonsLayout->addWidget(importButton);

    QSpacerItem *rightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding);
    buttonsLayout->addItem(rightSpacer);

    verticalLayout->addLayout(buttonsLayout);
}

MatrixModel* MatrixWidget::model()
{
    return matrixModel;
}

void MatrixWidget::changeSize(int new_size)
{
    matrixModel->changeSize(new_size);
}
