#ifndef MATRIX_H
#define MATRIX_H

//STL headers
#include <vector>
#include <random>

namespace qmatrixproduct {

/**
 * @brief 2-dimensional square matrix class with double values
 */
class SquareMatrix
{
public:
    /**
     * @brief Matrix constructor
     * @param m_size Matrix size
     */
    explicit SquareMatrix(int m_size = 64);

    /**
     * @brief Change the size of matrix
     * @param newSize new matrix size
     */
    void changeSize(int newSize);

    std::vector<double>& operator [](int row);
    const std::vector<double>& operator [](int row) const;
    SquareMatrix operator +(const SquareMatrix& other) const;
    SquareMatrix operator -(const SquareMatrix& other) const;
    SquareMatrix& operator =(const SquareMatrix& other);

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

} // namespace qmatrixproduct

#endif // MATRIX_H
