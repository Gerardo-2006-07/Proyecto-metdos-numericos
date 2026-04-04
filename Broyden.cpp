#include <iostream> // Librería para entrada y salida de datos
//#include <string>
#include <cmath>
#include <iomanip> //Para decimales de precision
//std::fixed << std::setprecision(8) es para los decimales de presicion
using namespace std; // Para no escribir std:: en cout y endl

//Prototipos de funciones
void solSist2x2(int op);
void solSist3x3(int op);

//Prototipos de las funciones matriciales
//Invresa
bool inversa2x2();
bool inversa3x3();

//Para calcular xk+1
void xkMas1_2x2(
    float A[][2],
    float B[][1],
    float C[][1],
    float D[][1]
);

void xkMas1_3x3(
    float A[][3],
    float B[][1],
    float C[][1],
    float D[][1]
);

bool actualizarJacobianaBroyden2x2(
    float J[2][2],      // A^{-1} anterior → se actualiza aquí
    float xk[2][1],     // x_k
    float xk_1[2][1],   // x_{k-1}
    float Fk[2][1],     // F(x_k)
    float Fk_1[2][1]    // F(x_{k-1})
);

bool actualizarJacobianaBroyden3x3(
    float J[3][3],      // A^{-1} anterior → se actualiza aquí
    float xk[3][1],     // x_k
    float xk_1[3][1],   // x_{k-1}
    float Fk[3][1],     // F(x_k)
    float Fk_1[3][1]    // F(x_{k-1})
);



//Jacobiana para las 2x2, inicialiada en 0s
float J2x2[2][2] = {{0,0},{0,0}};
//Vectores vacios para los claculos
float x10[2][1];
float x11[2][1];
float F1X[2][1];
float F1X1[2][1];

//Funciones 2x2
float broyden1_funcion1(float x, float y) { return x*x + x*y + 2*y*y - 5; }
float broyden1_funcion2(float x, float y) { return 5*y - 2*x*y*y + 3; }
float broyden2_funcion1(float x, float y) { return x*x-3*y*y-10; }
float broyden2_funcion2(float x, float y) { return 2*y*y-3*x*y+1; }

float (*funciones[4])(float, float) = { broyden1_funcion1, broyden1_funcion2, broyden2_funcion1, broyden2_funcion2};

void jacobiana1(float x, float y);
void jacobiana2(float x, float y);

//Para las Jacobianas
void (*jacobianas2x2[2])(float, float) = {
    jacobiana1,
    jacobiana2
};

