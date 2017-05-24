#ifndef MATRIXMODEL_H
#define MATRIXMODEL_H

//Qt headers
#include <QObject>
#include <QAbstractTableModel>
#include <QFile>
#include <QTextStream>

//Custom headers
#include "squarematrix.h"

namespace qmatrixproduct {

/**
 * @brief QAbstractTableModel subclass that encapsulates SquareMatrix class
 */
class MatrixModel : public QAbstractTableModel
{
public:
    /**
     * @brief MatrixModel constructor
     * @param data Matrix that gets encapsulated
     * @param parent Parent
     */
    explicit MatrixModel(const qmatrixproduct::SquareMatrix &data = SquareMatrix(),
                         QObject *parent = 0);

    //These methods need to be reimplemented to make a editable model
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    /**
     * @brief Get reference to the Matrix object
     * @return reference to the Matrix object
     */
    qmatrixproduct::SquareMatrix &matrix();

    /**
     * @brief Call Matrix.changeSize
     * @param newSize New matrix size
     */
    void changeSize(int newSize);

    /**
     * @brief Call Matrix.randomize
     */
    void randomize();

    /**
     * @brief Import matrix from text file
     * @param filename Text file path.
     * Each value must be separated with spaces.
     * Rows must be separated with newlines
     */
    void importFromFile(const QString &filename);

    void setReadOnly(bool readOnly);
private:
    qmatrixproduct::SquareMatrix m_data;
    bool m_readOnly;
};

} // namespace qmatrixproduct

#endif // MATRIXMODEL_H
