#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "matrixproduct.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Matrix A(2), B(2);
    A.randomize();
    B.randomize();
    MatrixProduct mp;
    Matrix C = mp.standardMultiply(A, B);
    qDebug() << mp.additions() << mp.multiplications() << mp.functionCalls();
    return a.exec();
}
