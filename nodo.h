#include <iostream>

struct nodo{
    int value;
    int fil;
    int col;

    nodo* nxtFil;
    nodo* nxtCol;
    nodo(int valor, int fila, int columna);
    ~nodo ();
};
