#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "problems/problem2.h"

//MAIN
int main()
{
  //MATRIX CREATION
  std::vector<std::vector<double>> w(NT+1, std::vector<double>(NZ+1, 0.0));
  
  //MATRIX SETUP
  
  //first time line
  for (unsigned int j = 1; j < NZ; j++)
  {
    w[1][j] = mu * atilde(j) + nu * btilde(j) + 
              sigma * (atilde(j-1) + atilde(j+1));
  }
  
  //bounds
  for (unsigned int i = 0; i <= NT; i++)
  {
    for (unsigned int j = 0; j <= NZ; j++)
    {

      if (i == 0) w[i][j] = atilde(j);
      if (j == 0) w[i][j] = ctilde(i);
      if (j == NZ) w[i][j] = dtilde(i);
    }
  }
  
  //inner region
  for (unsigned int i = 0; i <= NT; i++)
  {
    for (unsigned int j = 0; j <= NZ; j++)
    {
      if (i > 0 && i < NT && j > 0 && j < NZ) 
      { 
        w[i+1][j] = alpha * w[i-1][j] + beta * w[i][j] + 
                    lambda * (w[i][j-1] + w[i][j+1]);
      }
    }
  }

  
  //PRINT MATRIX
  for (unsigned int i = 0; i <= NT; i++)
  {
    for (unsigned int j = 0; j <= NZ; j++)
    {
      std::cout << std::setprecision(4) << std::setw(8) << std::left
      << T(i) << " " << Z(j) << "\t" << w[i][j] << "\t" 
      << exSln(i, j) << "\t" << fabs(w[i][j] - exSln(i, j)) 
      << std::endl;
    }
  }
  return 0;
}
