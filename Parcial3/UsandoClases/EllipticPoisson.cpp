//Application of class "solvePDE"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "solvePDE.h"

#define myPrint std::setw(4) << std::setprecision(4)

int main()
{ 
  //object creation
  solvePDE poisson;
  
  //configure b
  poisson.setSysb();
  
  //configure M
  poisson.setSysM();
  
  //solve System
  poisson.GaussLinearSolve();
  
  //print solution
  std::cout << "Solution printing" << std::endl;
  std::cout << "i\tj\txi\tyj\tw(i,j)\tu(i,j)" << std::endl;
  for (unsigned int i = 1; i < poisson.getNx(); i++)
  {
    for (unsigned int j = 1; j < poisson.getNy(); j++)
    {
      unsigned int l = i - 1 + (poisson.getNx() - 1) * (j - 1);
      std::cout << i << "\t" << j << "\t"
                << myPrint << poisson.getX(i) << "\t" 
                << myPrint << poisson.getY(j) << "\t"
                << myPrint << poisson.getSysb(l) << "\t"
                << myPrint << poisson.source(i, j) << std::endl;
    }
  }

  return(0);
} //end main
