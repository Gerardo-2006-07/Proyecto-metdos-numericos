#include <iostream> // Librería para entrada y salida de datos
//#include <string>
#include <cmath>
#include <vector>
#include <iomanip> //Para decimales de precision
//std::fixed << std::setprecision(8) es para los decimales de presicion
using namespace std; // Para no escribir std:: en cout y endl

//Funciones prototipo
//    //Ordenamiento de los datos (x_i, f(x_i)) por el valor de x_i usando el algoritmo de burbuja
void ordenar(vector<double>& x, vector<double>& fx);
//    //Verificación de que los datos sean equidistantes
bool esEquidistante(const vector<double>& x);
//    //Construcción de la tabla de diferencias (tanto para progresivas como para regresivas, solo cambia el punto de inicio)
vector<vector<double>> tablaDiferencias(const vector<double>& fx, int inicio, int m);
//    //Función para calcular el valor de la interpolación usando la tabla de diferencias (tanto para progresivas como para regresivas, solo cambia la fórmula)
double newtonProgresivo(const vector<vector<double>>& tabla, double s, int grado);
//    //Función para calcular el valor de la interpolación usando la tabla de diferencias (tanto para progresivas como para regresivas, solo cambia la fórmula)
double newtonRegresivo(const vector<vector<double>>& tabla, double s, int grado);

//Funciones prototipo
//    //Ordenamiento de los datos (x_i, f(x_i)) por el valor de x_i usando el algoritmo de burbuja
void ordenar(vector<double>& x, vector<double>& fx);
//    //Verificación de que los datos sean equidistantes
bool esEquidistante(const vector<double>& x);
//    //Construcción de la tabla de diferencias (tanto para progresivas como para regresivas, solo cambia el punto de inicio)
vector<vector<double>> tablaDiferencias(const vector<double>& fx, int inicio, int m);
//    //Función para calcular el valor de la interpolación usando la tabla de diferencias (tanto para progresivas como para regresivas, solo cambia la fórmula)
double newtonProgresivo(const vector<vector<double>>& tabla, double s, int grado);
//    //Función para calcular el valor de la interpolación usando la tabla de diferencias (tanto para progresivas como para regresivas, solo cambia la fórmula)
double newtonRegresivo(const vector<vector<double>>& tabla, double s, int grado);

