#pragma once
#include "nodo.h"

class SparseMatrix {
private:
    nodo* start;

public:
    SparseMatrix();
    void add(int value, int xPos, int yPos);
    int get(int xPos, int yPos);
    void remove(int xPos, int yPos);
    void printStoredValues();
    int density();
    SparseMatrix* multiply(SparseMatrix* second);
    ~SparseMatrix();
};