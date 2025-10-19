#include "SparseMatrix.h"
#include <iostream>

SparseMatrix::SparseMatrix() {
    // El constructor crea nuestro nodo de inicio.
    head = new nodo(-1, -1, -1);
}

SparseMatrix::~SparseMatrix() {

}

void SparseMatrix::add(int value, int xPos, int yPos) {
    // Primero, buscamos la posición correcta en la fila.
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

    // Avanzamos por la fila para encontrar la columna.
    nodo* horizontal = filaActual;
    while (horizontal->nxtCol != nullptr && horizontal->nxtCol->col < xPos) {
        horizontal = horizontal->nxtCol;
    }
    
    // Si ya existe un nodo aqui, solo cambiamos el valor y terminamos.
    if (horizontal->nxtCol != nullptr && horizontal->nxtCol->col == xPos) {
        horizontal->nxtCol->value = value;
        return;
    }

    // Si no existe, lo creamos y lo enlazamos en la fila.
    nodo* nuevoNodo = new nodo(value, yPos, xPos);
    nuevoNodo->nxtCol = horizontal->nxtCol;
    horizontal->nxtCol = nuevoNodo;

    // Ahora hacemos lo mismo para enlazarlo en la columna.
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
}


int SparseMatrix::get(int xPos, int yPos) {
    return 0;
}

void SparseMatrix::remove(int xPos, int yPos) {
}

void SparseMatrix::printStoredValues() {
}

int SparseMatrix::density() {
    return 0;
}

SparseMatrix* SparseMatrix::multiply(SparseMatrix* second) {
    return nullptr;
}