void runNewton(){
    int op = 0;
    char rep = 's';
    cout<<"\n\t--Interpolacion por diferencias de Newton--\n";
    cout<<"Integrantes: \nFajardo De la O Gerardo\nLopez Cervantes Cristofer Uriel\nCarlos\n\n";


    do
    {
        //1. Leer la tabla de valores
        //Solicitar el número de puntos de la tabla
        int n;
        cout<<"Ingrese el numero de puntos de la tabla: ";
        cin>>n;
        //    //Verificar que por lo menos sean 2 puntos para poder interpolar
        if(n < 2){
            cout<<"Se necesitan al menos 2 puntos\n";
            continue;
        }

        //    //Declarar vectores (AQUI, dentro del ciclo porque puede cambiar la tabla)
        vector<double> x, fx;
        //    //Asignar tamaño
        x.resize(n);
        fx.resize(n);

        //Leer los puntos (x_i, f(x_i)) y almacenarlos en arreglos o vectores
        cout<<"\nIngrese los valores:\n";
        for(int i = 0; i < n; i++){
            cout<<"x["<<i<<"]: ";
            cin>>x[i];
            cout<<"f(x)["<<i<<"]: ";
            cin>>fx[i];
        }

        //Preguntar ¿soncorrectos los datos? En caso de que NO solicitar la fila del valor a corregir, en caso de Si continuar
        do {
            //Mostrar tabla
            cout<<"\nTabla actual:\n";
            cout<<"i\t x[i]\t f(x)[i]\n"; 
            for(int i = 0; i < n; i++){
                cout<<i<<"\t "<<x[i]<<"\t "<<fx[i]<<"\n";
            }

            cout<<"\nSon correctos los datos? (S/N): ";
            cin>>rep;

            if(rep == 'N' || rep == 'n'){
                int pos;
                cout<<"Que fila desea corregir? (0 a "<<n-1<<"): ";
                cin>>pos;

                if(pos >= 0 && pos < n){
                    cout<<"Nuevo valor de x["<<pos<<"]: ";
                    cin>>x[pos];

                    cout<<"Nuevo valor de f(x)["<<pos<<"]: ";
                    cin>>fx[pos];
                } else {
                    cout<<"Indice invalido\n";
                }
            }

        } while (rep == 'N' || rep == 'n');

        //Verifique que los datos sean equidistantes y que estén ordenados, sino ordenarlos
        //    //Primero ordenamos los datos (con algoritmo de burbuja)
        ordenar(x, fx);
        cout<<"\nTabla actual (ordenada si era el caso):\n";
        cout<<"i\t x[i]\t f(x)[i]\n"; 
        for(int i = 0; i < n; i++){
            cout<<i<<"\t "<<x[i]<<"\t "<<fx[i]<<"\n";
        }

        //    //Vemos si los datos son equidistantes
        if(esEquidistante(x)){
            cout<<"\nLos datos son equidistantes\n";
        } else {
            cout<<"\nLos datos NO son equidistantes, no se puede usar esta tabla\n";
            rep = 'N';
        }

        while (rep!= 'N' && rep != 'n' ){
            //2
            //Solicitar el punto a interpolar. Verificar que esté dentro del intervalo de la tabla [x0, xn]
            double punto;
            cout<<"\nIngrese el punto a interpolar: ";
            cin>>punto;
            //    // Validar si está dentro del intervalo
            if(punto < x[0] || punto > x[n-1]){
                cout<<"El punto NO esta dentro del intervalo ["<<x[0]<<", "<<x[n-1]<<"]\n";
                cout<<"No se puede interpolar con esta tabla\n";
                continue; // regresa a pedir otro punto
            }


            //Leer el grado del polinomio. Comprobar que los puntos de la tabla son suficientes para el grado del polinomio solicitado
            int grado;
            cout<<"\nIngrese el grado del polinomio: ";
            cin>>grado;
            //Verificar que el grado sea menor que n-1 (porque para grado k se necesitan k+1 puntos)
            if(grado >= n){
                cout<<"El grado debe ser menor que "<<n-1<<"\n";
                continue;
            }

            //    //Cálculo de la "h" para las "s"
            double h;
            h = x[1] - x[0]; // Asumiendo que los datos son equidistantes, h es la diferencia entre dos puntos consecutivos


            // Encontrar el intervalo donde cae el punto
            int i = 0;
            for(int j = 0; j < n-1; j++){
                if(punto >= x[j] && punto <= x[j+1]){
                    i = j;
                    break;
                }
            }

            // Cantidad de puntos necesarios
            int m = grado + 1;

            // Índice de inicio
            int inicio;

            // DECISIÓN + SELECCIÓN DE PUNTOS
            double punto_medio = (x[0] + x[n-1]) / 2.0;
            if(punto <= punto_medio){
                cout<<"Mas cerca de x["<<i<<"], etonces, Progresivas\n";
                inicio = i; // progresivas: hacia adelante

                // VALIDACIÓN (sin ajustar)
                if(inicio + m > n){
                    cout<<"No hay suficientes puntos hacia adelante para un polinomio de grado "<<grado<<"\n";
                    continue; // vuelve a pedir otro punto
                }

                //    //Calculamos S para las progresivas: S=(x-x0)/h
                double s = (punto - x[inicio]) / h;

                //    //Función para crear la tabla
                vector<vector<double>> tabla = tablaDiferencias(fx, inicio, m);

                //3
                //Presentar la tabla de diferencias y el resultado
                //RESULTADOS
                //  // IMPRIMIR LA TABLA (Para que el usuario la vea)
                cout << "\n--- Tabla de Diferencias Progresivas ---\n";
                // Encabezados de las columnas (opcional para estética)
                for(int j = 0; j < m; j++) cout << "Diferencia " << j << "\t";
                cout << "\n----------------------------------------------------------\n";

                for(int i = 0; i < m; i++) {
                    for(int j = 0; j < m - i; j++) {
                        cout << fixed << setprecision(6) << tabla[i][j] << "\t";
                    }
                    cout << "\n"; // Salto de línea para cada fila
                }

                double resultado = newtonProgresivo(tabla, s, grado);
                
                //    // Imprimes el resultado
                cout << fixed << setprecision(8);
                cout << "\nEl valor interpolado P(" << punto << ") es: " << resultado << endl;


            } else {
                cout<<"Mas cerca de x["<<i+1<<"], entonces Regresivas\n";
                inicio = i + 1 - grado; // regresivas: hacia atrás

                // VALIDACIÓN (sin ajustar)
                if(inicio < 0){
                    cout<<"No hay suficientes puntos hacia atras para un polinomio de grado "<<grado<<"\n";
                    continue; // vuelve a pedir otro punto
                }

                //    //Calculamos S para las regresivas: S=(x-xn)/h
                double s = (punto - x[inicio + grado]) / h;

                //    //función para crear la tabla (será la misma que la de Progresivas)
                vector<vector<double>> tabla = tablaDiferencias(fx, inicio, m);

                
                //3
                //Presentar la tabla de diferencias y el resultado
                // RESULTADOS
                cout << "\n--- Tabla de Diferencias Regresivas ---\n";
                // Encabezados de las columnas (opcional para estética)
                for(int j = 0; j < m; j++) cout << "Diferencia " << j << "\t";
                cout << "\n----------------------------------------------------------\n";

                for(int i = 0; i < m; i++) {
                    for(int j = 0; j < m - i; j++) {
                        cout << fixed << setprecision(6) << tabla[i][j] << "\t";
                    }
                    cout << "\n";
                }

                // 3. Calcular el resultado con la función regresiva
                double resultado = newtonRegresivo(tabla, s, grado);

                // 4. Mostrar resultado
                cout << fixed << setprecision(8);
                cout << "\nCon s (regresiva) = " << s;
                cout << "\nEl valor interpolado P(" << punto << ") es: " << resultado << endl;


            }
            
            //4. Preguntar: ¿Desea interpolar otro punto con la misma tabla?
            cout<<"Desea interpolar otro punto con la misma tabla? (S/N): ";
            cin>>rep;
        }

        //Preguntar: ¿Desea cambiar la tabla?
        cout<<"Desea cambiar la tabla (para interpolar otro punto)? (S/N): ";
        cin>>rep;
    } while (rep != 'N' && rep != 'n');

    // return 0; // Indica que el programa terminó bien
}



