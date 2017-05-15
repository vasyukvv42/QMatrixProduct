#ifndef MATRIXPRODUCT_H
#define MATRIXPRODUCT_H

//Custom headers
#include "matrix.h"

/**
 * @brief Class for matrix product calculation w/ statistics
 */
class MatrixProduct
{
public:
    /**
     * @brief MatrixProduct constructor
     */
    MatrixProduct();

    /**
     * @brief Standard O(n^3) matrix multiplication algorithm
     * @param A Left-hand side matrix
     * @param B Right-hand side matrix
     * @return Matrix C = AB
     */
    Matrix standardMultiply(const Matrix &A, const Matrix &B);

    /**
     * @brief Strassen O(n^log7) matrix multiplication algorithm
     * @param A Left-hand side matrix
     * @param B Right-hand side matrix
     * @return Matrix C = AB
     */
    Matrix strassenMultiply(const Matrix &A, const Matrix &B);

    //TODO: Strassen and Winograd-Strassen

    /**
     * @brief Get closest power of 2 greater than n (i.e. 64 for n=63)
     * @param n Positive number
     * @return Closest power of 2
     */
    static int closestPowerOf2(int n);

    /**
     * @brief Get number of multiplications done since object creation
     * @return Number of multiplications
     */
    uint64_t multiplications() const;

    /**
     * @brief Get number of additions done since object creation
     * @return Number of additions
     */
    uint64_t additions() const;

    /**
     * @brief Get number of function calls
     * (only the multiplication functions are counted)
     * @return Number of function calls
     */
    uint64_t functionCalls() const;
private:
    uint64_t m_multiplications;
    uint64_t m_additions;
    uint64_t m_functionCalls;
};

#endif // MATRIXPRODUCT_H
