#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Qt headers
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
#include <QElapsedTimer>

//STL headers
#include <memory>

//Custom headers
#include "matrixmodel.h"
#include "matrixwidget.h"
#include "matrixproduct.h"
#include "resultswindow.h"

namespace qmatrixproduct {

/**
 * @brief Main window of the program
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * @brief MainWindow constructor
     * @param parent Parent
     */
    explicit MainWindow(QWidget *parent = 0);
public slots:
    /**
     * @brief Slot connected with "Multiply" button.
     * Opens a ResultsWindow window
     */
    void onMultiplyButtonClicked();
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

} // namespace qmatrixproduct

#endif // MAINWINDOW_H
