#include "NewtonSolver.hpp"
#include "muparser_fun.hpp" //wrapper that helps us using muparser
#include "json.hpp" //needed to work with json files

#include <fstream> //allows us to open files
#include <string> //contains the string datatype

using json = nlohmann::json; //namespace

int main(int argc, char **argv)
{

  std::ifstream f("data.json"); //opens the json file
  json data = json::parse(f); //json object used for parsing

  //we want to define f and df with muparser
  //and also pass the parameters through the json file

  const unsigned max_it = data.value("max_it",10);
  const double tol_res = data.value("tol_res",1e-8);
  const double tol_x = data.value("tol_x",1e-8);

  std::string funString = data.value("fun","");
  std::string dfunString = data.value("dfun","");

  //define the functions from the strings

  MuparserFun fun(funString);
  MuparserFun dfun(dfunString);

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
