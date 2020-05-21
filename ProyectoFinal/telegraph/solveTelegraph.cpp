//Program to test class "telegraph"
#include <iostream>
#include <iomanip>
#include "telegraph.h"
#include "examples/example1.h"

#define printIndex std::left << std::setw(3)
#define printReal std::right << std::setw(10) << std::fixed << std::setprecision(4)
#define printComp std::setw(10) << std::scientific << std::setprecision(3)

int main()
{
  //object creation: bvp stands for Boundary Value Problem
  telegraph bvp(T0, TF, Z0, ZF, NT, NZ, k,
                boundFunc, initDerFunc);

  //solve problem
  bvp.setw();
    
  //print solution
  double exSol = 0.0;
  std::cout << "Solution printing:" << std::endl;
  std::cout << "i   j       xi         yj         "
               "w(i,j)     u(i,j)    |u-w|" << std::endl;
  for (unsigned int i = 0; i <= NT; i++)
  {
    for (unsigned int j = 0; j <= NZ; j++)
    {
      exSol = exSln(i, j); //analytic solution
      std::cout << printIndex << i << " " 
                << printIndex << j << " "
                << printReal << T(i) << " " 
                << printReal << Z(j) << " "
                << printReal << bvp.getSln(i, j) << " "
                << printReal << exSol << "  | " 
                << printComp << fabs(exSol - bvp.getSln(i, j))
                << std::endl;
    }
  } //end printing
  
  //write to files
  bvp.saveAsMatrix("outputMat.dat"); //save as matrix data
  bvp.saveAsColumns("outputCols.dat"); //save as column data

  return(0);
} //end main
