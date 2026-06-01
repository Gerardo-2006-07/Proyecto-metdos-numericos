#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

double funcion1(double x)
{
    return pow(x,4.0)*sqrt(3.0+2.0*x*x)/3.0;
}

double funcion2(double x)
{
    return pow(x,5.0)/pow(x*x+4.0,1.0/5.0);
}

double trapecio(double (*f)(double), double a, double b, int n)
{
    double h=(b-a)/n;
    double suma=f(a)+f(b);

    for(int i=1;i<n;i++)
        suma+=2.0*f(a+i*h);

    return (h/2.0)*suma;
}

void mostrarTablaPuntos(double (*f)(double), double a, double b, int n, int nivel)
{
    double h=(b-a)/n;

    cout << "\n============================================================\n";
    cout << "TRAPECIO NIVEL " << nivel << "\n";
    cout << "============================================================\n";
    cout << "n = " << n << "\n";
    cout << "h = " << fixed << setprecision(7) << h << "\n\n";

    cout << left << setw(10) << "i"
         << setw(20) << "xi"
         << setw(20) << "f(xi)" << "\n";

    cout << "------------------------------------------------------------\n";

    for(int i=0;i<=n;i++)
    {
        double xi=a+i*h;

        cout << left
             << setw(10) << i
             << setw(20) << fixed << setprecision(7) << xi
             << setw(20) << fixed << setprecision(7) << f(xi)
             << "\n";
    }

    cout << "------------------------------------------------------------\n";

    double I=trapecio(f,a,b,n);

    cout << "\nI(h" << nivel << ") = "
         << fixed << setprecision(7)
         << I << "\n";
}

void mostrarExtrapolacion(int i,int j,double actual,double anterior,double resultado)
{
    cout << "\n============================================================\n";
    cout << "EXTRAPOLACION R[" << i << "][" << j << "]\n";
    cout << "============================================================\n";

    cout << "R[" << i << "][" << j << "] = "
         << actual
         << " + ("
         << actual
         << " - "
         << anterior
         << ")/(4^"
         << j
         << "-1)\n";

    cout << "Resultado = "
         << fixed << setprecision(7)
         << resultado << "\n";
}

void tablaRomberg(const vector<vector<double>>& R,
                  const vector<double>& h,
                  int niveles)
{
    cout << "\n\n===============================================================================================\n";
    cout << "                                     TABLA DE ROMBERG\n";
    cout << "===============================================================================================\n";

    cout << setw(6) << "k"
         << setw(15) << "h"
         << setw(18) << "O(h^2)"
         << setw(18) << "O(h^4)"
         << setw(18) << "O(h^6)"
         << setw(18) << "O(h^8)"
         << setw(18) << "O(h^10)"
         << "\n";

    cout << "-----------------------------------------------------------------------------------------------\n";

    for(int i=0;i<niveles;i++)
    {
        cout << setw(6) << i+1;
        cout << setw(15) << fixed << setprecision(7) << h[i];

        for(int j=0;j<=i;j++)
            cout << setw(18) << fixed << setprecision(7) << R[i][j];

        cout << "\n";
    }

    cout << "===============================================================================================\n";
}

void romberg(double (*f)(double),
             double a,
             double b,
             int nivelesMax)
{
    vector<vector<double>> R(nivelesMax, vector<double>(nivelesMax,0.0));
    vector<double> h(nivelesMax);

    int nivelesUsados=nivelesMax;
    double error=0.0;

    for(int i=0;i<nivelesMax;i++)
    {
        int n=(int)pow(2,i);

        h[i]=(b-a)/n;

        mostrarTablaPuntos(f,a,b,n,i+1);

        R[i][0]=trapecio(f,a,b,n);

        for(int j=1;j<=i;j++)
        {
            R[i][j]=R[i][j-1]
                   +(R[i][j-1]-R[i-1][j-1])
                   /(pow(4,j)-1);

            mostrarExtrapolacion(
                i,j,
                R[i][j-1],
                R[i-1][j-1],
                R[i][j]
            );
        }

        if(i>0)
        {
            error=fabs(R[i][i]-R[i-1][i-1]);

            if(error<1e-7)
            {
                nivelesUsados=i+1;
                break;
            }
        }
    }

    tablaRomberg(R,h,nivelesUsados);

    cout << "\n============================================================\n";
    cout << "RESULTADO FINAL\n";
    cout << "============================================================\n";

    cout << "Integral aproximada : "
         << fixed << setprecision(7)
         << R[nivelesUsados-1][nivelesUsados-1]
         << "\n";

    if(nivelesUsados>1)
    {
        cout << "Error aproximado    : "
             << fixed << setprecision(7)
             << fabs(
                R[nivelesUsados-1][nivelesUsados-1]
                -
                R[nivelesUsados-2][nivelesUsados-2]
             )
             << "\n";
    }

    cout << "Niveles utilizados  : "
         << nivelesUsados
         << "\n";

    cout << "Precision objetivo  : 7 decimales\n";
}

int runRomberg()
{
    int opcion;
    char repetir='S';

    do
    {
        cout << "\n==================================================\n";
        cout << "      INTEGRACION NUMERICA - ROMBERG\n";
        cout << "==================================================\n\n";

        cout << "1. f(x)=x^4*sqrt(3+2x^2)/3\n\n";
        cout << "2. f(x)=x^5/(x^2+4)^(1/5)\n\n";
        cout << "3. Salir\n\n";

        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if(opcion==3)
            return 0;

        double a,b;
        int niveles;

        cout << "\nLimite inferior a: ";
        cin >> a;

        cout << "Limite superior b: ";
        cin >> b;

        while(a>=b)
        {
            cout << "Error: a debe ser menor que b.\n";
            cout << "Ingrese nuevamente b: ";
            cin >> b;
        }

        cout << "Numero maximo de niveles Romberg: ";
        cin >> niveles;

        while(niveles<2)
        {
            cout << "Ingrese un valor >= 2: ";
            cin >> niveles;
        }

        if(opcion==1)
            romberg(funcion1,a,b,niveles);
        else if(opcion==2)
            romberg(funcion2,a,b,niveles);

        cout << "\nDesea resolver otra integral? (S/N): ";
        cin >> repetir;

    }while(repetir=='S' || repetir=='s');

    return 0;
}
