#include "GetPot"

#include <iostream>
#include <string>

int main(int argc, char **argv) {
  GetPot            command_line(argc, argv);
  const std::string filename = command_line.follow("data", 2, "-f", "--file");

  GetPot            datafile(filename.c_str());
  const std::string section = "integration/domain/";
  //this is needed if the file we are dealing with has a certain structure
  //getpot will look for this "path" inside the parameter file to search for what it needs

  const double a = datafile((section + "a").data(), 0.0);
  const double b = datafile((section + "b").data(), 0.0);

  std::cout << "Integration range: \n" << 
      "a = " << a << "\n" << 
      "b = " << b << std::endl;


  return 0;
}
