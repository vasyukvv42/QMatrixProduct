#include "squarematrix.h"

namespace qmatrixproduct {

SquareMatrix::SquareMatrix(int size) : m_size(size)
{
    for (int i = 0; i < size; i++)
        m_data.push_back(std::vector<double>(size, 0));
}

std::vector<double>& SquareMatrix::operator [](int row)
{
    return m_data[row];
}

const std::vector<double>& SquareMatrix::operator [](int row) const
{
    return m_data[row];
}

void SquareMatrix::changeSize(int new_size)
{
    for (int i = 0; i < m_size; i++)
        m_data[i].resize(new_size, 0);
    m_data.resize(new_size, std::vector<double>(new_size, 0));
    m_size = new_size;
}

SquareMatrix SquareMatrix::operator +(const SquareMatrix &other) const
{
    SquareMatrix result(m_size);
    for (int i = 0; i < m_size; i++)
        for (int j = 0; j < m_size; j++)
            result[i][j] = m_data[i][j] + other.m_data[i][j];
    return result;
}

SquareMatrix SquareMatrix::operator -(const SquareMatrix &other) const
{
    SquareMatrix result(m_size);
    for (int i = 0; i < m_size; i++)
        for (int j = 0; j < m_size; j++)
            result[i][j] = m_data[i][j] - other.m_data[i][j];
    return result;
}

SquareMatrix &SquareMatrix::operator =(const SquareMatrix &other)
{
    m_size = other.m_size;
    m_data.clear();
    m_data = other.m_data;
    return *this;
}

int SquareMatrix::size() const
{
    return m_size;
}

void SquareMatrix::randomize()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(-10, 10);
    for (int i = 0; i < m_size; i++)
        for (int j = 0; j < m_size; j++)
            m_data[i][j] = dist(mt);
}

} // namespace qmatrixproduct
