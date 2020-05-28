#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <iomanip>


using namespace std;

// En el algoritmo del libro esta como INPUT                           

const int a = 0;
const int b = 2;
const int c = 0;
const int d = 1;
const int n = 6;
const int m = 5;
const int Nx = n-1;   //Mesh points
const int Ny = m-1;
const double h = (b-a)/n;
const double k = (d-c)/m;

double F(int x, int y);
double G(int x, int y);




int main()
{
  double TOL = 10e-10;
                                    

  double w[Nx][Ny];
  int N = 100;

  //Paso 5              
  
  double lamda = (h*h)/(k*k);
  double miu = 2*(1 + lamda);

  int l = 1;

  //Puntos de encaje                                            

  //Paso 2 y 3                                                         

  for (int i = 0; i < Nx; i++)
    w[i][Ny] = a + i*h;
  for (int j = 0; j < Ny; j++)
    w[Nx][j] = c + j*k;

  //Paso 4       
  
  for (int i = 1; i <= n-1; i++)
    {
      for (int j = 1; j <= m-1; j++)
        w[i][j] = 0;
    }
  while( l <= N)
    {
      double z;
      double NORM;
      z = (-h*h*F(1,m-1) + G(a,m-1) + lamda*G(1,d) + lamda*w[1][m-2]
           + w[2][m-1])/miu;
      NORM = abs(z-w[1][m-1]);
      w[1][m-1] = z;
  for (int i = 2; i <= Nx-1; i++)
	{
          z = (-h*h*F(i,m-1) + lamda*G(i,d) + w[i-1][m-1] + w[i+1][m-1]
               + lamda*w[i][m-2])/miu;
          if( abs(w[i][m-1] - z) > NORM)
            NORM = abs(w[i][m-1] - z);
          w[i][m-1] = z;
        }
   z = (-h*h*F(n-1, m-1) + G(b,m-1) + lamda*G(n-1, d) + w[n-2][m-1]
           + lamda*w[n-1][m-2])/miu;
      if ( abs(w[n-1][m-1] - z) > NORM)
        NORM = abs(w[n-1][m-1] - z);
      w[n-1][m-1] = z;
	  
      for (int j = Ny-1; j >= 2; j--)
        {
          z = (-h*h*F(1,j) + G(a,j) + lamda*w[1][j+1] + lamda*w[1][j-1]
               + w[2][j])/miu;
          if ( abs(w[1][j] -z) > NORM)
            NORM = abs(w[1][j] - z);
          w[1][j] = z;
	      
	  for (int i = 2; i <= Nx-1; i++)
            {
              z = (-h*h*F(i,j) + w[i-1][j] + lamda*w[i][j+1] + w[i+1][j]
                   + lamda*w[i][j-1])/miu;
              if( abs(w[i][j]-z) > NORM )
                NORM = abs(w[i][j] - z);
              w[i][j] = z;

            }
          z = (-h*h*F(n-1,j) + G(b,j) + w[n-2][j] + lamda*w[n-1][j+1]
	       + lamda*w[n-1][j-1])/miu;
          if( abs(w[n-1][j]- z) > NORM)
            NORM = abs(w[n-1][j] - z);
          w[n-1][j] = z;
        }
	  
      z = (-h*h*F(1,1) + G(a,1) + lamda*G(1,c) + lamda*w[1][2] + w[2][1])/miu;
      if( abs(w[1][1]-z) > NORM)
	NORM = abs(w[1][1] -z);
      w[1][1] = z;

      for(int i = 2; i <= Nx-1; i++)
	{
          z = (-h*h*F(i,1) + lamda*G(i,c) + w[i-1][1] + lamda*w[i][2]
	       + w[i+1][1])/miu;
          if( abs(w[i][1] - z) > NORM)
            NORM = abs(w[i][1]-z);
	  w[i][1] = z;
        }

      z = (-h*h*F(n-1,1) + G(b,1) + lamda*G(n-1,c) + w[n-2][1]
           + lamda*w[n-1][2])/miu;
      if( abs(w[n-1][1] - z) > NORM)
	NORM = abs(w[n-1][1] -z);
      w[n-1][1] = z;
	  
      if(NORM <= TOL)
        {
          for (int i= 1; i<=Nx; i++)
            {
              for(int j = 1; j <= Ny; j++)
                cout << setw(20) << i
                     << setw(20) << j << setw(20) << w[i][j] << endl;
            }
	  cout << endl;
        }
      l = l+1;
    }
  return 0;
}

// f(x,y) pero creo que la tengo mala , solo que aún no estiendo como               
// la debo poner.                                                      

double F(int x, int y)
{
  int w[Nx][Ny];
  for (x=0; x <= Nx; x++)
    {
      for ( y = 0; y <= Ny; y++)
	return w[x][y] =-h*h*x*exp(y);
        }
}


//Condiciones de frontera
// Esta tampoco se si la tengo buena!!!

double G(int x, int y)
{
  int w[Nx][Ny];
  for(int x = 1; x <= Nx+1; x++ )
    {
      for (int y = 0; y <= Ny; y++)
        {
          return w[x][c] = 0, w[a][y] = 0, w[x][d] = exp(1)*x*h,w[b][y] = k*2*e\
xp(y);
        }
    }
}



  
