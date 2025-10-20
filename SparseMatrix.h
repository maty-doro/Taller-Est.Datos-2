#pragma once
#include "nodo.h"

class SparseMatrix {
private:
    nodo* head; // Nodo cabecera que simplifica las inserciones.
    int columnas;
    int filas;

public:
    SparseMatrix();
    void add(int value, int xPos, int yPos);//listo
    int get(int xPos, int yPos);
    void remove(int xPos, int yPos);
    void printStoredValues();
    int density();//falta
    SparseMatrix* multiply(SparseMatrix* second);
    int getColumnas();
    int getFilas();
    ~SparseMatrix();
};