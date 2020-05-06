//Application of class "bvp2D"
#include <iostream>
#include <iomanip>
#include "poisson2D.h"
#include "eqSetUpExample1.h"

#define myPrint std::fixed << std::setw(6) << std::setprecision(4)

int main()
{ 
  //object creation: bvp stands for Boundary Value Problem
  poisson2D bvp(xInit, xFin, yInit, yFin, xPoints, yPoints, 
                sourceBVP, boundBVP);
  
  //solution to the BVP
  bvp.doSolve();
  
  //print solution
  std::cout << "Solution printing" << std::endl;
  std::cout << "i\tj\txi\t\tyj\t\tw(i,j)" << std::endl;
  for (unsigned int i = 1; i < xPoints; i++)
  {
    for (unsigned int j = 1; j < yPoints; j++)
    {
      unsigned int l = i - 1 + (xPoints - 1) * (j - 1);
      std::cout << i << "\t" << j << "\t"
                << myPrint << x(i) << "\t\t" 
                << myPrint << y(j) << "\t\t"
                << myPrint << bvp.getb(l) << std::endl;
    }
  }

  return(0);
} //end main
