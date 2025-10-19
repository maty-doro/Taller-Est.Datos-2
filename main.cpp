#include <iostream>
#include "SparseMatrix.h"

int main() {
    std::cout << "Probando la implementacion de la Matriz" << std::endl;

    SparseMatrix miMatriz;

    miMatriz.printStoredValues();

    miMatriz.add(10, 1, 2);
    miMatriz.add(50, 3, 4);
    miMatriz.add(25, 3, 2);
    miMatriz.add(99, 8, 10);

    miMatriz.printStoredValues();
    
    std::cout << "\nActualizando el valor en (1, 2) a 150..." << std::endl;
    miMatriz.add(150, 1, 2);

    miMatriz.printStoredValues();

    return 0;
}