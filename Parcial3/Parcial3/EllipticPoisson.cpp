//Applitcation of class "solvePDE"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "solvePDE.h"

#define myPrint std::setw(5) << std::setprecision(3)

int main()
{ 
  //object creation
  solvePDE poisson;
  
  //print initial values
  std::cout << "Test printing of initial values" << std::endl;
  std::cout << "i\tj\txi\tyi\tf(xi,yi)" << std::endl;
  for (unsigned int i = 1; i < poisson.getNx(); i++)
  {
    for (unsigned int j = 1; j < poisson.getNy(); j++)
    {
      std::cout << i << "\t" << j << "\t"
                << myPrint << poisson.getX(i) << "\t" 
                << myPrint << poisson.getY(j) << "\t"
                << myPrint << poisson.source(i, j) << std::endl;
    }
  }
  
  std::cout << "\nSystem matrix setup and printing" << std::endl;
  //configure M
  poisson.setSysM();
  
  //print M
  poisson.printSysM();
  
  return(0);
} //end main
