#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "matrixproduct.h"
#include "resultswindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Matrix A(2), B(2);
    A.randomize();
    B.randomize();
    MatrixProduct *mp = new MatrixProduct;
    Matrix C = mp->standardMultiply(A, B);
    MatrixModel *model = new MatrixModel(C, true);
    ResultsWindow r(model, "0s", mp);
    r.show();
    return a.exec();
}
