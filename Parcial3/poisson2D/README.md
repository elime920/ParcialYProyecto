# Poisson PDE solver, subject to Dirichlet boundary conditions

The program written on the files contained here solves the Boundary Value Problem:

( d^2/dx^2 + d^2/dx^2 ) u(x, y) = f(x, y), 

(x, y) in S, 

u(x, y) = g(x, y) on the boundary of S.


# Files:

1. *poisson2D.h*: class definition header file

2. *poisson2D.cpp*: class *poisson2D* member-functions definitions

3. *eqSolve.cpp*: main implementation. Depending on which problem is to be solved, include one of the problem headers.

4. *Parcial3.py*: python code to plot the output for several examples.


# Folders:

- examples: contains two header files (*example1.h* and *example2.h*) to be included inside the main program, for them to be solved.

- exercises: contains seven header files (*exercise1.h*, *exercise2.h*, *exercise3a.h*, *exercise3b.h*, *exercise3c.h*, *exercise3d.h*, *exercise8.h*) to be included inside the main program, for them to be solved.


# Compilation:

*g++ eqSolve.cpp poisson2D.cpp -o eqSolve.exe*

# TO-DO:

--
