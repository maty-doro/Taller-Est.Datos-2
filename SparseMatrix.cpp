#include "SparseMatrix.h"
#include <iostream>
#include <ostream>

SparseMatrix::SparseMatrix() {
    // El constructor crea nuestro nodo de inicio
    head = new nodo(-1, -1, -1);
    columnas = 0;
    filas = 0;
}

SparseMatrix::~SparseMatrix() {

}

void SparseMatrix::add(int value, int yPos, int xPos) {
    // Primero, buscamos la posición correcta en la fila
    nodo* vertical = head;
    while (vertical->nxtFil != nullptr && vertical->nxtFil->fil < yPos) {
        vertical = vertical->nxtFil;
    }

    // Si la fila no existe, creamos su cabecera.
    if (vertical->nxtFil == nullptr || vertical->nxtFil->fil > yPos) {
        nodo* nuevaCabeceraFila = new nodo(-1, yPos, -1);
        nuevaCabeceraFila->nxtFil = vertical->nxtFil;
        vertical->nxtFil = nuevaCabeceraFila;
    }
    nodo* filaActual = vertical->nxtFil;

    // Avanzamos por la fila para encontrar la columna
    nodo* horizontal = filaActual;
    while (horizontal->nxtCol != nullptr && horizontal->nxtCol->col < xPos) {
        horizontal = horizontal->nxtCol;
    }
    
    // Si ya existe un nodo aqui, solo cambiamos el valor y terminamos
    if (horizontal->nxtCol != nullptr && horizontal->nxtCol->col == xPos) {
        horizontal->nxtCol->value = value;
        if (xPos > columnas) {
        columnas = xPos;
        }
        if (yPos > filas) {
        filas = yPos;
        }
        return;
    }

    // Si no existe, lo creamos y lo enlazamos en la fila
    nodo* nuevoNodo = new nodo(value, yPos, xPos);
    nuevoNodo->nxtCol = horizontal->nxtCol;
    horizontal->nxtCol = nuevoNodo;

    // Ahora hacemos lo mismo para enlazarlo en la columna
    vertical = head;
    while (vertical->nxtCol != nullptr && vertical->nxtCol->col < xPos) {
        vertical = vertical->nxtCol;
    }

    if (vertical->nxtCol == nullptr || vertical->nxtCol->col > xPos) {
        nodo* nuevaCabeceraColumna = new nodo(-1, -1, xPos);
        nuevaCabeceraColumna->nxtCol = vertical->nxtCol;
        vertical->nxtCol = nuevaCabeceraColumna;
    }
    nodo* columnaActual = vertical->nxtCol;
    
    while (columnaActual->nxtFil != nullptr && columnaActual->nxtFil->fil < yPos) {
        columnaActual = columnaActual->nxtFil;
    }
    nuevoNodo->nxtFil = columnaActual->nxtFil;
    columnaActual->nxtFil = nuevoNodo;
    
    if (xPos > columnas) {
        columnas = xPos;
    }
    if (yPos > filas) {
        filas = yPos;
    }
}


int SparseMatrix::get(int xPos, int yPos) {
    nodo* filaActual = head->nxtFil;
    if (filaActual == nullptr) {
        std::cout << "La matriz esta vacia." << std::endl;
        return 0;
    }
    while (filaActual != nullptr) {
        nodo* nodoActual = filaActual->nxtCol; // Empezamos en el primer nodo con valor de la fila.

        // Recorremos cada nodo en la fila actual
        while (nodoActual != nullptr) {
            if(nodoActual->fil==xPos && nodoActual->col==yPos){
                return nodoActual->value;
            }
            nodoActual = nodoActual->nxtCol;
        }
        filaActual = filaActual->nxtFil;
    }
    return 0;
}

void SparseMatrix::remove(int xPos, int yPos) {
    nodo* filaActual = head->nxtFil;
    if (filaActual == nullptr) {
        std::cout << "La matriz esta vacia." << std::endl;
        return;
    }

    while (filaActual != nullptr) {
        nodo* nodoActual = filaActual->nxtCol;

        while (nodoActual != nullptr) {
            if(nodoActual->fil==xPos && nodoActual->col==yPos){
                nodoActual->value = 0;
                std::cout<<"Nodo Reseteado a 0"<<std::endl;
            }
            nodoActual = nodoActual->nxtCol;
        }
        filaActual = filaActual->nxtFil;
    }

}

void SparseMatrix::printStoredValues() {
    std::cout << "--- Contenido de la Matriz ---" << std::endl;
    nodo* filaActual = head->nxtFil;

    if (filaActual == nullptr) {
        std::cout << "La matriz esta vacia." << std::endl;
        return;
    }

    // Recorremos cada fila
    while (filaActual != nullptr) {
        nodo* nodoActual = filaActual->nxtCol; // Empezamos en el primer nodo con valor de la fila.

        // Recorremos cada nodo en la fila actual
        while (nodoActual != nullptr) {
            std::cout << "(" << nodoActual->fil << ", " << nodoActual->col << ") --> " << nodoActual->value << std::endl;
            nodoActual = nodoActual->nxtCol;
        }
        filaActual = filaActual->nxtFil;
    }
    std::cout << "-----------------------------" << std::endl;
}


int SparseMatrix::density() {
    return 0;
}

SparseMatrix* SparseMatrix::multiply(SparseMatrix* second) {
if (getColumnas() != second->getFilas()) {
std::cout<<"No hay posibilidad de multiplicar las matrices"<<std::endl;
return nullptr;
}
SparseMatrix* MxNueva = new SparseMatrix();
nodo* filaA = head->nxtFil;

    if(filaA==nullptr) {
    std::cout << "Matriz está vacia" << std::endl;
    }
    //Recorre fila m1
while (filaA != nullptr) {
   nodo* colM2 = second->head->nxtCol;
   //Columnas m2
   while(colM2 != nullptr){
       int suma = 0;
       nodo* nodoActual = filaA->nxtCol;
       //Recorre elementos de la fila m1
       while (nodoActual!=nullptr){
           nodo* colActual = colM2->nxtFil;
           //Encuentra la fila de nodoActual
           while(colActual!= nullptr && colActual->fil<nodoActual->col){
               colActual = colActual->nxtFil;
           }
           if(colActual!= nullptr && colActual->fil == nodoActual->col){
               suma += colActual->value*nodoActual->value;
           }
           if (suma > 0){
            MxNueva->add(suma,filaA->fil,colM2->col);
           }
           nodoActual = nodoActual->nxtCol;
       }
       colM2 = colM2->nxtCol;
   }
   filaA = filaA->nxtFil;
}
return MxNueva;

}
int SparseMatrix::getColumnas(){
    return columnas;
}
int SparseMatrix::getFilas(){
    return filas;
}
