//poisson2D class declaration. Member functions defined in poisson2D.cpp
#include <vector>
#include <functional>

#ifndef TELEGRAPHER_H
#define TELEGRAPHER_H



class Telegrapher
{
 public:
  Telegrapher(double, double, double, double, double,
	      double, double, unsigned int, unsigned int,
	      std::function<double(unsigned int, unsigned int)>,
	      std::function<double(unsigned int, unsigned int)>);

  //destructor
  ~Telegrapher();

    //set parameters appearing in the difference equation
  void setComputationParams();

    //auxiliary function to assign the source and boundary functions
  double evalOnIndices(unsigned int, unsigned int,
		       std::function<double(unsigned int, unsigned int)>);

    //source function data type
  std::function<double(unsigned int, unsigned int)> sFunc;
    //boundary function data t
  std::function<double(unsigned int, unsigned int)> bFunc;
  //source function prototype
  double source(unsigned int, unsigned int);
    //boundary function prototype
  double boundary(unsigned int, unsigned int);
  void setW(); //create the matrix associated to the BVP
  double getSln(unsigned int, unsigned int);
 private:
  unsigned short int NT, NZ, dim;
  double T0, T;
  double Z0, ZF;
  double lambda, alpha, beta; //difference equation parameters
  double mu, sigma, nu, k;
  double hT, hZ;
  std::vector<std::vector<double>> W;

};

#endif
