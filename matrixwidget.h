#ifndef MATRIXWIDGET_H
#define MATRIXWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QSpacerItem>
#include <QHeaderView>
#include "matrixmodel.h"

class MatrixWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MatrixWidget(QWidget *parent = 0);
    MatrixModel* model();
private:
    void setupUi();

    MatrixModel *matrixModel;
    QTableView *tableView;
    QPushButton *randomizeButton;
    QPushButton *importButton;
public slots:
    void changeSize(int new_size);
    void randomize();
};

#endif // MATRIXWIDGET_H
