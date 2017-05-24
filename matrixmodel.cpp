#include "matrixmodel.h"

namespace qmatrixproduct {

MatrixModel::MatrixModel(const SquareMatrix &data, QObject *parent)
    : QAbstractTableModel(parent),
      m_data(data),
      m_readOnly(false)
{

}

int MatrixModel::rowCount(const QModelIndex &) const
{
   return m_data.size();
}

int MatrixModel::columnCount(const QModelIndex &) const
{
    return m_data.size();
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
    if (role == Qt::EditRole) {
        bool ok = true;
        double newValue = value.toDouble(&ok);
        if (ok)
            m_data[row][col] = newValue;
        else
            return false;
    }
    return true;
}

Qt::ItemFlags MatrixModel::flags(const QModelIndex &index) const
{
    if (!index.isValid() || m_readOnly)
        return QAbstractItemModel::flags(index);
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

SquareMatrix& MatrixModel::matrix()
{
    return m_data;
}

void MatrixModel::changeSize(int newSize)
{
    beginResetModel();
    m_data.changeSize(newSize);
    endResetModel();
}

void MatrixModel::randomize()
{
    beginResetModel();
    m_data.randomize();
    endResetModel();
}

void MatrixModel::importFromFile(const QString &filename)
{
    /* This doesn't resize the matrix, only tries to fit the
     * data from the file into the matrix starting from top
     * left corner (i = 0, j = 0)
     */
    beginResetModel();
    QFile input(filename);
    input.open(QIODevice::ReadOnly | QIODevice::Text);
    for (int i = 0; i < m_data.size() && !input.atEnd(); i++) {
        QString line = input.readLine();
        QTextStream ls(&line);
        for (int j = 0; j < m_data.size() && !ls.atEnd(); j++)
            ls >> m_data[i][j];
    }
    endResetModel();
}

void MatrixModel::setReadOnly(bool readOnly)
{
    m_readOnly = readOnly;
}

} // namespace qmatrixproduct
