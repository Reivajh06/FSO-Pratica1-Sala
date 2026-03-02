#include "sala.h"
#include <stdlib.h>

unsigned int CAPACIDAD;

//Puntero del vector de asientos
unsigned int* seats = NULL;

//Contadores del número de asientos libres y ocupados del vector (array) de asientos, para evitar recorridos del vector
//innecesarios (que en capacidades altas afectaría negativamente al rendimiento)
unsigned int empty_seats;
unsigned int occupied_seats;

int reserva_asiento(int id_persona) {
    if(seats == NULL || id_persona < 0 || occupied_seats == CAPACIDAD) return - 1;

    for(int i = 0; i < CAPACIDAD; i++) {

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
    if(seats == NULL || id_asiento < 0) return -1;

    if(seats[id_asiento] == 0) return -1;

    int seat = seats[id_asiento];

    seats[id_asiento] = 0;
    empty_seats++;
    occupied_seats--;

    return seat;
}

int estado_asiento(int id_asiento) {
    if(seats == NULL) return -1;

    if (id_asiento < 0) return -1;

    int seat = seats[id_asiento];

    return seat;
}

int asientos_libres() {
    if(seats == NULL) return -1;

    return empty_seats;
}

int asientos_ocupados() {
    if(seats == NULL) return -1;

    return occupied_seats;
}

int capacidad_sala() {
    if(seats == NULL) return -1;

    return CAPACIDAD;
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

    CAPACIDAD = capacidad;
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
    CAPACIDAD = 0;

    return 0;
}