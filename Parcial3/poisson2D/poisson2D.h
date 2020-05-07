//poisson2D class declaration. Member functions defined in poisson2D.cpp
#include <vector>
#include <functional>

#ifndef POISSON2D_H
#define POISSON2D_H

//class poisson2D: two-dim. Poisson finite-difference implementation
class poisson2D
{
  public:
    //constructor
    poisson2D(double, double, double, double, 
              unsigned int, unsigned int, 
              std::function<double(unsigned int, unsigned int)>,
              std::function<double(unsigned int, unsigned int)>);
     
    //destructor
    ~poisson2D();
    
    //set parameters appearing in the difference equation
    void setComputationParams();
    
    //auxiliary function to assign the source and boundary functions
    double evalOnIndices(unsigned int, unsigned int, 
                         std::function<double(unsigned int, unsigned int)>);
    
    //source function data type
    std::function<double(unsigned int, unsigned int)> sFunc;
    
    //boundary function data type
    std::function<double(unsigned int, unsigned int)> bFunc;
    
    //source function prototype
    double source(unsigned int, unsigned int);
    
    //boundary function prototype
    double boundary(unsigned int, unsigned int);
  
    void setM(); //create the matrix associated to the BVP
  
    void setb(); //set inhomogeneity vector b
  
    void GaussLinearSolve(); //solve linear eq. with Gauss-Jordan elim.
  
    void doSolve(); //execute functions involved to solve the equation
    
    double getb(unsigned int); //output the result vector b

  private:
    //problem parameters and constants
    unsigned short int Nx, Ny, dim; //points on x, on y, and inner grid
    double x0, xN; //endpoints on x
    double y0, yN; //endpoints on y
    double lambda, mu; //difference equation parameters
    std::vector<double> b; //bound and source terms
    std::vector<std::vector<double>> M; //solver matrix

}; //end class poisson2D

#endif