//Jacobiana para las 3x3, inicialiada en 0s
float J3x3[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
//Vectores vacios para los claculos
float x20[3][1];
float x21[3][1];
float F2X[3][1];
float F2X1[3][1];

//Funciones 3x3
float broyden3_funcion1(float x, float y, float z) { return 3*x*x+y*y-8*y+2*z*z-5; }
float broyden3_funcion2(float x, float y, float z) { return -2*x*x-12*x+y*y-3*z*z+10; }
float broyden3_funcion3(float x, float y, float z) { return -x+2*y+5*z; }
float broyden4_funcion1(float x, float y, float z) { return x*x+y*y-2*z+3; }
float broyden4_funcion2(float x, float y, float z) { return x+y+z-5; }
float broyden4_funcion3(float x, float y, float z) { return x*x-y*y+z*z-9; }

float (*funciones3x3[6])(float, float, float) = {
    broyden3_funcion1, broyden3_funcion2, broyden3_funcion3,
    broyden4_funcion1, broyden4_funcion2, broyden4_funcion3
};

void jacobiana3(float x, float y, float z);
void jacobiana4(float x, float y, float z);

//Para las Jacobianas
void (*jacobianas3x3[2])(float, float, float) = {
    jacobiana3,
    jacobiana4
};

void runBroyden(){
    int op = 0;
    cout<<"\n\t--Metodo de Broyden--\n";
    cout<<"Integrantes: \nFajardo De la O Gerardo\nLopez Cervantes Cristofes Uriel\nOtro\n\n";
    while (op != 5){
        cout<<"Menu con sistemas de ecuaciones disponibles:\n\n";    
        cout<<"1.f1(x,y)=x^2+xy+2y^2-5\n  f2(x,y)=5y-2xy^2+3\n\n";
        cout<<"2.f1(x,y)=x^2-3y^2-10\n  f2(x,y)=2y^2-3xy+1\n\n";
        cout<<"3.f1(x,y,z)=3x^2+y^2-8y+2z^2-5\n  f2(x,y,z)=-2x^2-12x+y^2-3z^2+10\n  f3(x,y,z)=-x+2y+5z\n\n";
        cout<<"4.f1(x,y,z)=x^2+y^2-2z+3\n  f2(x,y,z)=x+y+z-5\n  f3(x,y,z)=x^2-y^2+z^2-9\n\n";
        cout<<"5.Salir\n\n";
        cout<<"Ingrese la opcion del sistema a resolver: ";
        cin>>op;
        switch (op)
        {
            case 1:
                cout << "f1(x,y)=x^2+xy+2y^2-5\nf2(x,y)=5y-2xy^2+3\n\n";
                solSist2x2(op);
                break;
            case 2:
                cout << "f1(x,y)=x^2-3y^2-10\nf2(x,y)=2y^2-3xy+1\n\n";
                solSist2x2(op);
                break;
            case 3:
                cout << "f1(x,y,z)=3x^2+y^2-8y+2z^2-5\nf2(x,y,z)=-2x^2-12x+y^2-3z^2+10\nf3(x,y,z)=-x+2y+5z\n\n";
                solSist3x3(op);
                break;
            case 4:
                cout << "f1(x,y,z)=x^2+y^2-2z+3\nf2(x,y,z)=x+y+z-5\nf3(x,y,z)=x^2-y^2+z^2-9\n\n";
                solSist3x3(op);
                break;
            case 5:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Ingrese una opcion valida (1-5)\n";
                break;
        }
    }

    // return 0; // Indica que el programa terminó bien
}

//Funciones para 2x2 con Broyden
void solSist2x2(int op){
    //Inicializar vectores vacios
    
    for (size_t i = 0; i < 2; i++){
        J2x2[i][0] = 0;
        J2x2[i][1] = 0;
    }
    for (size_t i = 0; i < 2; i++){
        x10[i][0] = 0;
        x11[i][0] = 0;
        F1X[i][0] = 0;
        F1X1[i][0] = 0;
    }

    int iter = 0;
    float error_F;
    float vector[2][1]; // Valores iniciales para x e y

    float max_iter = 100; // Número máximo de iteraciones
    float error = 0.0005; // Tolerancia para la convergencia

    //cout << "f1(x,y)=x^2+xy+2y^2-5\nf2(x,y)=5y-2xy^2+3\n";
    cout << "Ingrese x0: ";  cin >> x10[0][0];
    cout << "Ingrese y0: ";  cin >> x10[1][0];
    cout << "Ingrese tolerancia: "; cin >> error;
    cout << "Ingerese numero maximo de iteraciones: "; cin >> max_iter;

    //Usamos Newton para obtener la primera iteracion y la Jacobiana
    jacobianas2x2[op-1](x10[0][0], x10[1][0]);
    
    //Calculamos la inversa de la Jacobiana   
    if(!inversa2x2()){
        return;
    }

    //Calculamos F(x0)
    /*
    F1X[0][0] = funciones[op-1](x10[0][0], x10[1][0]);
    F1X[1][0] = funciones[op-1](x10[0][0], x10[1][0]);
    */

    int base = (op - 1) * 2;
    F1X[0][0] = funciones[base](x10[0][0], x10[1][0]);
    F1X[1][0] = funciones[base + 1](x10[0][0], x10[1][0]);

    //Calculamos x1 = x0 - J^-1 * F(x0)
    for(int i=0; i<2; i++){
        x11[i][0] = x10[i][0];
        for(int j=0; j<2; j++){
            x11[i][0] -= J2x2[i][j]*F1X[j][0];
        }
    }

    //Aplicamos Bryden ya con x1 y F(x1) para actualizar la Jacobiana
    cout << "Iteraciones por Broyden:\n";
    
    do{
        // 1. Evaluar F en el punto nuevo (x11)
        //F1X1[0][0] = funciones[op-1](x11[0][0], x11[1][0]);
        //F1X1[1][0] = funciones[op-1](x11[0][0], x11[1][0]);

        F1X1[0][0] = funciones[base](x11[0][0], x11[1][0]);
        F1X1[1][0] = funciones[base + 1](x11[0][0], x11[1][0]);

        // 2. Calcular error
        error_F = fabs(F1X1[0][0]);
        if(fabs(F1X1[1][0]) > error_F) error_F = fabs(F1X1[1][0]);

        cout << "Iter " << iter << ": x=[" << x11[0][0] << ", " << x11[1][0] << "] --- Error: " << error_F << endl;

        if (error_F < error) break;

        // 3. ACTUALIZAR LA INVERSA (Broyden)
        // Usamos: inversa actual, x_nuevo, x_viejo, F_nueva, F_vieja
        actualizarJacobianaBroyden2x2(J2x2, x11, x10, F1X1, F1X);

        // 4. Preparar para la siguiente iteración
        // El punto actual (x11) pasa a ser el viejo (x10)
        for(int i=0; i<2; i++){
            x10[i][0] = x11[i][0];
            F1X[i][0] = F1X1[i][0];
        }

        // 5. Calcular el PRÓXIMO punto x11 usando la inversa actualizada
        // x_sig = x_actual - J_inv * F_actual
        float proximo_x[2][1];
        xkMas1_2x2(J2x2, F1X, x10, proximo_x); 
        
        x11[0][0] = proximo_x[0][0];
        x11[1][0] = proximo_x[1][0];

        iter++;
    } while (iter<max_iter && error_F > error);
        
    cout << "Solucion encontrada: x = " << x11[0][0] << ", y = " << x11[1][0] << "\n";
    cout << "Numero de iteraciones: " << iter << endl;

}   

//Funciones para 3x3 con Broyden
void solSist3x3(int op){
    //Inicializar vectores vacios
    for (size_t i = 0; i < 3; i++){
        J3x3[i][0] = 0;
        J3x3[i][1] = 0;
        J3x3[i][2] = 0;
    }
    for (size_t i = 0; i < 3; i++){
        x20[i][0] = 0;
        x21[i][0] = 0;
        F2X[i][0] = 0;
        F2X1[i][0] = 0;
    }
    
    int iter = 0;
    float error_F;
    float vector[3][1]; // Valores iniciales para x, y, z

    float max_iter = 100; // Número máximo de iteraciones
    float error = 0.0005; // Tolerancia para la convergencia
    //cout << "f1(x,y,z)=3x^2+y^2-8y+2z^2-5\nf2(x,y,z)=-2x^2-12x+y^2-3z^2+10\nf3(x,y,z)=-x+2y+5z\n";
    cout << "Ingrese x0: ";  cin >> x20[0][0];
    cout << "Ingrese y0: ";  cin >> x20[1][0];
    cout << "Ingrese z0: ";  cin >> x20[2][0];
    cout << "Ingrese tolerancia: "; cin >> error;
    cout << "Ingerese numero maximo de iteraciones: "; cin >> max_iter;

    //Usamos Newton para obtener la primera iteracion y la Jacobiana
    jacobianas3x3[op-3](x20[0][0], x20[1][0], x20[2][0]);

    //Calculamos la inversa de la Jacobiana   
    if(!inversa3x3()){
        return;   
    }
    
    //calculamos F(x0)
    int base = (op - 3) * 3;
    F2X[0][0] = funciones3x3[base](x20[0][0], x20[1][0], x20[2][0]);
    F2X[1][0] = funciones3x3[base + 1](x20[0][0], x20[1][0], x20[2][0]);
    F2X[2][0] = funciones3x3[base + 2](x20[0][0], x20[1][0], x20[2][0]);

    //Calculamos x1 = x0 - J^-1 * F(x0)
    for(int i=0; i<3; i++){
        x21[i][0] = x20[i][0];
        for(int j=0; j<3; j++){
            x21[i][0] -= J3x3[i][j]*F2X[j][0];
        }
    }

    //Aplicamos Bryden ya con x1 y F(x1) para actualizar la Jacobiana
    cout << "Iteraciones por Broyden:\n";
    do{
        // 1. Evaluar F en el punto nuevo (x21)
        F2X1[0][0] = funciones3x3[base](x21[0][0], x21[1][0], x21[2][0]);
        F2X1[1][0] = funciones3x3[base + 1](x21[0][0], x21[1][0], x21[2][0]);
        F2X1[2][0] = funciones3x3[base + 2](x21[0][0], x21[1][0], x21[2][0]);

        // 2. Calcular error
        error_F = fabs(F2X1[0][0]);
        if(fabs(F2X1[1][0]) > error_F) error_F = fabs(F2X1[1][0]);
        if(fabs(F2X1[2][0]) > error_F) error_F = fabs(F2X1[2][0]);

        cout << "Iter " << iter << ": x=[" << x21[0][0] << ", " << x21[1][0] << ", " << x21[2][0] << "] --- Error: " << error_F << endl;

        if (error_F < error) break;

        // 3. ACTUALIZAR LA INVERSA (Broyden)
        // Usamos: inversa actual, x_nuevo, x_viejo, F_nueva, F_vieja
        actualizarJacobianaBroyden3x3(J3x3, x21, x20, F2X1, F2X);

        // 4. Preparar para la siguiente iteración
        // El punto actual (x21) pasa a ser el viejo (x20)
        for(int i=0; i<3; i++){
            x20[i][0] = x21[i][0];
            F2X[i][0] = F2X1[i][0];
        }

        // 5. Calcular el PRÓXIMO punto x21 usando la inversa actualizada
        // x_sig = x_actual - J_inv * F_actual
        float proximo_x[3][1];
        xkMas1_3x3(J3x3, F2X1, x21, proximo_x); 
        
        x21[0][0] = proximo_x[0][0];
        x21[1][0] = proximo_x[1][0];
        x21[2][0] = proximo_x[2][0];

        iter++;
    } while (iter<max_iter && error_F > error);
        
    cout << "Solucion encontrada: x = " << x21[0][0] << ", y = " << x21[1][0] << ", z = " << x21[2][0] << "\n";
    cout << "Numero de iteraciones: " << iter << endl;

}   

//Calculos de matrices

//Jacobiana 1
void jacobiana1(float x, float y){
    J2x2[0][0] = 2*x + y;
    J2x2[0][1] = x + 4*y;
    J2x2[1][0] = -2*y*y;
    J2x2[1][1] = 5 - 4*x*y;
}
//Jacobiana 2
void jacobiana2(float x, float y){
    J2x2[0][0] = 2*x;
    J2x2[0][1] = -6*y;
    J2x2[1][0] = -3*y;
    J2x2[1][1] = 4*y - 3*x;
}
//Jacobiana 3
void jacobiana3(float x, float y, float z){
    J3x3[0][0] = 6*x;
    J3x3[0][1] = 2*y - 8;    
    J3x3[0][2] = 4*z;
    J3x3[1][0] = -4*x - 12;
    J3x3[1][1] = 2*y;
    J3x3[1][2] = -6*z;
    J3x3[2][0] = -1;
    J3x3[2][1] = 2;
    J3x3[2][2] = 5;
}
//Jacobiana 4
void jacobiana4(float x, float y, float z){
    J3x3[0][0] = 2*x;
    J3x3[0][1] = 2*y;
    J3x3[0][2] = -2;
    J3x3[1][0] = 1;
    J3x3[1][1] = 1;
    J3x3[1][2] = 1;
    J3x3[2][0] = 2*x;
    J3x3[2][1] = -2*y;
    J3x3[2][2] = 2*z;
}


//Inversa de una matriz 2x2, se guarda en la variable global J2x2_inv
bool inversa2x2() {
    float det;
    float inv[2][2];  // ← MATRIZ LOCAL TEMPORAL

    det = J2x2[0][0]*J2x2[1][1] - J2x2[0][1]*J2x2[1][0];

    if (fabs(det) < 1e-10) {
        cout << "Jacobiano singular.\n";
        return false;
    }
    // Calcular inversa usando la matriz original
    inv[0][0] =  J2x2[1][1] / det;
    inv[0][1] = -J2x2[0][1] / det;
    inv[1][0] = -J2x2[1][0] / det;
    inv[1][1] =  J2x2[0][0] / det;

    // Copiar la inversa a la matriz global
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            J2x2[i][j] = inv[i][j];

    return true;
}

//Inversa de una matriz 3x3, se guarda en la variable global J3x3_inv
bool inversa3x3() {
    float det;
    float inv[3][3];  // ← MATRIZ LOCAL TEMPORAL

    det = J3x3[0][0]*(J3x3[1][1]*J3x3[2][2] - J3x3[1][2]*J3x3[2][1]) - J3x3[0][1]*(J3x3[1][0]*J3x3[2][2] - J3x3[1][2]*J3x3[2][0]) +
    J3x3[0][2]*(J3x3[1][0]*J3x3[2][1] - J3x3[1][1]*J3x3[2][0]);

    if (fabs(det) < 1e-12)
    {
        cout << "Jacobiano singular.\n";
        return false;
    }

    // Calcular inversa usando la matriz original
    inv[0][0] = (J3x3[1][1]*J3x3[2][2] - J3x3[1][2]*J3x3[2][1]) / det;
    inv[0][1] = (J3x3[0][2]*J3x3[2][1] - J3x3[0][1]*J3x3[2][2]) / det;
    inv[0][2] = (J3x3[0][1]*J3x3[1][2] - J3x3[0][2]*J3x3[1][1]) / det;
    inv[1][0] = (J3x3[1][2]*J3x3[2][0] - J3x3[1][0]*J3x3[2][2]) / det;
    inv[1][1] = (J3x3[0][0]*J3x3[2][2] - J3x3[0][2]*J3x3[2][0]) / det;
    inv[1][2] = (J3x3[0][2]*J3x3[1][0] - J3x3[0][0]*J3x3[1][2]) / det;
    inv[2][0] = (J3x3[1][0]*J3x3[2][1] - J3x3[1][1]*J3x3[2][0]) / det;
    inv[2][1] = (J3x3[0][1]*J3x3[2][0] - J3x3[0][0]*J3x3[2][1]) / det;
    inv[2][2] = (J3x3[0][0]*J3x3[1][1] - J3x3[0][1]*J3x3[1][0]) / det;

    // Copiar la inversa a la matriz global
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            J3x3[i][j] = inv[i][j];
        }
    }

    return true; // Retornar true si la inversa se calculó correctamente, false si la matriz es singular
}

