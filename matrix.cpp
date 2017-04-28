#include "matrix.h"

Matrix::Matrix(int size) : m_size(size)
{
    for (int i = 0; i < size; i++)
        m_data.push_back(std::vector<double>(size, 0));
}

Matrix::Matrix(const Matrix &other)
{
    m_size = other.m_size;
    m_data = other.m_data;
}

std::vector<double>& Matrix::operator [](int row)
{
    return m_data[row];
}

const std::vector<double>& Matrix::operator [](int row) const
{
    return m_data[row];
}


void Matrix::changeSize(int new_size)
{
    for (int i = 0; i < m_size; i++) {
        m_data[i].resize(new_size, 0);
        m_data[i].shrink_to_fit();
    }
    m_data.resize(new_size, std::vector<double>(new_size, 0));
    m_data.shrink_to_fit();
    m_size = new_size;
}

Matrix Matrix::operator +(const Matrix &other) const
{
    Matrix result(m_size);
    for (int i = 0; i < m_size; i++)
        for (int j = 0; j < m_size; j++)
            result[i][j] = m_data[i][j] + other.m_data[i][j];
    return result;
}

Matrix Matrix::operator -(const Matrix &other) const
{
    Matrix result(m_size);
    for (int i = 0; i < m_size; i++)
        for (int j = 0; j < m_size; j++)
            result[i][j] = m_data[i][j] - other.m_data[i][j];
    return result;
}

Matrix &Matrix::operator =(const Matrix &other)
{
    m_size = other.m_size;
    m_data.clear();
    m_data = other.m_data;
    return *this;
}

int Matrix::size() const
{
    return m_size;
}

void Matrix::randomize()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(-100, 100);
    for (int i = 0; i < m_size; i++)
        for (int j = 0; j < m_size; j++)
            m_data[i][j] = dist(mt);
}
