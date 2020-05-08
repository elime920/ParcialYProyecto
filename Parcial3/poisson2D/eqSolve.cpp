//Program to test class "poisson2D"
#include <iostream>
#include <iomanip>
#include <string>
#include "poisson2D.h"
#include "eqSetUpExercise8.h"

#define myPrint std::fixed << std::setw(5) << std::setprecision(3)

int main()
{ 
  //object creation: bvp stands for Boundary Value Problem
  poisson2D bvp(xInit, xFin, yInit, yFin, xPoints, yPoints, 
                sourceBVP, boundBVP);
  
  //choose a method to solve the problem
  //Options: Gauss-Jordan, Jacobi, Gauss-Seidel, SOR
  std::string choice = "SOR";
  
  //solution to the BVP
  bvp.doSolve(choice, 32);
  
  //print solution
  std::cout << "Solution printing:" << std::endl;
  std::cout << "i\tj\txi\t\tyj\t\tw(i,j)\t\tu(i,j)" << std::endl;
  for (unsigned int i = 0; i <= xPoints; i++)
  {
    for (unsigned int j = 0; j <= yPoints; j++)
    {
      //boundary terms
      if ( i == 0 || j == 0 || i == xPoints || j == yPoints)
      {
        std::cout << i << "\t" << j << "\t"
                  << myPrint << x(i) << "\t\t" 
                  << myPrint << y(j) << "\t\t"
                  << myPrint << boundBVP(i, j) << "\t\t"
                  << myPrint << analyticBVP(i, j) << std::endl;
      }
      
      //inner region terms
      else
      {
      unsigned int l = i - 1 + (xPoints - 1) * (j - 1);
      std::cout << i << "\t" << j << "\t"
                << myPrint << x(i) << "\t\t" 
                << myPrint << y(j) << "\t\t"
                << myPrint << bvp.getb(l) << "\t\t"
                << myPrint << analyticBVP(i, j) << std::endl;
      }
    }
  }
  
  //write to file. Give correct name to each run, instead of "myOutput.dat"
  bvp.writeToFile("myOutput.dat");

  return(0);
} //end main
