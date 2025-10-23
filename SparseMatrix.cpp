#include "SparseMatrix.h"
#include <iostream>
#include <ostream>

SparseMatrix::SparseMatrix() {
    // El constructor crea nuestro nodo de inicio
    head = new nodo(-1, -1, -1);
    columnas = 0;
    filas = 0;
    elementCount = 0;
}

SparseMatrix::~SparseMatrix() {
    nodo* filaActual = head->nxtFil;

    // Recorre cada fila
    while (filaActual != nullptr) {
        nodo* nodoActual = filaActual->nxtCol;
        
        // Borra todos los nodos de datos en la fila actual
        while (nodoActual != nullptr) {
            nodo* nodoABorrar = nodoActual;
            nodoActual = nodoActual->nxtCol;
            delete nodoABorrar;
        }

        nodo* filaABorrar = filaActual;
        filaActual = filaActual->nxtFil;
        delete filaABorrar;
    }

    // Borra las cabeceras de las columnas
    nodo* colActual = head->nxtCol;
    while (colActual != nullptr) {
        nodo* colABorrar = colActual;
        colActual = colActual->nxtCol;
        delete colABorrar;
    }
    delete head;
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
    elementCount++;

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
    nodo* vertical = head->nxtFil;

    // Busca la cabecera de la fila 'yPos'
    while (vertical != nullptr && vertical->fil < yPos) {
        vertical = vertical->nxtFil;
    }
    if (vertical == nullptr || vertical->fil != yPos) {
        return 0;
    }
    // Ahora busca el nodo 'xPos' solo en esa fila
    nodo* horizontal = vertical->nxtCol;
    while (horizontal != nullptr && horizontal->col < xPos) {
        horizontal = horizontal->nxtCol;
    }

    if (horizontal == nullptr || horizontal->col != xPos) {
        return 0;
    }
    return horizontal->value;
}

void SparseMatrix::remove(int yPos, int xPos) {
   // Encontrar el nodo previo en la fila
    nodo* vertical = head;
    while (vertical->nxtFil != nullptr && vertical->nxtFil->fil < yPos) {
        vertical = vertical->nxtFil;
    }
    if (vertical->nxtFil == nullptr || vertical->nxtFil->fil > yPos) {
        return;
    }
    nodo* prevHorizontal = vertical->nxtFil;

    // Avanza hasta el nodo *anterior* al que queremos borrar
    while (prevHorizontal->nxtCol != nullptr && prevHorizontal->nxtCol->col < xPos) {
        prevHorizontal = prevHorizontal->nxtCol;
    }
    if (prevHorizontal->nxtCol == nullptr || prevHorizontal->nxtCol->col > xPos) {
        return;
    }
    
    nodo* nodoABorrar = prevHorizontal->nxtCol;

    // Encontrar el nodo previo en la columna
    vertical = head;
    while (vertical->nxtCol != nullptr && vertical->nxtCol->col < xPos) {
        vertical = vertical->nxtCol;
    }
    if (vertical->nxtCol == nullptr || vertical->nxtCol->col > xPos) {
         return; 
    }
    nodo* prevVertical = vertical->nxtCol;

    while (prevVertical->nxtFil != nullptr && prevVertical->nxtFil->fil < yPos) {
        prevVertical = prevVertical->nxtFil;
    }

    // Desconectar el nodo de ambas listas
    prevHorizontal->nxtCol = nodoABorrar->nxtCol;
    prevVertical->nxtFil = nodoABorrar->nxtFil;

    delete nodoABorrar;
    elementCount--;
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
    if (elementCount == 0) {
        return 0;
    }
    double totalSize = (double)filas * columnas;

    if (totalSize == 0) {
        return 0;
    }

    // Retornar densidad como porcentaje
    return (int)(((double)elementCount / totalSize) * 100);
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
