#include "matrix.h"

Matrix::Matrix(int size) : size(size)
{
    for (int i = 0; i < size; i++)
        data.push_back(std::vector<double>(size, 0));
}

std::vector<double>& Matrix::operator [](int row)
{
    return data[row];
}

const std::vector<double>& Matrix::operator [](int row) const
{
    return data[row];
}


void Matrix::changeSize(int new_size)
{
    for (int i = 0; i < size; i++)
    {
        data[i].resize(new_size, 0);
        data[i].shrink_to_fit();
    }
    data.resize(new_size, std::vector<double>(new_size, 0));
    data.shrink_to_fit();
    size = new_size;
}

Matrix Matrix::operator +(const Matrix &obj)
{
    Matrix result(size);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result[i][j] = data[i][j] + obj.data[i][j];
    return result;
}

Matrix Matrix::operator -(const Matrix &obj)
{
    Matrix result(size);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result[i][j] = data[i][j] - obj.data[i][j];
    return result;
}

int Matrix::getSize() const
{
    return size;
}

void Matrix::randomize()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(-100, 100);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            data[i][j] = dist(mt);
}
