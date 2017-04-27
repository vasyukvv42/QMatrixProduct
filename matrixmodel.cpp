#include "matrixmodel.h"

MatrixModel::MatrixModel(const Matrix &data, QObject *parent)
    : QAbstractTableModel(parent), m_data(data)
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

void MatrixModel::randomize()
{
    beginResetModel();
    m_data.randomize();
    endResetModel();
}

void MatrixModel::importFromFile(const QString &filename)
{
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
