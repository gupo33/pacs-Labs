#include "NewtonSolver.hpp"
#include "GetPot" 

//this is the main, but we want to populate the variables through getpot

// function f 
double fun(const double &x)
{
  return x*x*x + 5 * x + 3;
};

// derivative of f
double dfun(const double &x)
{
  return 3 *x*x + 5;
};

int main(int argc, char **argv) //argc and argv need to be present
{
  GetPot command_line(argc, argv); //parses the arguments

  const std::string filename = command_line.follow("dataGetPot", 2, "-f", "--file");
  //selects a file name where to look for stuff

  GetPot datafile(filename.c_str());

  const unsigned int max_it = datafile("nmax_it", 100);
  const double tol_res = datafile("tol_fun", 1e-8);
  const double tol_x = datafile("tol_x", 1e-8);

  // initialize solver
  NewtonSolver solver(fun, dfun, max_it, tol_res, tol_x);

  // run Newton solver with initial condition 0.0 
  solver.solve(0.0);

  // output the results
  std::cout << "x =    " << solver.get_result() << std::endl;
  std::cout << "r =    " << solver.get_residual() << std::endl;
  std::cout << "iter = " << solver.get_iter() << std::endl;

  return 0;
}
