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
#include <QDebug>
#include <QElapsedTimer>
#include <memory>
#include "matrixmodel.h"
#include "matrixwidget.h"
#include "matrixproduct.h"
#include "resultswindow.h"

class MainWindow : public QMainWindow
{
    /**
     * @brief Main window of the program
     */
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
public slots:
    /**
     * @brief Slot connected with "Multiply" button.
     * Opens a ResultsWindow window
     */
    void multiply();
private:
    void setupUi();

    QWidget *m_centralWidget;
    MatrixWidget *m_matrixAWidget;
    MatrixWidget *m_matrixBWidget;
    std::shared_ptr<MatrixModel> m_matrixAModel;
    std::shared_ptr<MatrixModel> m_matrixBModel;
    QSpinBox *m_sizeBox;
    QComboBox *m_algorithmBox;
    QPushButton *m_multiplyButton;
};

#endif // MAINWINDOW_H