//X_k+1 = x_k - A^{-1} F(x_k)
void xkMas1_2x2(float A[2][2], float B[2][1], float C[2][1], float D[2][1]){
    for (int i = 0; i < 2; i++) {
        D[i][0] = 0.0f;
        for (int j = 0; j < 2; j++) {
            D[i][0] += A[i][j] * B[j][0];
        }
    }
    //Le esramos el vector xk
    for(int i=0; i<2; i++){
        D[i][0] = D[i][0] * -1 + C[i][0];
    }
}

void xkMas1_3x3(float A[3][3], float B[3][1], float C[3][1], float D[3][1]){
    for (int i = 0; i < 3; i++) {
        D[i][0] = 0.0f;
        for (int j = 0; j < 3; j++) {
            D[i][0] += A[i][j] * B[j][0];
        }
    }
    //Le esramos el vector xk
    for(int i=0; i<3; i++){
        D[i][0] = D[i][0] * -1 + C[i][0];
    }
}

//Actualiza la Jacobiana usando el método de Broyden para matrices 2x2
bool actualizarJacobianaBroyden2x2( float J[2][2], float xk[2][1], float xk_1[2][1], float Fk[2][1], float Fk_1[2][1]){
    float dX[2][1], dF[2][1];
    float Ainv_dF[2][1];
    float u[2][1];
    float v[1][2];
    float denom = 0.0f;

    // ΔX = xk − xk−1
    // ΔF = Fk − Fk−1
    for(int i = 0; i < 2; i++){
        dX[i][0] = xk[i][0] - xk_1[i][0];
        dF[i][0] = Fk[i][0] - Fk_1[i][0];
    }

    // A^{-1} ΔF
    for(int i = 0; i < 2; i++){
        Ainv_dF[i][0] = 0.0f;
        for(int j = 0; j < 2; j++){
            Ainv_dF[i][0] += J[i][j] * dF[j][0];
        }
    }

    // u = ΔX − A^{-1}ΔF
    for(int i = 0; i < 2; i++){
        u[i][0] = dX[i][0] - Ainv_dF[i][0];
    }

    // v = (ΔX)^T A^{-1}
    for(int j = 0; j < 2; j++){
        v[0][j] = 0.0f;
        for(int i = 0; i < 2; i++){
            v[0][j] += dX[i][0] * J[i][j];
        }
    }

    // denominador = (ΔX)^T A^{-1} ΔF
    for(int i = 0; i < 2; i++){
        denom += dX[i][0] * Ainv_dF[i][0];
    }

    if (fabs(denom) < 1e-12){
        cout << "Broyden: denominador ~ 0, Jacobiana no actualizada\n";
        return false;
    }

    // A^{-1}_k = A^{-1}_{k-1} + (u v) / denom
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            J[i][j] += (u[i][0] * v[0][j]) / denom;
        }
    }

    return true;
}

