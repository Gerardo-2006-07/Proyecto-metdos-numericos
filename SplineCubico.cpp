#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

struct Punto {
    double x;
    double y;
};

struct Coeficientes {
    double a, b, c, d;
};

// Lee los puntos desde un archivo CSV
std::vector<Punto> leerCSV(const std::string& filename) {
    std::vector<Punto> puntos;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string x_str, y_str;
        
        if (std::getline(ss, x_str, ',') && std::getline(ss, y_str, ',')) {
            try {
                puntos.push_back({std::stod(x_str), std::stod(y_str)});
            } catch (const std::exception& e) {
                // Ignorar encabezados o lineas invalidas
                continue;
            }
        }
    }
    
    if (puntos.size() < 3) {
        std::cerr << "Error: Se requieren al menos 3 puntos para la interpolacion por splines cubicos." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    return puntos;
}

// Resuelve un sistema de ecuaciones tridiagonal usando el Algoritmo de Thomas
std::vector<double> resolverTridiagonal(const std::vector<double>& inf, 
                                        std::vector<double> diag, 
                                        const std::vector<double>& sup, 
                                        std::vector<double> rhs) {
    size_t n = diag.size();
    std::vector<double> solucion(n);

    // Forward sweep
    for (size_t i = 1; i < n; ++i) {
        double m = inf[i - 1] / diag[i - 1];
        diag[i] -= m * sup[i - 1];
        rhs[i] -= m * rhs[i - 1];
    }

    // Back substitution
    solucion[n - 1] = rhs[n - 1] / diag[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        solucion[i] = (rhs[i] - sup[i] * solucion[i + 1]) / diag[i];
    }

    return solucion;
}

// Genera un script en Python para visualizar los resultados
void generarScriptGrafica(const std::vector<Punto>& puntos, const std::vector<Coeficientes>& polinomios) {
    std::ofstream script("graficar.py");
    if (!script.is_open()) {
        std::cerr << "Advertencia: No se pudo crear el script de graficacion." << std::endl;
        return;
    }

    script << "import matplotlib.pyplot as plt\n";
    script << "import numpy as np\n\n";
    
    // Graficar puntos originales
    script << "x_pts = [";
    for (size_t i = 0; i < puntos.size(); ++i) { script << puntos[i].x << (i < puntos.size()-1 ? ", " : ""); }
    script << "]\n";
    
    script << "y_pts = [";
    for (size_t i = 0; i < puntos.size(); ++i) { script << puntos[i].y << (i < puntos.size()-1 ? ", " : ""); }
    script << "]\n\n";
    
    script << "plt.scatter(x_pts, y_pts, color='black', zorder=5, label='Nodos (datos)')\n\n";

    // Graficar cada tramo del spline
    for (size_t i = 0; i < polinomios.size(); ++i) {
        script << "x_val = np.linspace(" << puntos[i].x << ", " << puntos[i+1].x << ", 100)\n";
        script << "y_val = " << polinomios[i].a << "*(x_val - " << puntos[i].x << ")**3 + "
               << polinomios[i].b << "*(x_val - " << puntos[i].x << ")**2 + "
               << polinomios[i].c << "*(x_val - " << puntos[i].x << ") + "
               << polinomios[i].d << "\n";
        //script << "plt.plot(x_val, y_val, label=f'Tramo {i}')\n";
        script << "plt.plot(x_val, y_val, label='Tramo " << i << "')\n";
    }

    script << "\nplt.title('Interpolacion por Trazadores Cubicos Naturales')\n";
    script << "plt.xlabel('X')\n";
    script << "plt.ylabel('Y')\n";
    script << "plt.legend()\n";
    script << "plt.grid(True)\n";
    script << "plt.show()\n";

    script.close();
    std::cout << "\n[+] Script de graficacion generado con exito en: py graficar.py" << std::endl;
}

