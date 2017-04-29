#ifndef RESULTSWINDOW_H
#define RESULTSWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QTableView>
#include <QGridLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QGroupBox>
#include <QPushButton>
#include <memory>

#include "matrixmodel.h"
#include "matrixproduct.h"

class ResultsWindow : public QWidget
{
    /**
     * @brief Window that opens after pressing "Multiply..." button
     */
    Q_OBJECT
public:
    explicit ResultsWindow(MatrixModel *model, const QString &time,
                           MatrixProduct *mp, QWidget *parent = 0);
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
