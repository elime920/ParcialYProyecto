# Telegraph PDE solver, subject to Cauchy - Dirichlet boundary conditions

The program written on the files contained here solves the Boundary Value Problem:

![equation](<a href="https://www.codecogs.com/eqnedit.php?latex=\left[&space;-\partial_{_T}^2&space;&plus;&space;\partial_{_Z}^2&space;-&space;k&space;\partial_{_T}&space;-&space;1&space;\right]&space;\&space;F(T,&space;Z)&space;=&space;0" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\left[&space;-\partial_{_T}^2&space;&plus;&space;\partial_{_Z}^2&space;-&space;k&space;\partial_{_T}&space;-&space;1&space;\right]&space;\&space;F(T,&space;Z)&space;=&space;0" title="\left[ -\partial_{_T}^2 + \partial_{_Z}^2 - k \partial_{_T} - 1 \right] \ F(T, Z) = 0" /></a>)


![equation](<a href="https://www.codecogs.com/eqnedit.php?latex=T&space;\in&space;[T_0,&space;T_F],&space;\qquad&space;Z&space;\in&space;[Z_0,&space;Z_F]" target="_blank"><img src="https://latex.codecogs.com/gif.latex?T&space;\in&space;[T_0,&space;T_F],&space;\qquad&space;Z&space;\in&space;[Z_0,&space;Z_F]" title="T \in [T_0, T_F], \qquad Z \in [Z_0, Z_F]" /></a>)


subject to:

![equation](<a href="https://www.codecogs.com/eqnedit.php?latex=F(T_0,&space;Z)&space;=&space;\tilde{a}(Z),&space;\qquad&space;\partial_{_T}f(T_0,&space;Z)&space;=&space;\tilde{b}(Z)," target="_blank"><img src="https://latex.codecogs.com/gif.latex?F(T_0,&space;Z)&space;=&space;\tilde{a}(Z),&space;\qquad&space;\partial_{_T}f(T_0,&space;Z)&space;=&space;\tilde{b}(Z)," title="F(T_0, Z) = \tilde{a}(Z), \qquad \partial_{_T}f(T_0, Z) = \tilde{b}(Z)," /></a>)

and

![equation](<a href="https://www.codecogs.com/eqnedit.php?latex=F(T,&space;Z_0)&space;=&space;\tilde{c}(T),&space;\qquad&space;f(T,&space;Z_F)&space;=&space;\tilde{d}(T)." target="_blank"><img src="https://latex.codecogs.com/gif.latex?F(T,&space;Z_0)&space;=&space;\tilde{c}(T),&space;\qquad&space;f(T,&space;Z_F)&space;=&space;\tilde{d}(T)." title="F(T, Z_0) = \tilde{c}(T), \qquad f(T, Z_F) = \tilde{d}(T)." /></a>)


# Files:

1. *telegraph.h*: class definition header file

2. *telegraph.cpp*: class *telegraph* member-functions definitions

3. *solveTelegraph.cpp*: main implementation. Depending on which problem is to be solved, include one of the problem headers.

4. *plotOutput.py*: python code to plot the output in animation for several examples.

5. *Plot2D.py*: python code to plot the output in graphics for several examples.

6. *Presentation.pdf*: slides shown when the project was unveiled.

7. *Article.pdf*: written text containing the theoretical approach.


# Folders:

- *examples*: contains header files to be included inside the main program, for them to be solved.


# Compilation:

Te following one-line code executes all the commands required to show the output as a GIF animation:


*g++ solveTelegraph.cpp telegraph.cpp -o solveTelegraph.exe && ./solveTelegraph.exe && python3 plotOutput.py Plot2D.py && eog animation.gif*

# TO-DO:

1. Implement a more stable method.
