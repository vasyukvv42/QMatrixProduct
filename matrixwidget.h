#ifndef MATRIXWIDGET_H
#define MATRIXWIDGET_H

//Qt headers
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QSpacerItem>
#include <QHeaderView>
#include <QFileDialog>
#include <QDir>

//STL headers
#include <memory>

//Custom headers
#include "matrixmodel.h"

namespace qmatrixproduct {

/**
 * @brief Widget for matrices w/ QTableView and two buttons
 */
class MatrixWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief MatrixWidget constructor
     * @param parent Parent
     */
    explicit MatrixWidget(QWidget *parent = 0);

    /**
     * @brief Get shared pointer to the MatrixModel object
     * @return
     */
    std::shared_ptr<MatrixModel> model();
public slots:
    /**
     * @brief Slot connected with "Size: " QSpinBox in the MainWindow
     * @param newSize New matrix size
     */
    void onSizeBoxChanged(int newSize);

    /**
     * @brief Slot connected with "Randomize" button
     */
    void onRandomizeButtonClicked();

    /**
     * @brief Slot connected with "Import..." button.
     * Opens a QFileDialog
     */
    void onImportButtonClicked();
private:
    void setupUi();

    std::shared_ptr<MatrixModel> m_matrixModel;
    QTableView *m_tableView;
    QPushButton *m_randomizeButton;
    QPushButton *m_importButton;
};

} // namespace qmatrixproduct

#endif // MATRIXWIDGET_H
