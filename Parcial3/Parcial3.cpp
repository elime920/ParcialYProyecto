#include <iostream>
#include <math.h>

using namespace std;

// En el algoritmo del libro esta como INPUT                           

const int a = 0;
const int b = 2;
const int c = 0;
const int d = 1;
const int n = 6;
const int m = 5;
const int Nx = n-1;  //Mesh points
const int Ny = m-1;

void F(double [][Ny]);
void G(double [][Ny]);


int main()
{
  double TOL = 10e-10;

  // Paso 1                                                            

  double h = (b-a)/n;  //Paso en x.                                    
  double k = (d-c)/m;  //Paso en y.                                    

  double w[Nx][Ny];
  int N = 100;

  //Paso 5              
  
  double lamda = (h*h)/(k*k);
  double miu = 2*(1 + lamda);

  int l = 1;

  //Puntos de encaje                                            

  //Paso 2 y 3                                                         

  for (int i = 0; i < Nx; i++)
    x[i] = a + i*h;
  for (int j = 0; j < Ny; j++)
    y[j] = c + j*k;

  //Paso 4       
  
  for (int i = 1; i <= n-1; i++)
    {
      for (int j = 1; j <= m-1; j++)
        w[i][j] = 0;
    }


  return 0;
}

// f(x,y) pero creo que la tengo mala , solo que aún no estiendo como               
// la debo poner.                                                      

void F(double w[Nx][Ny])
{
  for (int i=0; i <= n; i++)
    {
      for (int j = 0; i <= m; j++)
	w[i][j] = i*exp(j);
        }
}

//Condiciones de frontera
// Esta tampoco se si la tengo buena!!!

void G(double w[Nx][Ny])
{
  for(int i = 1; i <= Nx+1; i++ )
    {
      for (int j = 0; j <= Ny; j++)
        {
          w[i][c] = 0;
          w[a][j] = 0;
          w[i][d] = exp(1)*i*(b/n);
          w[b][j] = (d/m)*2*exp(j);
        }
    }
}


  
