#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cstdlib>

using namespace std;

#include "Newton.cpp"
#include "Broyden.cpp"
#include "SplineCubico.cpp"



#define MAX_SISTEMA 3
#define TOL 1e-6
#define MAX_IT 100

// --- FUNCIONES AUXILIARES ---

void limpiar() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausa() {
    cout << "\nPresiona Enter para continuar...";
    cin.ignore();
    cin.get();
}

// --- PORTADA PRINCIPAL ---
void portadaPrincipal() {
    limpiar();
    cout << "=============================================" << endl;
    cout << "            METODOS NUMERICOS 2" << endl;
    cout << "=============================================" << endl << endl;
    cout << "        INTEGRANTES DEL EQUIPO:" << endl;
    cout << "        - Aranda Perez Juan Carlos" << endl;
    cout << "        - Fajardo De la O Gerardo" << endl;
    cout << "        - Lopez Cervantes Cristofes Uriel" << endl << endl;
    cout << "=============================================" << endl;
    pausa();
}


int main() {
    int opcion;
    portadaPrincipal();
    do {
        limpiar();
        cout << "========== MENU DE SELECCION ==========\n";
        cout << "1) Programa 1 (Broyden)\n";
        cout << "2) Programa 2 (Interpolacion Newton)\n";
        cout << "3) Programa 3 (Trazadores Cubicos)\n";
        cout << "4) Salir\n";
        cout << "=======================================\n";
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: runBroyden(); pausa(); break;
            case 2: runNewton(); pausa(); break;
            case 3: runSpline(); pausa(); break;
            default: cout << "\nOpcion no valida.\n"; pausa();
        }
    } while(opcion != 4);
    return 0;
}