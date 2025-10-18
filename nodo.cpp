#include "nodo.h"

nodo::nodo(int valor, int fila, int columna){
    value = valor;
    fil = fila;
    col = columna;
    nxtFil = nullptr;
    nxtCol = nullptr;
}
nodo::~nodo(){
}
