#ifndef MATRIXWIDGET_H
#define MATRIXWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QSpacerItem>
#include <QHeaderView>
#include <QFileDialog>
#include <QDir>
#include "matrixmodel.h"

class MatrixWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MatrixWidget(QWidget *parent = 0);
    MatrixModel* model();
public slots:
    void changeSize(int new_size);
    void randomize();
    void import();
private:
    void setupUi();

    MatrixModel *m_matrixModel;
    QTableView *m_tableView;
    QPushButton *m_randomizeButton;
    QPushButton *m_importButton;
};

#endif // MATRIXWIDGET_H
