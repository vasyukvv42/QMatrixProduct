#include "matrixmodel.h"

MatrixModel::MatrixModel(const Matrix &data, QObject *parent)
    : QAbstractTableModel(parent), modelData(data)
{

}

int MatrixModel::rowCount(const QModelIndex &) const
{
   return modelData.getSize();
}

int MatrixModel::columnCount(const QModelIndex &) const
{
    return modelData.getSize();
}

QVariant MatrixModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    if (role == Qt::DisplayRole || role == Qt::EditRole)
       return QString::number(modelData[row][col]);
    return QVariant();
}

bool MatrixModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    int col = index.column();
    if (role == Qt::EditRole)
        modelData[row][col] = value.toDouble();
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
    return modelData;
}

void MatrixModel::changeSize(int new_size)
{
    beginResetModel();
    modelData.changeSize(new_size);
    endResetModel();
}

void MatrixModel::randomize()
{
    beginResetModel();
    modelData.randomize();
    endResetModel();
}

void MatrixModel::importFromFile(const QString &filename)
{
    beginResetModel();
    QFile input(filename);
    input.open(QIODevice::ReadOnly | QIODevice::Text);
    for (int i = 0; i < modelData.getSize() && !input.atEnd(); i++)
    {
        QString line = input.readLine();
        QTextStream ls(&line);
        for (int j = 0; j < modelData.getSize() && !ls.atEnd(); j++)
            ls >> modelData[i][j];
    }
    endResetModel();
}
