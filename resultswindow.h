#ifndef RESULTSWINDOW_H
#define RESULTSWINDOW_H

//Qt headers
#include <QWidget>
#include <QLabel>
#include <QTableView>
#include <QGridLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QGroupBox>
#include <QPushButton>
#include <QFileDialog>
#include <QDir>

//STL headers
#include <memory>

//Custom headers
#include "matrixmodel.h"
#include "matrixproduct.h"

/**
 * @brief Window that opens after pressing "Multiply..." button
 */
class ResultsWindow : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief ResultsWindow constructor
     * @param model MatrixModel object pointer
     * @param time Time spent on multiplication
     * @param mp MatrixProduct object pointer w/ all statistics
     * @param parent Parent
     */
    explicit ResultsWindow(MatrixModel *model, const QString &time,
                           MatrixProduct *mp, QWidget *parent = 0);
public slots:
    /**
     * @brief Slot connected with "Export..." button
     */
    void exportToFile();
private:
    void setupUi();

    /**
     * @brief Create a right-aligned label
     * @param text Label text
     * @return Pointer to the created label
     */
    QLabel* createLabel(const QString &text);

    std::unique_ptr<MatrixModel> m_matrixModel;
    QString m_time;
    std::unique_ptr<MatrixProduct> m_matrixProduct;
    QTableView *m_tableView;
    QPushButton *m_exportButton;
};

#endif // RESULTSWINDOW_H
