#ifndef MATRIXMODEL_H
#define MATRIXMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QFile>
#include <QTextStream>
#include "matrix.h"

class MatrixModel : public QAbstractTableModel
{
public:
    explicit MatrixModel(const Matrix &data = Matrix(), bool readOnly = false, QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    Matrix &matrix();
    void changeSize(int new_size);
    void randomize();
    void importFromFile(const QString &filename);
private:
    Matrix m_data;
    bool m_readOnly;
};

#endif // MATRIXMODEL_H
