#pragma once
#include "nodo.h"

class SparseMatrix {
private:
    nodo* head; 
    int columnas; 
    int filas;

public:
    SparseMatrix();
    void add(int value, int yPos, int xPos);
    int get(int xPos, int yPos);
    void remove(int xPos, int yPos);
    void printStoredValues();
    int density();
    SparseMatrix* multiply(SparseMatrix* second);
    ~SparseMatrix();

    int getColumnas();
    int getFilas();
};