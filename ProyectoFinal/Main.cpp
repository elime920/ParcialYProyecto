//Program to test class "poisson2D"
#include <iostream>
#include <iomanip>
#include <string>
#include "Telegrapher.h"
#include "example.h"

#define printIndex std::left << std::setw(3)
#define printReal std::right << std::setw(10) << std::fixed << std::setprecision(4)
#define printComp std::setw(10) << std::scientific << std::setprecision(3)

void printOutput(Telegrapher); //function prototype to print program output

int main()
{ 
  //object creation: bvp stands for Boundary Value Problem
  Telegrapher bvp(TInit, TFin, ZInit, ZFin, kcons, stepZ, stepT,
		  TPoints, ZPoints,
		  sourceBVP, boundBVP);
  
  return(0);
} //end main

//Function to print to terminal the output of the execution
void printOutput(Telegrapher bvp)
{
  
  std::cout << "Solution printing:" << std::endl;
  std::cout << "i   j       xi         yj         w(i,j)     u(i,j)    |u-w|" << std::endl;
  for (unsigned int i = 0; i <= TPoints; i++)
  {
    for (unsigned int j = 0; j <= ZPoints; j++)
    {
      //boundary terms
        std::cout << printIndex << i << " " 
                  << printIndex << j << " "
                  << printReal << Z(i) << " " 
                  << printReal << T(j) << " "
                  << printReal << bvp.getSln(i, j)  << " "
                  << printReal << analyticBVP(i, j) << "  | "
                  << " - - " << std::endl;
    
    }
  }
}