//Construcción de funciones

//    //Ordenamiento de los datos (x_i, f(x_i)) por el valor de x_i usando el algoritmo de burbuja
void ordenar(vector<double>& x, vector<double>& fx) {
    int n = x.size();
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-1-i; j++){
            if(x[j] > x[j+1]){
                swap(x[j], x[j+1]);
                swap(fx[j], fx[j+1]);
            }
        }
    }
}

//    //Verificación de que los datos sean equidistantes
bool esEquidistante(const vector<double>& x) {
    int n = x.size();

    double d = x[1] - x[0];

    for(int i = 1; i < n-1; i++){
        if(abs((x[i+1] - x[i]) - d) > 1e-6){
            return false;
        }
    }
    return true;
}

//    //Construcción de la tabla de diferencias (tanto para progresivas como para regresivas, solo cambia el punto de inicio)
vector<vector<double>> tablaDiferencias(const vector<double>& fx, int inicio, int m) {
    vector<vector<double>> tabla(m, vector<double>(m, 0));

    // Primera columna (f(x))
    for(int i = 0; i < m; i++){
        tabla[i][0] = fx[inicio + i];
    }

    // Construcción de diferencias
    for(int j = 1; j < m; j++){
        for(int i = 0; i < m - j; i++){
            tabla[i][j] = tabla[i+1][j-1] - tabla[i][j-1];
        }
    }

    return tabla;
}


//    //Progresivas
double newtonProgresivo(const vector<vector<double>>& tabla, double s, int grado) {
    double resultado = tabla[0][0]; // f(x0)
    double term = 1.0;

    for(int i = 1; i <= grado; i++) {
        // Calcula el producto s(s-1)(s-2)...
        term *= (s - (i - 1));
        
        // Suma el término: (s_k * delta^k f0) / k!
        // tabla[0][i] corresponde a la diferencia de orden 'i' en el renglón superior
        resultado += (term * tabla[0][i]) / tgamma(i + 1);
    }

    return resultado;
}

//    //Regresivas
double newtonRegresivo(const vector<vector<double>>& tabla, double s, int grado) {
    // Para regresivas empezamos en el último dato de la primera columna: f(xn)
    double resultado = tabla[grado][0]; 
    double term = 1.0;

    for(int i = 1; i <= grado; i++) {
        // En regresivas la fórmula usa (s), (s+1), (s+2)...
        term *= (s + (i - 1));
        
        // Usamos las diferencias que suben desde el último renglón
        resultado += (term * tabla[grado - i][i]) / tgamma(i + 1);
    }

    return resultado;
}
