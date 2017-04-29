#include "resultswindow.h"

ResultsWindow::ResultsWindow(std::shared_ptr<MatrixModel> matrixModel, const QString &time,
                             std::shared_ptr<MatrixProduct> mp, QWidget *parent) :
    QWidget(parent), m_matrixModel(matrixModel), m_time(time), m_matrixProduct(mp)
{
    setupUi();
}

void ResultsWindow::setupUi()
{
    setWindowTitle("Results");
    resize(1280, 720);

    QGridLayout *gridLayout = new QGridLayout(this);

    m_tableView = new QTableView(this);
    m_tableView->setModel(m_matrixModel.get());
    m_tableView->verticalHeader()->hide();
    m_tableView->horizontalHeader()->hide();
    m_tableView->verticalHeader()->setDefaultSectionSize(50);
    m_tableView->horizontalHeader()->setDefaultSectionSize(50);
    gridLayout->addWidget(m_tableView, 0, 0, 5, 5);

    m_exportButton = new QPushButton(this);
    m_exportButton->setText("Export...");
    gridLayout->addWidget(m_exportButton, 0, 5, 1, 1);

    QGroupBox *statisticsBox = new QGroupBox(this);
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Time spent:", createLabel(m_time));
    formLayout->addRow("Additions: ",
                       createLabel(QString::number(m_matrixProduct->additions())));
    formLayout->addRow("Multiplications: ",
                       createLabel(QString::number(m_matrixProduct->multiplications())));
    formLayout->addRow("Function calls: ",
                       createLabel(QString::number(m_matrixProduct->functionCalls())));
    statisticsBox->setLayout(formLayout);
    statisticsBox->setTitle("Statistics");

    gridLayout->addWidget(statisticsBox, 4, 5, 1, 1);
}

QLabel *ResultsWindow::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignRight);
    return label;
}
