#ifndef AGENT_HPP
#define AGENT_HPP

#include "Parameters.hpp"
#include <random>

enum class State{
  Susceptible,
  Infected,
  Recovered
};

class Agent
{
public:
  Agent(size_t, State, const Parameters &);

  void move();

  double x()         const {return m_x;};
  double y()         const {return m_y;};
  State state()      const {return m_state;};
  bool susceptible() const {return m_state == State::Susceptible;};
  bool infected()    const {return m_state == State::Infected;};
  bool recovered()   const {return m_state == State::Recovered;};

protected:
  const Parameters & m_params;

  std::pair<double,double> Agent::generate_random_step();

  double m_x;
  double m_y;
  State m_state;

  std::default_random_engine m_engine; //handles the generation of the random position of the agents


};

#endif /* AGENT_HPP */
