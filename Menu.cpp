#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cstdlib>

using namespace std;

#include "Newton.cpp"
#include "Broyden.cpp"
#include "SplineCubico.cpp"
#include "Romberg.cpp"



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
        cout << "A) Sistemas de ecuaciones no lineales (Broyden).\n";
        cout << "\t1) Programa 1 (Broyden)\n";
        cout << "B) Interpolación y ajuste de curvas.\n";
        cout << "\t2) Programa 2 (Interpolacion Newton)\n";
        cout << "\t3) Programa 3 (Trazadores Cubicos)\n";
        cout << "C) Integración (datos equidistantes)\n";
        cout << "\t4) Programa 4 (Romberg)\n";
        cout << "5) Salir\n";
        cout << "=======================================\n";
        cout << "Selecciona una opcion: ";
        //cin >> opcion;

        if (!(cin >> opcion) || opcion < 1 || opcion > 5) {
            cout << "\nError: Debes ingresar un numero en el rango indicado.\n";

            cin.clear(); // Limpia el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta la entrada incorrecta

            pausa();
            continue;
        }
     

        switch(opcion) {
            case 1: runBroyden(); pausa(); break;
            case 2: runNewton(); pausa(); break;
            case 3: runSpline(); pausa(); break;
            case 4: runRomberg(); pausa(); break;
            case 5: cout << "\nSaliendo del programa...\n"; break;
            default: cout << "\nOpcion no valida.\n"; pausa();
        }
    } while(opcion != 5);
    return 0;
}