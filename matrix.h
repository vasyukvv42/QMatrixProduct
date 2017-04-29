#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <random>

class Matrix
{
    /**
     * @brief 2-dimensional square matrix class with double values
     */
public:
    explicit Matrix(int m_size = 64);
    Matrix(const Matrix &other);

    /**
     * @brief Change the size of matrix
     * @param new_size new matrix size
     */
    void changeSize(int new_size);

    std::vector<double>& operator [](int row);
    const std::vector<double>& operator [](int row) const;
    Matrix operator +(const Matrix& other) const;
    Matrix operator -(const Matrix& other) const;
    Matrix& operator =(const Matrix& other);

    /**
     * @brief Get matrix size
     * @return matrix size
     */
    int size() const;

    /**
     * @brief Fill matrix with random int values from -10 to 10
     */
    void randomize();
private:
    /**
     * @brief Internal data stored as vector of vectors
     */
    std::vector<std::vector<double>> m_data;
    int m_size;
};

#endif // MATRIX_H
