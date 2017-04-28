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

#include "matrixmodel.h"
#include "matrixproduct.h"

class ResultsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ResultsWindow(MatrixModel *model, const QString &time, MatrixProduct *mp, QWidget *parent = 0);
    ~ResultsWindow();
private:
    void setupUi();
    QLabel* createLabel(const QString &text);

    MatrixModel *m_matrixModel;
    QString m_time;
    MatrixProduct *m_matrixProduct;
    QTableView *m_tableView;
    QPushButton *m_exportButton;
};

#endif // RESULTSWINDOW_H
