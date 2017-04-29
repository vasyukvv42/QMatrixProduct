#ifndef MATRIX_H
#define MATRIX_H

//STL headers
#include <vector>
#include <random>

/**
 * @brief 2-dimensional square matrix class with double values
 */
class Matrix
{
public:
    /**
     * @brief Matrix constructor
     * @param m_size Matrix size
     */
    explicit Matrix(int m_size = 64);

    /**
     * @brief Matrix constructor (copies other Matrix data and size)
     * @param other Other matrix
     */
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
