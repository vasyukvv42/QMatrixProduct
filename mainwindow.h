#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QSplitter>
#include <QLabel>
#include <QHeaderView>
#include <QSpacerItem>
#include "matrixmodel.h"
#include "matrixwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
private:
    void setupUi();

    QWidget *centralWidget;
    MatrixWidget *matrixAWidget;
    MatrixWidget *matrixBWidget;
    MatrixModel *matrixAModel;
    MatrixModel *matrixBModel;
    QSpinBox *sizeBox;
    QComboBox *algorithmBox;
    QPushButton *multiplyButton;
};

#endif // MAINWINDOW_H
