//Program to test class "poisson2D"
#include <iostream>
#include <iomanip>
#include <string>
#include "poisson2D.h"
#include "eqSetUpExercise8.h"
#include <fstream>
#define myPrint std::fixed << std::setw(5) << std::setprecision(3)

int main()
{
  int l;  
  //object creation: bvp stands for Boundary Value Problem
  poisson2D bvp(xInit, xFin, yInit, yFin, xPoints, yPoints, 
                sourceBVP, boundBVP);
  
  //choose a method to solve the problem
  //Options: Gauss-Jordan, Jacobi, Gauss-Seidel, SOR
  std::string choice = "SOR";
  
  //solution to the BVP
  bvp.doSolve(choice, 32);
  
  //print solution
  std::cout << "Hello, if you want to see the solution on the screen please enter 1,"
	    << "otherwise if you want it to be saved in a file, please enter 0."
	    << "Note that if you want to export the data 2 files will come out."
	    << "The first contains the matrix of approximations and "
	    << "the second contains the values of x, y and their respective approximation." << std::endl;
  std::cin >> l;

  if(l == 1)
    {
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
			    << myPrint << analyticBVP(i, j)
			    << std::endl;
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
    }
  else
    {
      std::ofstream write;
      write.open( "Completedata.dat" ); //open the file for input
  
  //check success when accessing the file
      if ( write.fail() )
	{
	  std::cout << "File could not be opened." << std::endl;
	  exit(1);
	}
      for (unsigned int i = 0; i <= xPoints; i++)
        {
          for (unsigned int j = 0; j <= yPoints; j++)
            {
              //boundary terms                                         
              if ( i == 0 || j == 0 || i == xPoints || j == yPoints)
                {
                  write << x(i) << "\t"
					<< myPrint << y(j) << "\t\t"
					<< myPrint << boundBVP(i, j)
					<< std::endl;
		}
              //inner region terms                                     
              else
                {
                  unsigned int l = i - 1 + (xPoints - 1) * (j - 1);
                  write << x(i) << "\t"
					<< myPrint << y(j) << "\t\t"
					<< myPrint << bvp.getb(l)
					<< std::endl;
		}
	    }
	}
  bvp.writeToFile("myOutput2.dat");
  write.close();
  std::cout << "All data has been successfully saved." << std::endl;
    }


  return(0);
} //end main
