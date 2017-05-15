#include "matrixproduct.h"

MatrixProduct::MatrixProduct() :
    m_multiplications(0),
    m_additions(0),
    m_functionCalls(0)
{

}

Matrix MatrixProduct::standardMultiply(const Matrix &A, const Matrix &B)
{
    m_functionCalls++;      //This function only gets called once though

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

    //Standard algorithm does n^3 multiplications and n^3 additions
    m_multiplications += size*size*size;
    m_additions += size*size*size;
    return C;
}

Matrix MatrixProduct::strassenMultiply(const Matrix &A, const Matrix &B)
{
    m_functionCalls++;

    int size = A.size();

    if (size <= 64) {
        Matrix C(size);
        C = standardMultiply(A, B);
        return C;
    }
    else {
        int newSize = size/2;
        Matrix A11(newSize), A12(newSize), A21(newSize), A22(newSize);
        Matrix B11(newSize), B12(newSize), B21(newSize), B22(newSize);
        Matrix C11(newSize), C12(newSize), C21(newSize), C22(newSize);
        Matrix P1(newSize), P2(newSize), P3(newSize), P4(newSize),
               P5(newSize), P6(newSize), P7(newSize);
        Matrix C(size);

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + newSize];
                A21[i][j] = A[i + newSize][j];
                A22[i][j] = A[i + newSize][j + newSize];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + newSize];
                B21[i][j] = B[i + newSize][j];
                B22[i][j] = B[i + newSize][j + newSize];
            }
        }

        P1 = strassenMultiply(A11 + A22, B11 + B22);
        P2 = strassenMultiply(A21 + A22, B11);
        P3 = strassenMultiply(A11, B12 - B22);
        P4 = strassenMultiply(A22, B21 - B11);
        P5 = strassenMultiply(A11 + A12, B22);
        P6 = strassenMultiply(A21 - A11, B11 + B12);
        P7 = strassenMultiply(A12 - A22, B21 + B22);

        C11 = P1 + P4 - P5 + P7;
        C12 = P3 + P5;
        C21 = P2 + P4;
        C22 = P1 - P2 + P3 + P6;

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                C[i][j]                     = C11[i][j];
                C[i][j + newSize]           = C12[i][j];
                C[i + newSize][j]           = C21[i][j];
                C[i + newSize][j + newSize] = C22[i][j];
            }
        }

        m_additions += 18*newSize*newSize;
        return C;
    }
}

uint64_t MatrixProduct::multiplications() const
{
    return m_multiplications;
}

uint64_t MatrixProduct::additions() const
{
    return m_additions;
}

uint64_t MatrixProduct::functionCalls() const
{
    return m_functionCalls;
}