void runSpline() {

    char continuar;
    do {


    std::string filename = "datos.csv";
    std::vector<Punto> puntos = leerCSV(filename);
    size_t n = puntos.size() - 1; // n intervalos

    std::vector<double> h(n);
    std::vector<double> f1(n);

    // 1. Calculos iniciales: hi y diferencias divididas f_i^[1]
    for (size_t i = 0; i < n; ++i) {
        h[i] = puntos[i + 1].x - puntos[i].x;
        f1[i] = (puntos[i + 1].y - puntos[i].y) / h[i];
    }

    // 2. Construccion del sistema tridiagonal para los nodos internos (1 a n-1)
    size_t num_ecuaciones = n - 1;
    std::vector<double> diag(num_ecuaciones);
    std::vector<double> inf(num_ecuaciones - 1);
    std::vector<double> sup(num_ecuaciones - 1);
    std::vector<double> rhs(num_ecuaciones);

    for (size_t i = 1; i <= num_ecuaciones; ++i) {
        diag[i - 1] = 2.0 * (h[i - 1] + h[i]);
        rhs[i - 1] = 6.0 * (f1[i] - f1[i - 1]);
        
        if (i < num_ecuaciones) {
            sup[i - 1] = h[i];
            inf[i - 1] = h[i];
        }
    }

    // 3. Solucion del sistema usando Thomas
    std::vector<double> S_internos = resolverTridiagonal(inf, diag, sup, rhs);

    // 4. Aplicar condiciones de frontera del Spline Natural (S_0 = 0, S_n = 0)
    std::vector<double> S(n + 1, 0.0);
    for (size_t i = 1; i < n; ++i) {
        S[i] = S_internos[i - 1];
    }

    /* REPETIDO
    std::cout << "--- VECTOR DE CURVATURAS (Si) ---" << std::endl;
    for (size_t i = 0; i <= n; ++i) {
        std::cout << "S[" << i << "] = " << S[i] << std::endl;
    }
    std::cout << "---------------------------------\n" << std::endl;
    */



    // --- MOSTRAR EL SISTEMA PARA OBTENER Si ---
    std::cout << "\n=========================================================" << std::endl;
    std::cout << "--- SISTEMA RESUELTO PARA CURVATURAS (Si) ---" << std::endl;
    for (size_t i = 0; i <= n; ++i) {
        std::cout << "S[" << i << "] = " << std::fixed << std::setprecision(6) << S[i] << std::endl;
    }
    std::cout << "=========================================================\n" << std::endl;







    // 5. Calculo de coeficientes para los polinomios
    std::vector<Coeficientes> polinomios(n);
    std::cout << "--- ECUACIONES DE LOS POLINOMIOS ---" << std::endl;
    


    // --- PRESENTAR TABLA CON Si, ai, bi, ci, di ---
    std::cout << "----------------------- TABLA DE RESULTADOS -----------------------" << std::endl;
    std::cout << std::left << std::setw(5) << "i" 
              << std::setw(12) << "Si" 
              << std::setw(12) << "ai" 
              << std::setw(12) << "bi" 
              << std::setw(12) << "ci" 
              << std::setw(12) << "di" << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;
    for (size_t i = 0; i < n; ++i) {
        polinomios[i].a = (S[i + 1] - S[i]) / (6.0 * h[i]);
        polinomios[i].b = S[i] / 2.0;
        polinomios[i].c = f1[i] - ((S[i + 1] + 2.0 * S[i]) / 6.0) * h[i];
        polinomios[i].d = puntos[i].y;

        std::cout << std::left << std::setw(5) << i 
                  << std::setw(12) << S[i] 
                  << std::setw(12) << polinomios[i].a 
                  << std::setw(12) << polinomios[i].b 
                  << std::setw(12) << polinomios[i].c 
                  << std::setw(12) << polinomios[i].d << std::endl;
    }
    std::cout << "-------------------------------------------------------------------\n" << std::endl;






    // --- PRESENTAR Polinomios ---
    std::cout << "----------------------- Polinomios Calculados -----------------------" << std::endl;
    for (size_t i = 0; i < n; ++i) {
        polinomios[i].a = (S[i + 1] - S[i]) / (6.0 * h[i]);
        polinomios[i].b = S[i] / 2.0;
        polinomios[i].c = f1[i] - ((S[i + 1] + 2.0 * S[i]) / 6.0) * h[i];
        polinomios[i].d = puntos[i].y;

        std::cout << "g_" << i << "(x) = ";
        std::cout << std::fixed << std::setprecision(4);
        std::cout << polinomios[i].a << "(x - " << puntos[i].x << ")^3 + "
                  << polinomios[i].b << "(x - " << puntos[i].x << ")^2 + "
                  << polinomios[i].c << "(x - " << puntos[i].x << ") + "
                  << polinomios[i].d << std::endl;
    }
    std::cout << "-------------------------------------------------------------------" << std::endl;



    // 6. Generar script en Python
    generarScriptGrafica(puntos, polinomios);



    

    // 7. Preguntar si desea realizar otro ajuste
        std::cout << "\x1B[33m" << "¿Desea realizar otro ajuste con otra tabla de valores? (s/n): " << "\x1B[0m";
        std::cin >> continuar;

        if (continuar == 's' || continuar == 'S') {
            std::cout << "\n[!] Modifica el archivo 'datos.csv' con tus nuevos valores y guarda los cambios." << std::endl;
            std::cout << ">>> Presiona ENTER cuando estes listo para recalcular..." << std::endl;
            std::cin.ignore(1000, '\n'); // Limpiar el buffer
            std::cin.get();             // Esperar el Enter del usuario
        }

    } while (continuar == 's' || continuar == 'S');

    





}