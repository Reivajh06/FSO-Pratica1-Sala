// test_sala.c
// ===============
// Batería de pruebas de la biblioteca "sala.h/sala.c"
//

#include <assert.h>
#include <stdio.h>
#include "sala.h"

#define DebeSerCierto(x)	assert(x)
#define DebeSerFalso(x)		assert(!(x))

void INICIO_TEST (const char* titulo_test)
{
    printf("**** batería de pruebas para %s: ", titulo_test);
    // fflush fuerza que se imprima el mensaje anterior
    // sin necesidad de utilizar un salto de línea
    fflush(stdout);
}

void FIN_TEST (const char* titulo_test)
{
    printf ("**** hecho\n");
}


void test_ReservaBasica()
{
    int mi_asiento;
#define CAPACIDAD 500
#define ID_1 1500

    INICIO_TEST("Reserva básica");
    crea_sala(CAPACIDAD);
    DebeSerCierto(capacidad_sala()==CAPACIDAD);
    DebeSerCierto((mi_asiento=reserva_asiento(ID_1))>=0);
    DebeSerCierto((asientos_libres()+asientos_ocupados())==CAPACIDAD);
    DebeSerCierto(estado_asiento(mi_asiento)>0);
    DebeSerCierto(libera_asiento(mi_asiento)==ID_1);
    DebeSerCierto((asientos_libres()+asientos_ocupados())==CAPACIDAD);
    elimina_sala();
    FIN_TEST("Reserva básica");
}

void test_sala() {
    int mi_asiento;
    #define CAPACIDAD 500
    #define ID_1 1500;
    INICIO_TEST("Sala");
    DebeSerCierto(capacidad_sala() == -1);
    DebeSerCierto(estado_asiento(50) == -1);
    DebeSerCierto(libera_asiento(20) == -1);
    DebeSerCierto(reserva_asiento(20) == -1);
    DebeSerCierto(asientos_ocupados() == -1);
    DebeSerCierto(asientos_libres() == -1);
    DebeSerCierto(capacidad_sala() == -1);
    DebeSerCierto(crea_sala(CAPACIDAD) == CAPACIDAD);
    DebeSerCierto(crea_sala(CAPACIDAD) == -1);
    DebeSerCierto(capacidad_sala() == CAPACIDAD);
    DebeSerCierto(estado_asiento(50) == 0);
    DebeSerCierto(reserva_asiento(20) == 1);
    DebeSerCierto(libera_asiento(1) == 20);
    DebeSerCierto(libera_asiento(1)== -1);
    DebeSerCierto(estado_asiento(1) == 0);
    DebeSerCierto(libera_asiento(510) == -1);
    DebeSerCierto(reserva_asiento(-2) ==-1);
    for (int i = 1; i <= CAPACIDAD; i++) {
        DebeSerCierto(reserva_asiento(i) == i);
    }
    DebeSerCierto(asientos_libres() == 0);
    DebeSerCierto(asientos_ocupados() == CAPACIDAD);
    DebeSerCierto(reserva_asiento(5) == -1);
    elimina_sala();
    DebeSerCierto(elimina_sala() == -1);
    DebeSerCierto(crea_sala(0)==-1);
    DebeSerCierto(crea_sala(-50) == -1);

    FIN_TEST("Reserva ");
}

void test_sala_reservar_sin_inicializar() {
    //Eliminamos la sala si fue creada previamente
    DebeSerCierto(elimina_sala());
    DebeSerCierto(reserva_asiento(2) == -1);
    DebeSerCierto(estado_asiento(2) == -1);
    DebeSerCierto(asientos_libres() == -1);
    DebeSerCierto(asientos_ocupados() == -1);
    DebeSerCierto(libera_asiento(4) == -1);

    FIN_TEST("Test sala reservar sin inicializar");
}

void test_sala_reservar_todos_los_asientos(int capacidad) {
    //Eliminamos la sala si ya fue creada antes
    elimina_sala();

    DebeSerCierto(crea_sala(capacidad) == capacidad);

    for(int i = 1; i <= capacidad; i++) {
        //reserva_asiento devuelve la posición del asiento en el array sala + 1.
        //Por tanto la reserva debe devolver el id de la persona.
        DebeSerCierto(reserva_asiento(i) == i);
        DebeSerCierto(estado_asiento(i) == i);
    }

    DebeSerCierto(asientos_libres() == 0);
    DebeSerCierto(asientos_ocupados() == capacidad);
}

void test_sala_reservar_con_sala_llena() {
    test_sala_reservar_todos_los_asientos(10);

    DebeSerCierto(reserva_asiento(2) == -1);
    DebeSerCierto(reserva_asiento(6) == -1);
    DebeSerCierto(reserva_asiento(7) == -1);
}

void test_sala_eliminar_algunos_asientos_y_volver_a_insertar() {
    test_sala_reservar_todos_los_asientos(10);

    DebeSerCierto(libera_asiento(1) == 1);
    DebeSerCierto(libera_asiento(10) == 10);
    DebeSerCierto(libera_asiento(5) == 5);

    //Comprobamos que efectivamente se han liberado dichas posiciones
    DebeSerCierto(estado_asiento(1) == 0);
    DebeSerCierto(estado_asiento(10) == 0);
    DebeSerCierto(estado_asiento(5) == 0);

    //Volvemos a insertar valores en las posiciones liberadas
    //Como las otras posiciones estan ocupadas, y la inserción es secuencial
    //deberia insertar los valores de manera que se vuelvan a llenar las posiciones 1, 5, 10, que en el array
    //son las posiciones 0, 4, 9
    DebeSerCierto(reserva_asiento(1) == 1);
    DebeSerCierto(reserva_asiento(5) == 5);
    DebeSerCierto(reserva_asiento(10) == 10);

    //Comprobamos el estado de los asientos despues de volver a insertar
    DebeSerFalso(estado_asiento(1) == 0);
    DebeSerFalso(estado_asiento(10) == 0);
    DebeSerFalso(estado_asiento(5) == 0);
}

void test_crear_sala_ya_inicializada() {
    //Eliminamos la sala si ya fue inicializada antes
    elimina_sala();

    DebeSerCierto(crea_sala(10) == 10);
    DebeSerCierto(crea_sala(10) == -1);
}


void ejecuta_tests ()
{
    test_ReservaBasica();
    // Añadir nuevos tests
    test_sala();
    test_sala_reservar_sin_inicializar();
    test_sala_reservar_todos_los_asientos(10);
    test_sala_reservar_con_sala_llena();
    test_sala_eliminar_algunos_asientos_y_volver_a_insertar();
    test_crear_sala_ya_inicializada();
}

int main()
{
    puts("Iniciando tests...");

    ejecuta_tests();

    puts("Batería de test completa.");
}