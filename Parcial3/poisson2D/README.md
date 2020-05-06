#Poisson PDE solver, subject to boundary conditions and source term

The program written on the files contained here solves the Boundary Value Problem:

( d^2/dx^2 + d^2/dx^2 ) u(x, y) = f(x, y), 
(x, y) in S
u(x, y) = g(x, y) on the boundary of S

#Files:

1. *poisson2D.h*: class definition header file

2. *poisson2D.cpp*: class *poisson2D* member-functions definitions

3. *eqSetUpExample1.h*, *eqSetUpExample2.h*: header files setting up the details for particular examples given in Burden.

4. *eqSolve.cpp*: main implementation. Depending on which problem is to be solved, include one of the two header files mentioned above.

#Compilation:

*g++ eqSolve.cpp poisson2D.cpp -o eqSolve.exe*

#TO-DO:

1. Add another solver for the system of linear equations (using GSL).

2. Format the output to a file, in such a way that a matrix with elements well placed can be latter imported as data input on another program.

3. Plot the output (color map the matrix; plotutils, python, etc.)
