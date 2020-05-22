//telegraph class declaration. Member functions in telegraph.cpp
#include <vector>
#include <string>
#include <functional>

#ifndef TELEGRAPH_H
#define TELEGRAPH_H

//class telegraph
class telegraph
{
  public:
    //constructor
    telegraph(std::vector<double>, //endpoints
              std::vector<double>, //system parameters
              std::vector<std::function<double(double)>>, //b.c. for v
              std::vector<std::function<double(double)>>, //b.c. for i
              unsigned int, unsigned int); //# of points along t and z
     
    //destructor
    ~telegraph();

    //V boundary function data type
    std::vector<std::function<double(double)>> bcV;
    //I boundary function data type
    std::vector<std::function<double(double)>> bcI;

    //set parameters appearing in the difference equation
    void setComputationParams();

    //accesors for adimensional variables T and Z
    double getT(unsigned int);
    double getZ(unsigned int);

    void setwV(); //create the matrix associated to the voltage
    void setwI(); //create the matrix associated to the current
    
    double getwV(unsigned int, unsigned int); //output the voltage
    double getwI(unsigned int, unsigned int); //output the voltage
    
    void saveAsMatrix(std::vector<std::vector<double>> &, std::string);
    void saveAsCols(std::vector<std::vector<double>> &, std::string);
    
    //chose which data is to be saved and the method to save it
    void saveToFile(std::string, std::string, std::string);
    
    double Jt, Jz; //jacobian transformation components (diag., const.)

  private:
    double R, L, C, G; //system parameters
    unsigned short int NT, NZ; //points on T and Z axes
    double hT, hZ; //steps on T and Z
    double T0, TF; //endpoints on T
    double Z0, ZF; //endpoints on Z
    double k, alpha, beta, lambda, mu, nu, sigma; //computation const.
    std::vector<std::vector<double>> wV, wI; //matrices for V and I

}; //end class telegraph

#endif
