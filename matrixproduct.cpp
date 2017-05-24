#include "matrixproduct.h"

namespace qmatrixproduct {

MatrixProduct::MatrixProduct() :
    m_multiplications(0),
    m_additions(0),
    m_recursiveCalls(0)
{

}

SquareMatrix MatrixProduct::standardMultiply(const SquareMatrix &A, const SquareMatrix &B)
{
    m_recursiveCalls++;

    int size = A.size();
    double sum;
    SquareMatrix C(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            sum = 0;
            for (int k = 0; k < size; k++)
                sum += A[i][k]*B[k][j];
            C[i][j] = sum;
        }
    }

    //Standard algorithm does n^3 multiplications and n^3 additions
    m_multiplications += (uint64_t) size*size*size;
    m_additions += (uint64_t) size*size*size;

    return C;
}

SquareMatrix MatrixProduct::strassenMultiply(const SquareMatrix &A, const SquareMatrix &B)
{
    m_recursiveCalls++;

    int size = A.size();

    if (!isPowerOfTwo(size)) {
        int powerOfTwo = closestPowerOfTwo(size);
        SquareMatrix newA = A;
        SquareMatrix newB = B;
        newA.changeSize(powerOfTwo);
        newB.changeSize(powerOfTwo);
        SquareMatrix C = strassenMultiply(newA, newB);
        C.changeSize(size);
        return C;
    }
    else if (size <= 32)
        return standardMultiply(A, B);
    else {
        int newSize = size/2;

        SquareMatrix A11(newSize), A12(newSize), A21(newSize), A22(newSize);
        SquareMatrix B11(newSize), B12(newSize), B21(newSize), B22(newSize);
        SquareMatrix C11(newSize), C12(newSize), C21(newSize), C22(newSize);

        SquareMatrix M1(newSize), M2(newSize), M3(newSize), M4(newSize),
                     M5(newSize), M6(newSize), M7(newSize);

        SquareMatrix C(size);

        strassenPartition(A, A11, A12, A21, A22);
        strassenPartition(B, B11, B12, B21, B22);

        M1 = strassenMultiply(A11 + A22, B11 + B22);
        M2 = strassenMultiply(A21 + A22, B11);
        M3 = strassenMultiply(A11, B12 - B22);
        M4 = strassenMultiply(A22, B21 - B11);
        M5 = strassenMultiply(A11 + A12, B22);
        M6 = strassenMultiply(A21 - A11, B11 + B12);
        M7 = strassenMultiply(A12 - A22, B21 + B22);

        C11 = M1 + M4 - M5 + M7;
        C12 = M3 + M5;
        C21 = M2 + M4;
        C22 = M1 - M2 + M3 + M6;

        strassenCompose(C, C11, C12, C21, C22);

        m_additions += (uint64_t) 18*newSize*newSize;
        return C;
    }
}

SquareMatrix MatrixProduct::winogradMultiply(const SquareMatrix &A, const SquareMatrix &B)
{
    m_recursiveCalls++;

    int size = A.size();

    if (!isPowerOfTwo(size)) {
        int powerOfTwo = closestPowerOfTwo(size);
        SquareMatrix newA = A;
        SquareMatrix newB = B;
        newA.changeSize(powerOfTwo);
        newB.changeSize(powerOfTwo);
        SquareMatrix C = winogradMultiply(newA, newB);
        C.changeSize(size);
        return C;
    }
    else if (size <= 32)
        return standardMultiply(A, B);
    else {
        int newSize = size/2;

        SquareMatrix A11(newSize), A12(newSize), A21(newSize), A22(newSize);
        SquareMatrix B11(newSize), B12(newSize), B21(newSize), B22(newSize);
        SquareMatrix C11(newSize), C12(newSize), C21(newSize), C22(newSize);

        SquareMatrix S1(newSize), S2(newSize), S3(newSize), S4(newSize),
                     S5(newSize), S6(newSize), S7(newSize), S8(newSize);

        SquareMatrix P1(newSize), P2(newSize), P3(newSize), P4(newSize),
                     P5(newSize), P6(newSize), P7(newSize);

        SquareMatrix T1(newSize), T2(newSize);

        SquareMatrix C(size);

        strassenPartition(A, A11, A12, A21, A22);
        strassenPartition(B, B11, B12, B21, B22);

        S1 = A21 + A22;
        S2 = S1 - A11;
        S3 = A11 - A21;
        S4 = A12 - S2;
        S5 = B12 - B11;
        S6 = B22 - S5;
        S7 = B22 - B12;
        S8 = S6 - B21;

        P1 = winogradMultiply(S2, S6);
        P2 = winogradMultiply(A11, B11);
        P3 = winogradMultiply(A12, B21);
        P4 = winogradMultiply(S3, S7);
        P5 = winogradMultiply(S1, S5);
        P6 = winogradMultiply(S4, B22);
        P7 = winogradMultiply(A22, S8);

        T1 = P1 + P2;
        T2 = T1 + P4;

        C11 = P2 + P3;
        C12 = T1 + P5 + P6;
        C21 = T2 - P7;
        C22 = T2 + P5;

        strassenCompose(C, C11, C12, C21, C22);

        m_additions += (uint64_t) 15*newSize*newSize;
        return C;
    }
}

bool MatrixProduct::isPowerOfTwo(int n)
{
    return n && !(n & (n - 1));
}

int MatrixProduct::closestPowerOfTwo(int n)
{
    int p;
    for (p = 1; p < n; p <<= 1);
    return p;
}

void MatrixProduct::strassenPartition(const SquareMatrix &A,
                                      SquareMatrix &A11, SquareMatrix &A12,
                                      SquareMatrix &A21, SquareMatrix &A22)
{
    int newSize = A.size()/2;
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
        }
    }
}

void MatrixProduct::strassenCompose(SquareMatrix &C,
                                    const SquareMatrix &C11, const SquareMatrix &C12,
                                    const SquareMatrix &C21, const SquareMatrix &C22)
{
    int newSize = C.size()/2;
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j]                     = C11[i][j];
            C[i][j + newSize]           = C12[i][j];
            C[i + newSize][j]           = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
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

uint64_t MatrixProduct::recursiveCalls() const
{
    return m_recursiveCalls;
}

} // namespace qmatrixproduct
