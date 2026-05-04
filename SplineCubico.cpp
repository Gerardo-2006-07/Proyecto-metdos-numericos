#include <iostream> // Librería para entrada y salida de datos
//#include <string>
#include <cmath>
#include <vector>
#include <iomanip> //Para decimales de precision
//std::fixed << std::setprecision(8) es para los decimales de presicion
using namespace std; // Para no escribir std:: en cout y endl

void runSplineCubico(){
    cout<<"\n\t--Metodo de Spline Cubico--\n";

    int n;
    cout << "Ingrese el numero de puntos: ";
    cin >> n;

    vector<float> x(n), y(n);
    cout << "Ingrese los puntos (x y) separados por espacio:\n";
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    // Aquí se implementaría el método de spline cúbico usando los puntos ingresados
    // Por ejemplo, se podrían calcular los coeficientes del spline cúbico y luego evaluar el spline en un punto específico
}