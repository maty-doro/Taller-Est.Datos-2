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
    // Encontramos la fila correcta
    nodo* vertical = head;
    while (vertical->nxtFil != nullptr && vertical->nxtFil->fil < yPos) {
        vertical = vertical->nxtFil;
    }

    // Si no existe la fila, la creamos
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
    
    // Si el nodo ya existe, solo actualizamos el valor
    if (horizontal->nxtCol != nullptr && horizontal->nxtCol->col == xPos) {
        horizontal->nxtCol->value = value;
        if (xPos+1 > columnas) {
        columnas = xPos+1;
        }
        if (yPos+1 > filas) {
        filas = yPos+1;
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
    
    if (xPos+1 > columnas) {
        columnas = xPos+1;
    }
    if (yPos+1 > filas) {
        filas = yPos+1;
    }
}


int SparseMatrix::get(int yPos, int xPos) {
    nodo* filaActual = head->nxtFil;
    if (filaActual == nullptr) {
        std::cout << "La matriz esta vacia." << std::endl;
        return 0;
    }
    while (filaActual != nullptr) {
        nodo* nodoActual = filaActual->nxtCol; // Empezamos en el primer nodo con valor de la fila.

        // Recorremos cada nodo en la fila actual
        while (nodoActual != nullptr) {
            if (nodoActual->fil == yPos && nodoActual->col == xPos) {
                return nodoActual->value;
            }
            nodoActual = nodoActual->nxtCol;
        }
        filaActual = filaActual->nxtFil;
    }
    return 0;
}

void SparseMatrix::remove(int yPos, int xPos) {
    nodo* filaActual = head->nxtFil;
    if (filaActual == nullptr) {
        std::cout << "La matriz esta vacia." << std::endl;
        return;
    }

    while (filaActual != nullptr) {
        nodo* nodoActual = filaActual->nxtCol;

        while (nodoActual != nullptr) {
            if (nodoActual->fil == yPos && nodoActual->col == xPos) {
                nodoActual->value = 0;
                std::cout<<"Nodo Reseteado a 0"<<std::endl;
            }
            nodoActual = nodoActual->nxtCol;
        }
        filaActual = filaActual->nxtFil;
    }

}

void SparseMatrix::printStoredValues() {
    
    nodo* filaActual = head->nxtFil;

    if (filaActual == nullptr) {
        std::cout << "La matriz esta vacia." << std::endl;
        return;
    }
    std::cout << "--- Contenido de la Matriz ---" << std::endl;
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
    double elementCount = 0;
    nodo* filaActual = head->nxtFil;

    // Contar elementos no nulos
    while (filaActual != nullptr) {
        nodo* nodoActual = filaActual->nxtCol;
        while (nodoActual != nullptr) {
            elementCount++;
            nodoActual = nodoActual->nxtCol;
        }
        filaActual = filaActual->nxtFil;
    }

    if (elementCount == 0) {
        return 0;
    }

    // Calcular tamaño total usando las variables miembro
    double totalSize = (double)(filas + 1) * (columnas + 1);

    if (totalSize == 0) {
        return 0;
    }

    // Retornar densidad como porcentaje
    return (int)((elementCount / totalSize) * 100);
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
        return nullptr;
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
               nodoActual = nodoActual->nxtCol;
            }
            if (suma > 0){
                MxNueva->add(suma,filaA->fil,colM2->col);
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
