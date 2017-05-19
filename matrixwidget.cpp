#include "matrixwidget.h"

namespace qmatrixproduct {

MatrixWidget::MatrixWidget(QWidget *parent) : QWidget(parent)
{
    setupUi();

    //Connect two buttons with their slots
    connect(m_randomizeButton, SIGNAL(clicked(bool)), this, SLOT(onRandomizeButtonClicked()));
    connect(m_importButton, SIGNAL(clicked(bool)), this, SLOT(onImportButtonClicked()));
}

void MatrixWidget::setupUi()
{
    //Create global vertical layout
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);

    //MatrixModel in this widget is shared with MainWindow
    m_matrixModel = std::make_shared<MatrixModel>();

    //Create table view for the matrix, hide headers and change cell size
    m_tableView = new QTableView(this);
    m_tableView->setModel(m_matrixModel.get());
    m_tableView->verticalHeader()->hide();
    m_tableView->horizontalHeader()->hide();
    m_tableView->verticalHeader()->setDefaultSectionSize(40);
    m_tableView->horizontalHeader()->setDefaultSectionSize(40);
    verticalLayout->addWidget(m_tableView);

    //Create horizontal layout for the buttons
    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    //Create empty space to the left of Randomize button
    QSpacerItem *leftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding);
    buttonsLayout->addItem(leftSpacer);

    //Create the Randomize button
    m_randomizeButton = new QPushButton(this);
    m_randomizeButton->setText("Randomize");
    buttonsLayout->addWidget(m_randomizeButton);

    //Create the Import button
    m_importButton = new QPushButton(this);
    m_importButton->setText("Import...");
    buttonsLayout->addWidget(m_importButton);

    //Create empty space to the right of Import button
    QSpacerItem *rightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding);
    buttonsLayout->addItem(rightSpacer);

    verticalLayout->addLayout(buttonsLayout);
}

std::shared_ptr<MatrixModel> MatrixWidget::model()
{
    return m_matrixModel;
}

void MatrixWidget::onSizeBoxChanged(int new_size)
{
    m_matrixModel->changeSize(new_size);
}

void MatrixWidget::onRandomizeButtonClicked()
{
    m_matrixModel->randomize();
}

void MatrixWidget::onImportButtonClicked()
{
    //Open a QFileDialog to choose a text file
    QString filename = QFileDialog::getOpenFileName(this, "Import Matrix",
                                                    QDir::homePath(),
                                                    "Text files (*.txt)");
    m_matrixModel->importFromFile(filename);
}

} // namespace qmatrixproduct
