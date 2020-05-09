//Program to test class "poisson2D"
#include <iostream>
#include <iomanip>
#include <string>
#include "poisson2D.h"
#include "exercises/exercise3b.h"

#define printIndex std::left << std::setw(3)
#define printReal std::right << std::setw(10) << std::fixed << std::setprecision(4)
#define printComp std::setw(10) << std::scientific << std::setprecision(3)

int main()
{ 
  //object creation: bvp stands for Boundary Value Problem
  poisson2D bvp(xInit, xFin, yInit, yFin, xPoints, yPoints, 
                sourceBVP, boundBVP);
  
  //choose a method to solve the problem
  //Options: Gauss-Jordan, Jacobi, Gauss-Seidel, SOR
  std::string choice = "SOR";
  
  //solution to the BVP
  bvp.doSolve(choice, 16);
  
  //print solution
  unsigned int l = 0; //unified index to get elements from sln vector
  double exSln = 0.0;
  std::cout << "Solution printing:" << std::endl;
  std::cout << "i   j       xi         yj         w(i,j)     u(i,j)    |u-w|" << std::endl;
  for (unsigned int i = 0; i <= xPoints; i++)
  {
    for (unsigned int j = 0; j <= yPoints; j++)
    {
      //boundary terms
      if ( i == 0 || j == 0 || i == xPoints || j == yPoints)
      {
        std::cout << printIndex << i << " " 
                  << printIndex << j << " "
                  << printReal << x(i) << " " 
                  << printReal << y(j) << " "
                  << printReal << boundBVP(i, j) << " "
                  << printReal << analyticBVP(i, j) << "  | "
                  << " - - " << std::endl;
      }
      
      //inner region terms
      else
      {
        l = i - 1 + (xPoints - 1) * (j - 1); //unified index
        exSln = analyticBVP(i, j); //analytic solution
        std::cout << printIndex << i << " " 
                  << printIndex << j << " "
                  << printReal << x(i) << " " 
                  << printReal << y(j) << " "
                  << printReal << bvp.getSln(l) << " "
                  << printReal << exSln << "  | " 
                  << printComp << fabs(exSln - bvp.getSln(l)) 
                  << std::endl;
      }
    }
  }
  
  //write to file
  bvp.writeToFile("output.dat");

  return(0);
} //end main
