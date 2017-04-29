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
    Q_OBJECT
public:
    explicit ResultsWindow(std::shared_ptr<MatrixModel> model, const QString &time,
                           std::shared_ptr<MatrixProduct> mp, QWidget *parent = 0);
private:
    void setupUi();
    QLabel* createLabel(const QString &text);

    std::shared_ptr<MatrixModel> m_matrixModel;
    QString m_time;
    std::shared_ptr<MatrixProduct> m_matrixProduct;
    QTableView *m_tableView;
    QPushButton *m_exportButton;
};

#endif // RESULTSWINDOW_H
