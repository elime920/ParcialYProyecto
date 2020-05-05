#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;

//En el algoritmo del libro esta como INPUT
const int a = 0;
const int b = 2;
const int c = 0;
const int d = 1;

const int n = 6;
const int m = 5;

const double TOL = 1.0e-10;
const int N = 100;

double F(int, int); //F(x_i, y_j) = -h^2 f(x_i, y_j)
double g(int, int);

//Paso 1: cantidades h y k
const double h = static_cast<double>(b-a)/static_cast<double>(n);
const double k = static_cast<double>(d-c)/static_cast<double>(m);

//Pasos 2 y 3: prototipos de funciones
double x(int); //regresa el valor de x con indice argumento
double y(int); //regresa el valor de y con indice argumento

int main()
{
  //Paso 4
  //Creacion de matriz para guardar el campo aproximado
  vector<vector<double>> w(n+1, vector<double>(m+1, 0));
  
  //poner condiciones de frontera y llenar los otros espacios con 0
  for (int i = 0; i <= n; i++)
  {
    for (int j = 0; j <= m; j++)
    {
      w[i][j] = g(i, j);
    }
  }
  
  //primera impresion de w: se confirma que las condiciones de
  //frontera estan bien ubicadas
  for (int i = 0; i <= n; i++)
  {
    for (int j = 0; j <= m; j++)
    {
      cout << setprecision(3) << w[i][j] << "\t";
    }
    cout << endl;
  }

  //Paso 5  
  double lambda = static_cast<double>((h*h)/(k*k));
  double mu = 2*(1 + lambda);
  int l = 1;

  //Pasos 7 a 20: algoritmo de gauss - Seidel
  double z = 0.0;
  double NORM = 0.0;
  
  while (l <= N)
  {
    //Paso 7
    z = (F(1,m-1) + g(a,m-1) + lambda*g(1,d) + lambda*w[1][m-2] + w[2][m-1]) / mu;
    NORM = abs(z - w[1][m-1]);
    w[1][m-1] = z;
    
    //Paso 8
    for (int i = 2; i <= n-2; i++)
    {
      z = (F(i,m-1) + lambda*g(i,d) + w[i-1][m-1] + w[i+1][m-1] + lambda*w[i][m-2]) / mu;
      if (abs(w[i][m-1] - z) > NORM) {NORM = abs(w[i][m-1] - z);}
      w[i][m-1] = z;
    }
   
   //Paso 9
    z = (F(n-1,m-1) + g(b,m-1) + lambda*g(n-1,d) + w[n-2][m-1] + lambda*w[n-1][m-2]) / mu;
    if (abs(w[n-1][m-1] - z) > NORM) {NORM = abs(w[n-1][m-1] - z);}
    w[n-1][m-1] = z;
    
    //Paso 10
    for (int j = m-2; j >= 2; j--)
    {
      //Paso 11
      z = (F(1,j) + g(a,j) + lambda*w[1][j+1] + lambda*w[1][j-1] + w[2][j]) / mu;
      if (abs(w[1][j] -z) > NORM) {NORM = abs(w[1][j] - z);}
      w[1][j] = z;
      
      //Paso 12
      for (int i = 2; i <= n-2; i++)
      {
        z = (F(i,j) + w[i-1][j] + lambda*w[i][j+1] + w[i+1][j] + lambda*w[i][j-1]) / mu;
        if (abs(w[i][j]-z) > NORM) {NORM = abs(w[i][j] - z);}
        w[i][j] = z;
      }
      
      //Paso 13
      z = (F(n-1,j) + g(b,j) + w[n-2][j] + lambda*w[n-1][j+1] + lambda*w[n-1][j-1]) / mu;
      if (abs(w[n-1][j]- z) > NORM) {NORM = abs(w[n-1][j] - z);}
      w[n-1][j] = z;
    } //fin de paso 10
    
    //Paso 14
    z = (F(1,1) + g(a,1) + lambda*g(1,c) + lambda*w[1][2] + w[2][1]) / mu;
    if (abs(w[1][1]-z) > NORM) {NORM = abs(w[1][1] -z);}
    w[1][1] = z;
    
    //Paso 15
    for(int i = 2; i <= n-2; i++)
    {
      z = (F(i,1) + lambda*g(i,c) + w[i-1][1] + lambda*w[i][2] + w[i+1][1]) / mu;
      if( abs(w[i][1] - z) > NORM) {NORM = abs(w[i][1]-z);}
      w[i][1] = z;
    }
    
    //Paso 16
    z = (F(n-1,1) + g(b,1) + lambda*g(n-1,c) + w[n-2][1] + lambda*w[n-1][2]) / mu;
    if( abs(w[n-1][1] - z) > NORM) {NORM = abs(w[n-1][1] -z);}
    w[n-1][1] = z;
  
    //Paso 17
    if (NORM <= TOL) 
    {
      cout << "l = " << l << ", NORM = " << NORM << endl;
      //Paso 18
      cout << "xi\tyi\tw[i][j]" << endl;
      for (int i = 1; i <= n-1; i++)
      {
        for(int j = 1; j <= m-1; j++)
        {
          cout << setprecision(3) << x(i) << "\t" << y(j) << "\t" << w[i][j] << endl;
        }
        cout << endl; //salto de linea
      }
      
      //Paso 20
      break;
      
    } //fin de paso 17

    //Paso 20
    l += 1;
  } //fin de ciclo while
  
  cout << "El ciclo termino con " << l << " iteraciones y con valor"
       " de NORM: " << NORM << endl;
  
  //Imprimir nuevamente el grid. Buena noticia: las condiciones
  //de frontera siguen intactas
  for (int i = 0; i <= n; i++)
  {
    for (int j = 0; j <= m; j++)
    {
      cout << setprecision(3) << w[i][j] << "\t"; //g(i, j) << "\t";//
    }
    cout << endl;
  }
  
  return 0;
}

//Estas funciones dan los valores de x, y para los indices i, j
double x(int i)
{
  return static_cast<double>(a + i * h);
}

double y(int j)
{
  return static_cast<double>(c + j * k);
}

//Esta funcion retorna el valor de -h^2 f(x_i, y_j)
double F(int i, int j)
{
  return (- h * h * x(i) * exp(y(j)));
}

//Esta funcion retorna la funcion con condiciones de frontera
//(evaluada en el punto x_i, y_j)
//y da el valor de 0 a puntos que no esten en la frontera
double g(int i, int j)
{
  double resultado = 0.0; //aca estara guardado el resultado
  
  if (i == 0) //primera condicion: u(0, y) = 0
    {resultado = 0.0;}
  
  else if (j == 0) //segunda condicion: u(x, 0) = x
    {resultado = x(i);}
  
  else if (i == n) //tercera condicion: u(2, y) = 2 e^y
    {resultado = 2.0 * exp(y(j));}
  
  else if (j == m) //cuarta condicion: u(x, 1) = e x
    {resultado = exp(1.0) * x(i);}
  
  return (resultado); //retornar el resultado segun la frontera
}
