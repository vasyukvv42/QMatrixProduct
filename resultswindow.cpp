#include "resultswindow.h"

namespace qmatrixproduct {

ResultsWindow::ResultsWindow(MatrixModel *matrixModel, const QString &time,
                             MatrixProduct *mp, int algorithmIndex, QWidget *parent) :
    QWidget(parent),
    m_matrixModel(matrixModel),
    m_time(time),
    m_matrixProduct(mp),
    m_algorithmIndex(algorithmIndex)
{
    setupUi();

    //Connect the "Export" button to its slot
    connect(m_exportButton, SIGNAL(clicked(bool)), this, SLOT(onExportButtonClicked()));
}

void ResultsWindow::setupUi()
{
    //Set window title and size
    //TODO: check how this window looks on Windows, it might have no title bar lol
    setWindowTitle("Results");
    resize(800, 600);
    setWindowFlags(Qt::Window);

    //Create global grid layout
    QGridLayout *gridLayout = new QGridLayout(this);

    /* Create table view for the resulting matrix
     * Cell size is slightly larger than in MainWindow
     * This table view takes around 5/6 of the window
     */
    m_tableView = new QTableView(this);
    m_tableView->setModel(m_matrixModel.get());
    m_tableView->verticalHeader()->hide();
    m_tableView->horizontalHeader()->hide();
    m_tableView->verticalHeader()->setDefaultSectionSize(50);
    m_tableView->horizontalHeader()->setDefaultSectionSize(50);
    gridLayout->addWidget(m_tableView, 0, 0, 5, 5);

    //Create Export button
    m_exportButton = new QPushButton(this);
    m_exportButton->setText("Export...");
    gridLayout->addWidget(m_exportButton, 0, 5, 1, 1);

    /* Create group box for displaying statistics
     * This group box is a form layout of QLabel: QLabel pairs
     */
    QGroupBox *statisticsBox = new QGroupBox(this);
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Time elapsed:", createLabel(m_time));
    formLayout->addRow("Additions: ",
                       createLabel(QString::number(m_matrixProduct->additions())));
    formLayout->addRow("Multiplications: ",
                       createLabel(QString::number(m_matrixProduct->multiplications())));
    formLayout->addRow("Recursive calls: ",
                       createLabel(QString::number(m_matrixProduct->recursiveCalls())));
    statisticsBox->setLayout(formLayout);

    QStringList algorithms = {"(Strassen)", "(Winograd-Strassen)", "(Standard)"};
    statisticsBox->setTitle("Statistics " + algorithms[m_algorithmIndex]);

    gridLayout->addWidget(statisticsBox, 4, 5, 1, 1);
}

QLabel *ResultsWindow::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text, this);
    label->setAlignment(Qt::AlignRight);
    return label;
}

void ResultsWindow::onExportButtonClicked()
{
    /* This saves resulting matrix as a text file
     * Each value is separated with spaces
     * Each row is separated with newlines
     */

    //Open QFileDialog to get filename from user
    QString filename = QFileDialog::getSaveFileName(this, "Export Matrix",
                                                    QDir::homePath(),
                                                    "Text files (*.txt)");

    QFile output(filename);
    output.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&output);

    SquareMatrix &C = m_matrixModel->matrix();
    int size = C.size();

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            stream << C[i][j] << " ";
        }
        stream << endl;
    }
}

} // namespace qmatrixproduct
