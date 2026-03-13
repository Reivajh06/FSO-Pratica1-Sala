#include "sala.h"
#include <stdlib.h>

unsigned int CAPACIDAD;

//Puntero del vector de asientos
unsigned int* seats = NULL;

//Contadores del número de asientos libres y ocupados del vector (array) de asientos, para evitar recorridos del vector
//innecesarios (que en capacidades altas afectaría negativamente al rendimiento)
unsigned int empty_seats;
unsigned int occupied_seats;

/**
 * Busca por el vector de asientos cualquier posición libre y asigna en ese asiento el id de la persona a sentar
 *
 * @param id_persona id de la persona a sentar
 * @return -1 si el vector de asientos no está inicializado o la sala está llena o el id del primer asiento que se encontró libre
 */
int reserva_asiento(int id_persona) {
    if(seats == NULL || id_persona <= 0 || occupied_seats == CAPACIDAD) return - 1;

    for(int i = 0; i < CAPACIDAD; i++) {

        if(seats[i] == 0) {
            seats[i] = id_persona;
            empty_seats--;
            occupied_seats++;
            return i + 1;
        }
    }

    return -1;
}

/**
 * Retorna el id de la persona sentada en el asiento especificado,
 * indicando que dicho asiento ahora esta vacío (0)
 *
 * @param id_asiento id del asiento a liberar
 * @return -1 si la sala no está inicializada o está vacío el asiento o el id de la persona sentada
 * en el asiento especificado
 **/
int libera_asiento(int id_asiento) {
    if(seats == NULL || id_asiento <= 0) return -1;

    if(id_asiento > CAPACIDAD) return -1;

    if(seats[id_asiento - 1] == 0) return -1;

    int person_id = seats[id_asiento - 1];

    seats[id_asiento - 1] = 0;
    empty_seats++;
    occupied_seats--;

    return person_id;
}

/**
 * Determina el estado actual del asiento especificado
 *
 * @param id_asiento id del asiento pasado por parámetro
 * @return -1 si el vector de asientos no está inicializado o el id es inválido, sino el estado del asiento especificado
 */
int estado_asiento(int id_asiento) {
    if(seats == NULL) return -1;

    if (id_asiento <= 0 || id_asiento > CAPACIDAD) return -1;

    int seat = seats[id_asiento - 1];

    return seat;
}

/**
 * Determina el número de asientos libres en la sala
 *
 * @return -1 si el vector de asientos no está inicializado, sino el número de asientos vacíos
 */
int asientos_libres() {
    if(seats == NULL) return -1;

    return empty_seats;
}

/**
 * Determina el número de asientos ocupados en la sala
 *
 * @return -1 si el vector de asientos no está inicializado, sino el número de asientos ocupados
 */
int asientos_ocupados() {
    if(seats == NULL) return -1;

    return occupied_seats;
}

/**
 * Determina la capacidad de la sala, especificada cuando se inicializó el vector de asientos
 *
 * @return -1 si el vector de asientos no está inicializado, sino la capacidad del vector
 */
int capacidad_sala() {
    if(seats == NULL) return -1;

    return CAPACIDAD;
}

/**
 * Reserva memoria para inicializar el vector de asientos, dada la capacidad del mismo
 *
 * @param capacidad longitud que tendrá el vector de asientos
 * @return -1 si la capacidad es inválida o ya está inicializado el vector de asientos (también por posibles fallos al alojar memoria),
 * sino devuelve la capacidad especificada del vector
 */
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

/**
 * Libera la memoria utilizada por el vector de asientos
 *
 * @return -1 si el vector no está inicializado, o 0 si se realizó con éxito
 */
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