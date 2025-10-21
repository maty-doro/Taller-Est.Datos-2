#include <iostream>
#include "SparseMatrix.h"
using namespace std;

int main() {
    std::cout << "Taller 2 Estructura de Datos" << std::endl;
    SparseMatrix m1;
    m1.add(12, 3, 5);
    m1.add(23, 12, 12);
    SparseMatrix m2;
    m2.add(7, 2, 1);
    m2.add(3, 12, 12);
    cout<<m1.getColumnas()<<endl;
    cout<<m2.getFilas()<<endl;
    SparseMatrix* m3 = m1.multiply(&m2);
    delete m3;

    return 0;
}