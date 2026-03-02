#include "sala.h"
#include <stdlib.h>

unsigned int CAPACIDAD;
int actualCapacity;

unsigned int* seats = NULL;

unsigned int empty_seats;
unsigned int occupied_seats;

int reserva_asiento(int id_persona) {
    if(seats == NULL) {
        return - 1;
    }

    for(int i = 0; i < actualCapacity; i++) {

        if(seats[i] == 0) {
            seats[i] = id_persona;
            empty_seats--;
            occupied_seats++;
            return i;
        }
    }

    return -1;
}

int libera_asiento(int id_asiento) {
    if(seats == NULL || id_asiento >= actualCapacity || seats[id_asiento] == 0) return -1;

    int seat = seats[id_asiento];

    seats[id_asiento] = 0;

    return seat;
}

int estado_asiento(int id_asiento) {
    if(seats == NULL) return -1;

    int seat = seats[id_asiento];

    return seat;
}

int asientos_libres() {
    return empty_seats;
}

int asientos_ocupados() {
    return actualCapacity - empty_seats;
}

int capacidad_sala() {
    return actualCapacity;
}

int crea_sala(int capacidad) {
    if (capacidad <= 0) return -1;

    if(seats != NULL) {
        return -1;
    }

    seats = malloc(capacidad * sizeof(unsigned int));

    if (seats == NULL) return -1;

    for(int i = 0; i < capacidad; i++) {
        seats[i] = 0;
    }

    actualCapacity = capacidad;
    empty_seats = capacidad;
    occupied_seats = 0;

    return capacidad;
}

int elimina_sala() {
    if(seats == NULL) {
        return -1;
    }

    free(seats);
    seats = NULL;
    empty_seats = 0;
    occupied_seats = 0;
    actualCapacity = 0;

    return 0;
}