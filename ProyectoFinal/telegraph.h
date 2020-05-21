//telegraph class declaration. Member functions defined in telegraph.cpp
#include <vector>
#include <functional>

#ifndef TELEGRAPH_H
#define TELEGRAPH_H

//class telegraph
class telegraph
{
  public:
    //constructor
    telegraph(double, double, double, double, 
              unsigned int, unsigned int, double,
              std::function<double(unsigned int, unsigned int)>,
              std::function<double(unsigned int)>);
     
    //destructor
    ~telegraph();
    
    //set parameters appearing in the difference equation
    void setComputationParams();

    //boundary function data type
    std::function<double(unsigned int, unsigned int)> bFunc;
    //time derivative on T0 function data type
    std::function<double(unsigned int)> initConDer;
        
    //boundary function prototype
    double boundary(unsigned int, unsigned int);
    //time derivative on T0 function prototype
    double timeDerOnT0(unsigned int);
  
    void setw(); //create the matrix associated to the BVP
    
    double getSln(unsigned int, unsigned int); //output the solution
    
    void saveAsMatrix(std::string); //save output to file as matrix
    void saveAsColumns(std::string); //save output to file as data columns

  private:
    unsigned short int NT, NZ; //points on x, on y, and inner grid
    double T0, TF; //endpoints on x
    double Z0, ZF; //endpoints on y
    double k, alpha, beta, lambda, mu, nu, sigma; //difference equation parameters
    std::vector<std::vector<double>> w; //solver matrix

}; //end class telegraph

#endif
