#ifndef MATRIXPRODUCT_H
#define MATRIXPRODUCT_H

#include <chrono>
#include "matrix.h"

class MatrixProduct
{
public:
    MatrixProduct();
    Matrix standardMultiply(const Matrix &A, const Matrix &B);
    //TODO: Strassen and Winograd-Strassen
    uint64_t multiplications();
    uint64_t additions();
    uint64_t functionCalls();
private:
    uint64_t m_multiplications;
    uint64_t m_additions;
    uint64_t m_functionCalls;
};

#endif // MATRIXPRODUCT_H
