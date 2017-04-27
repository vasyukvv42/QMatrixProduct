#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix
{
public:
    explicit Matrix(int size = 64);
    void changeSize(int new_size);
    std::vector<double>& operator [](int row);
    const std::vector<double>& operator [](int row) const;
    Matrix operator +(const Matrix& that);
    Matrix operator -(const Matrix& that);
    int getSize() const;
private:
    std::vector<std::vector<double>> data;
    int size;
};

#endif // MATRIX_H
