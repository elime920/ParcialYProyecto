//telegraph class member-function definitions
#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <limits>
#include "telegraph.h"

#define _USE_MATH_DEFINES

//constructor
telegraph::telegraph(double TInit, double TFin, double ZInit, double ZFin, 
                     unsigned int TPoints, unsigned int ZPoints, double K,
                     std::function<double(unsigned int, unsigned int)> bf, 
                     std::function<double(unsigned int)> icd)
                     
  : T0(TInit), TF(TFin), Z0(ZInit), ZF(ZFin), //extremal points
    NT(TPoints), NZ(ZPoints), //quantity of points on T and Z axes
    k(K), bFunc(bf), initConDer(icd), //k-value of the PDE, and boundary functions
    w(NT+1, std::vector<double>(NZ+1, 0)) //matrix w
{
  std::cout << "Telegrapher's PDE solver started.\n" << std::endl;
  //Use the initialized parameters to set the secondary ones
  setComputationParams();
}

//destructor
telegraph::~telegraph()
{
  std::cout << "\nTelegrapher's PDE solver finished." << std::endl;
}

//set the computation parameters
void telegraph::setComputationParams()
{

  double hT = static_cast<double>((TF - T0) / NT);
  double hZ = static_cast<double>((ZF - Z0) / NZ);

  alpha = (0.5 * k * hT - 1.0) / (0.5 * k * hT + 1.0);
  beta = (2.0 - 2.0 * pow((hT/hZ), 2) - pow(hT, 2))/(0.5 * k * hT + 1.0);
  lambda = pow((hT/hZ), 2) / (0.5 * k * hT + 1.0);
  mu = 1.0 - pow((hT/hZ), 2) - 0.5 * pow(hT, 2);
  nu = hT - 0.5 * k * pow(hT, 2);
  sigma = 0.5 * pow((hT/hZ), 2);
}

//boundary function evaluation
double telegraph::boundary(unsigned int i, unsigned int j)
{
  return bFunc(i, j);
}

//time derivative at T0 function evaluation
double telegraph::timeDerOnT0(unsigned int j)
{
  return initConDer(j);
}

//set the matrix associated to the BVP
void telegraph::setw()
{
  //bounds
  for (unsigned int i = 0; i <= NT; i++)
  {
    for (unsigned int j = 0; j <= NZ; j++)
    {
      w[i][j] = boundary(i, j);
    }
  }
  
  //first time line
  for (unsigned int j = 1; j < NZ; j++)
  {
    w[1][j] = mu * boundary(0,j) + nu * timeDerOnT0(j) + 
             sigma * (boundary(0,j-1) + boundary(0,j+1));
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
}

double telegraph::getSln(unsigned int i, unsigned int j)
{
  return w[i][j];
}

//save results to a file as a matrix
void telegraph::saveAsMatrix(std::string fileName)
{
  std::ifstream readFile; //in case file already exists
  
  readFile.open( fileName.c_str() ); //trying to open the file for input
  
  char userAns;
  if ( !readFile.fail() ) //don't fail: data file exists
  {
    std::cout << "\nA file named '"<< fileName 
              << "' already exists.\n" 
              << "Continue and overwrite? [y/n]: ";
    std::cin >> userAns;
    std::cin.ignore(); //empties buffer
    
    //if user chooses not to overwrite
    if (std::tolower(userAns) == 'n')
    {
      std::cout << "\nFile '" << fileName << "' won't be overwritten,"
                   " process finished." << std::endl;
      exit(1); //finish program execution
    }
  }
  
  readFile.close(); //finish reading process
  
  std::ofstream writeSolution;
  writeSolution.open( fileName.c_str() ); //open the file for input
  
  if ( writeSolution.fail() ) //check successfull opening
  {
    std::cout << "\nFile '" << fileName 
              << "' could not be opened." << std::endl;
    exit(1);
  }
  
  //output file stream format
  writeSolution << std::setiosflags(std::ios::fixed)
                << std::setiosflags(std::ios::showpoint)
                << std::setprecision(4)
                << std::scientific;
                
  //write data to file
  unsigned int l; //unified index
  for (unsigned int i = 0; i <= NT; i++)
  {
    for (unsigned int j = 0; j <= NZ; j++)
    {
      writeSolution << w[i][j] << " ";
    }
    writeSolution << std::endl;
  }
  
  writeSolution.close();
  std::cout << "\nFile " << fileName << " successfully written." << std::endl;
}

//save results to a file as three columns: x, y, w
void telegraph::saveAsColumns(std::string fileName)
{
  std::ifstream readFile; //in case file already exists
  
  readFile.open( fileName.c_str() ); //trying to open the file for input
  
  char userAns;
  if ( !readFile.fail() ) //don't fail: data file exists
  {
    std::cout << "\nA file named '"<< fileName 
              << "' already exists.\n" 
              << "Continue and overwrite? [y/n]: ";
    std::cin >> userAns;
    std::cin.ignore(); //empties buffer
    
    //if user chooses not to overwrite
    if (std::tolower(userAns) == 'n')
    {
      std::cout << "\nFile '" << fileName << "' won't be overwritten,"
                   " process finished." << std::endl;
      exit(1); //finish program execution
    }
  }
  
  readFile.close(); //finish reading process
  
  std::ofstream writeSolution;
  writeSolution.open( fileName.c_str() ); //open the file for input
  
  if ( writeSolution.fail() ) //check successfull opening
  {
    std::cout << "\nFile '" << fileName 
              << "' could not be opened." << std::endl;
    exit(1);
  }
  
  //output file stream format
  writeSolution << std::setiosflags(std::ios::fixed)
                << std::setiosflags(std::ios::showpoint)
                << std::setprecision(4)
                << std::scientific;
                
  //write data to file
  unsigned int l; //unified index
  for (unsigned int i = 0; i <= NT; i++)
  {
    for (unsigned int j = 0; j <= NZ; j++)
    {
      writeSolution << T0 + i * (TF - T0) / NT << " " 
                    << Z0 + j * (ZF - Z0) / NZ << " " 
                    << w[i][j] << std::endl;
    }
  }
  
  writeSolution.close();
  std::cout << "\nFile " << fileName << " successfully written." << std::endl;
}
