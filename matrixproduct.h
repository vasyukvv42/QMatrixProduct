#ifndef MATRIXPRODUCT_H
#define MATRIXPRODUCT_H

//Custom headers
#include "squarematrix.h"

namespace qmatrixproduct {

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
     * @param A Square matrix
     * @param B Square matrix
     * @return Matrix C = AB
     */
    SquareMatrix standardMultiply(const SquareMatrix &A, const SquareMatrix &B);

    /**
     * @brief Strassen O(n^log7) matrix multiplication algorithm
     * @param A Square matrix
     * @param B Square matrix
     * @return Matrix C = AB
     */
    SquareMatrix strassenMultiply(const SquareMatrix &A, const SquareMatrix &B);

    /**
     * @brief Winograd-Strassen matrix multiplication algorithm
     * @param A Square matrix
     * @param B Square matrix
     * @return Matrix C = AB
     */
    SquareMatrix winogradMultiply(const SquareMatrix &A, const SquareMatrix &B);

    /**
     * @brief Check whether n is a power of 2
     * @param n
     * @return true if n is a power of 2
     */
    static bool isPowerOfTwo(int n);

    /**
     * @brief Get closest power of 2 greater than n (i.e. 64 for n=63)
     * @param n Positive number
     * @return Closest power of 2
     */
    static int closestPowerOfTwo(int n);

    /**
     * @brief Partition matrix A(n) into 4 (n/2) square matrices for Strassen algorithm
     * @param A Matrix to partition
     * @param A11 Top left
     * @param A12 Top right
     * @param A21 Bottom left
     * @param A22 Bottom right
     */
    static void strassenPartition(const SquareMatrix &A,
                                  SquareMatrix &A11, SquareMatrix &A12,
                                  SquareMatrix &A21, SquareMatrix &A22);

    /**
     * @brief Compose matrix C(n) from 4 (n/2) matrices
     * @param C Resulting matrix
     * @param C11 Top left
     * @param C12 Top right
     * @param C21 Bottom left
     * @param C22 Bottom right
     */
    static void strassenCompose(SquareMatrix &C,
                                const SquareMatrix &C11, const SquareMatrix &C12,
                                const SquareMatrix &C21, const SquareMatrix &C22);

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
     * @brief Get number of recursive function calls
     * (only the multiplication functions are counted)
     * @return Number of recursive calls
     */
    uint64_t recursiveCalls() const;
private:
    uint64_t m_multiplications;
    uint64_t m_additions;
    uint64_t m_recursiveCalls;
};

} // namespace qmatrixproduct

#endif // MATRIXPRODUCT_H
