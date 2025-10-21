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
    int get(int yPos, int xPos);
    void remove(int yPos, int xPos);
    void printStoredValues();
    int density();
    SparseMatrix* multiply(SparseMatrix* second);
    int getColumnas();
    int getFilas();
    ~SparseMatrix();

};