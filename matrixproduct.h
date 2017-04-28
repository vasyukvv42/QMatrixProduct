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
    int64_t multiplications();
    int64_t additions();
    int64_t functionCalls();
private:
    int64_t m_multiplications;
    int64_t m_additions;
    int64_t m_functionCalls;
};

#endif // MATRIXPRODUCT_H
