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
telegraph::telegraph(std::vector<double> EndPoints,
                     std::vector<double> Params, 
                     std::vector<std::function<double(double)>> vBC,
                     std::vector<std::function<double(double)>> iBC,
                     unsigned int tPoints, unsigned int zPoints)
                     
  : NT(tPoints), NZ(zPoints), //quantity of points along t and z axes
    bcV(vBC), bcI(iBC), //set boundary functions
    wV(NT+1, std::vector<double>(NZ+1, 0.0)), //matrix w for voltage
    wI(NT+1, std::vector<double>(NZ+1, 0.0)) //matrix w for current
{
  std::cout << "Telegrapher's PDE solver started.\n" << std::endl;
  
  //unpack variables from vectors
  R = Params[0]; L = Params[1]; C = Params[2]; G = Params[3];
  
  //temporary location: endpoints will be adimensionalized
  T0 = EndPoints[0]; TF = EndPoints[1];
  Z0 = EndPoints[2]; ZF = EndPoints[3];
  
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
  //characteristic time and length for the system
  Tc = sqrt((L * C) / (G * R));
  Lc = 1.0 / sqrt(G * R);
  
  //k factor appearing on adimensionalized PDE
  k = sqrt((R * C) / (G * L)) + sqrt((G * L) / (R * C));
  
  //adimensionalize endpoints
  T0 /= Tc; 	TF /= Tc; 	Z0 /= Lc; 	ZF /= Lc;

  //steps along T and Z
  hT = static_cast<double>((TF - T0) / NT);
  hZ = static_cast<double>((ZF - Z0) / NZ);

  //iteration constants
  alpha = (0.5 * k * hT - 1.0) / (0.5 * k * hT + 1.0);
  beta = (2.0 - 2.0 * pow((hT/hZ), 2) - pow(hT, 2)) / 
         (0.5 * k * hT + 1.0);
  lambda = pow((hT/hZ), 2) / (0.5 * k * hT + 1.0);
  mu = 1.0 - pow((hT/hZ), 2) - 0.5 * pow(hT, 2);
  nu = hT - 0.5 * k * pow(hT, 2);
  sigma = 0.5 * pow((hT/hZ), 2);
}

double telegraph::getT(unsigned int i)
{
  return T0 + i * hT;
}

double telegraph::getZ(unsigned int j)
{
  return Z0 + j * hZ;
}

//set the matrix associated to the voltage
void telegraph::setwV()
{
  //use condition of voltage at t0
  for (unsigned int j = 0; j <= NZ; j++)
  {
    wV[0][j] = bcV[0](Lc*getZ(j));
  }
  
  //use condition of time derivative of voltage at t0
  for (unsigned int j = 0; j <= NZ; j++)
  {
    wV[1][j] = mu * bcV[0](Lc*getZ(j)) + nu * Tc*bcV[1](Lc*getZ(j)) + 
               sigma * (bcV[0](Lc*getZ(j-1)) + bcV[0](Lc*getZ(j+1)));
  }
  
  //use spatial boundary conditiones: voltage at z0 and zf
  for (unsigned int i = 0; i <= NT; i++)
  {
    wV[i][0] = bcV[2](Tc*getT(i)); //voltage at z0
    wV[i][NZ] = bcV[3](Tc*getT(i)); //voltage at zf
  }
  
  //inner region
  for (unsigned int i = 1; i < NT; i++)
  {
    for (unsigned int j = 1; j < NZ; j++)
    {
      wV[i+1][j] = alpha * wV[i-1][j] + beta * wV[i][j] + 
                    lambda * (wV[i][j-1] + wV[i][j+1]);
    }
  }
}

//set the matrix associated to the current
void telegraph::setwI()
{
  //use condition of current at t0
  for (unsigned int j = 0; j <= NZ; j++)
  {
    wI[0][j] = bcI[0](Lc*getZ(j));
  }
  
  //use condition of time derivative of current at t0
  for (unsigned int j = 0; j <= NZ; j++)
  {
    wI[1][j] = mu * bcI[0](Lc*getZ(j)) + nu * Tc*bcI[1](Lc*getZ(j)) + 
               sigma * (bcI[0](Lc*getZ(j-1)) + bcI[0](Lc*getZ(j+1)));
  }
  
  //use spatial boundary conditiones: current at z0 and zf
  for (unsigned int i = 0; i <= NT; i++)
  {
    wI[i][0] = bcI[2](Tc*getT(i)); //current at z0
    wI[i][NZ] = bcI[3](Tc*getT(i)); //current at zf
  }
  
  //inner region
  for (unsigned int i = 1; i < NT; i++)
  {
    for (unsigned int j = 1; j < NZ; j++)
    {
      wI[i+1][j] = alpha * wI[i-1][j] + beta * wI[i][j] + 
                    lambda * (wI[i][j-1] + wI[i][j+1]);
    }
  }
}

double telegraph::getwV(unsigned int i, unsigned int j)
{
  return wV[i][j];
}

double telegraph::getwI(unsigned int i, unsigned int j)
{
  return wI[i][j];
}

//save results to a file as a matrix
void telegraph::saveAsMatrix(std::vector<std::vector<double>> &w, std::string fileName)
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
void telegraph::saveAsCols(std::vector<std::vector<double>> &w, std::string fileName)
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
    //std::cin.ignore(); //empties buffer
    
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
  for (unsigned int i = 0; i <= NT; i++)
  {
    for (unsigned int j = 0; j <= NZ; j++)
    {
      writeSolution << Tc*getT(i) << " " 
                    << Lc*getZ(j) << " " 
                    << w[i][j] << std::endl;
    }
  }
  
  writeSolution.close();
  std::cout << "\nFile " << fileName << " successfully written." << std::endl;
}

//save the desired output to a file
void telegraph::saveToFile(std::string vOrI, std::string matOrCol,
                           std::string fileName)
{
  if(vOrI == "V")
  {
    if (matOrCol == "Matrix") saveAsMatrix(wV, fileName);
    else if (matOrCol == "Columns") saveAsCols(wV, fileName);
  }
  
  else if(vOrI == "I")
  {
    if (matOrCol == "Matrix") saveAsMatrix(wI, fileName);
    else if (matOrCol == "Columns") saveAsCols(wI, fileName);
  }
  
}
