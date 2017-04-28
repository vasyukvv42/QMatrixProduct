#include "matrixproduct.h"

MatrixProduct::MatrixProduct() :
    m_multiplications(0),
    m_additions(0),
    m_functionCalls(0)
{

}

Matrix MatrixProduct::standardMultiply(const Matrix &A, const Matrix &B)
{
    m_functionCalls++;

    int size = A.size();
    int sum;
    Matrix C(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            sum = 0;
            for (int k = 0; k < size; k++)
                sum += A[i][k]*B[k][j];
            C[i][j] = sum;
        }
    }

    m_multiplications += size*size*size;
    m_additions += m_multiplications;
    return C;
}

int64_t MatrixProduct::multiplications()
{
    return m_multiplications;
}

int64_t MatrixProduct::additions()
{
    return m_additions;
}

int64_t MatrixProduct::functionCalls()
{
    return m_functionCalls;
}