//Actualiza la Jacobiana usando el método de Broyden para matrices 3x3
bool actualizarJacobianaBroyden3x3( float J[3][3], float xk[3][1], float xk_1[3][1], float Fk[3][1], float Fk_1[3][1]){
    float dX[3][1], dF[3][1];
    float Ainv_dF[3][1];
    float u[3][1];
    float v[1][3];
    float denom = 0.0f;

    // ΔX = xk − xk−1
    // ΔF = Fk − Fk−1
    for(int i = 0; i < 3; i++){
        dX[i][0] = xk[i][0] - xk_1[i][0];
        dF[i][0] = Fk[i][0] - Fk_1[i][0];
    }

    // A^{-1} ΔF
    for(int i = 0; i < 3; i++){
        Ainv_dF[i][0] = 0.0f;
        for(int j = 0; j < 3; j++){
            Ainv_dF[i][0] += J[i][j] * dF[j][0];
        }
    }

    // u = ΔX − A^{-1}ΔF
    for(int i = 0; i < 3; i++){
        u[i][0] = dX[i][0] - Ainv_dF[i][0];
    }

    // v = (ΔX)^T A^{-1}
    for(int j = 0; j < 3; j++){
        v[0][j] = 0.0f;
        for(int i = 0; i < 3; i++){
            v[0][j] += dX[i][0] * J[i][j];
        }
    }

    // denominador = (ΔX)^T A^{-1} ΔF
    for(int i = 0; i < 3; i++){
        denom += dX[i][0] * Ainv_dF[i][0];
    }

    if (fabs(denom) < 1e-12){
        cout << "Broyden: denominador ~ 0, Jacobiana no actualizada\n";
        return false;
    }

    // A^{-1}_k = A^{-1}_{k-1} + (u v) / denom
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            J[i][j] += (u[i][0] * v[0][j]) / denom;
        }
    }
    
    return true;
}