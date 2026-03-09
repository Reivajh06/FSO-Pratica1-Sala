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
    printf("********** batería de pruebas para %s: ", titulo_test);
    // fflush fuerza que se imprima el mensaje anterior
    // sin necesidad de utilizar un salto de línea
    fflush(stdout);
}

void FIN_TEST (const char* titulo_test)
{
    printf ("********** hecho\n");
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


void ejecuta_tests ()
{
    test_ReservaBasica();
    // Añadir nuevos tests
    test_sala();
}

int main()
{
    puts("Iniciando tests...");

    ejecuta_tests();

    puts("Batería de test completa.");
}