#include "matrixmodel.h"

MatrixModel::MatrixModel(const Matrix &data, QObject *parent)
    : QAbstractTableModel(parent), m_data(data)
{

}

int MatrixModel::rowCount(const QModelIndex &) const
{
   return m_data.getSize();
}

int MatrixModel::columnCount(const QModelIndex &) const
{
    return m_data.getSize();
}

QVariant MatrixModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    if (role == Qt::DisplayRole || role == Qt::EditRole)
       return QString::number(m_data[row][col]);
    return QVariant();
}

bool MatrixModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    int col = index.column();
    if (role == Qt::EditRole)
        m_data[row][col] = value.toDouble();
    return true;
}

Qt::ItemFlags MatrixModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

Matrix& MatrixModel::matrix()
{
    return m_data;
}

void MatrixModel::changeSize(int new_size)
{
    beginResetModel();
    m_data.changeSize(new_size);
    endResetModel();
}


