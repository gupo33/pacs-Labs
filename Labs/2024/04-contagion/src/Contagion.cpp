#include "Contagion.hpp"
#include <random>
#include <iostream>

#include <sstream> //for stringstreams
#include <iomanip> //for setw

#include <fstream> //to open files

Contagion::Contagion(const std::string &filename)
  : m_params(filename),
    m_time(m_params.contagion.n_timesteps + 1), //initialize current time of the simulation
    m_n_susceptible(m_params.contagion.n_timesteps + 1 ),
    m_n_infected(m_params.contagion.n_timesteps + 1 ),
    m_n_recovered(m_params.contagion.n_timesteps + 1 )
{
  //initialize for random position generator

  std::default_random_engine(m_params.seed);

}

void
Contagion::run() {
  //first time step

  m_time[0] = 0.0;
  m_n_susceptible[0] = m_params.contagion.n_agents - m_params.contagion.n_init_infected;
  m_n_infected[0]    = m_params.contagion.n_init_infected;
  m_n_recovered[0]   = 0;

  for( unsigned int step = 1; step < m_params.contagion.n_timesteps; ++step ){
    m_time[step] = static_cast<double>(step) / m_params.contagion.n_timesteps_per_day; //this way, we don't have an implicit conversion

    //update the agents

    //...

    if(m_params.dump && (step % m_params.dump == 0)){
      //define the name of the output file

      std::ostringstream oss;

      oss << "snapshot." << std::setfill('0') << std::setw(5) << step << ".csv"; //pads the output with 5 zeroes

      output_position(oss.str()); //new method that outputs the position
    }
  }
}

void
Contagion::output_results() const {
  //open a file

  std::ofstream file{"output.csv", std::ofstream::out}; //out is the position where to print inside the file

  //print the header of the file, containing: time, n_susceptible, n_infected, n_recovered

  file << "time,n_susceptible,n_infected,n_recovered\n";

  //dump the vector containing the SIR information

  for(size_t i = 0; i < m_time.size(); ++i){
    file << m_time[i] << "," << m_n_susceptible[i] 
                      << "," << m_n_infected[i] 
                      << "," << m_n_recovered[i] << "\n";
  }

  //close the file

  file.close();
  
}

void
Contagion::output_position(const std::string & filename) const {

  //open file

  std::ofstream file(filename, std::ofstream::out);

  //print file header

  file << "x,y,state\n";

  //print agent position

  for(const auto & a : m_agents){
    file  << a.x() << ','
          << a.y() << ','
          << static_cast<int>(a.state()) << "\n"; // cast needed to properly visualize result inside file
  }

  //close the file
}
