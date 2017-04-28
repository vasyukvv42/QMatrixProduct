#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <random>

class Matrix
{
public:
    explicit Matrix(int m_size = 64);
    Matrix(const Matrix &other);
    void changeSize(int new_size);
    std::vector<double>& operator [](int row);
    const std::vector<double>& operator [](int row) const;
    Matrix operator +(const Matrix& other) const;
    Matrix operator -(const Matrix& other) const;
    Matrix& operator =(const Matrix& other);
    int size() const;
    void randomize();
private:
    std::vector<std::vector<double>> m_data;
    int m_size;
};

#endif // MATRIX_H
