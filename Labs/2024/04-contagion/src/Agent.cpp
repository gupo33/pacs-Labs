#include "Agent.hpp"

Agent::Agent( size_t seed, State state, const Parameters &params):
    m_params(params),
    m_engine(seed),
    m_state(state)
{
    //generate random position of the agent

    std::uniform_real_distribution<double> read_dist(0.0,1.0);

    m_x = read_dist(m_engine) * m_params.domain.domain_size();
    m_y = read_dist(m_engine) * m_params.domain.domain_size();
}

void Agent::move(){
    for(int i = 0; i<1000;++i){
        //generate a movement
        //check if m_x,m_y are inside the domain
        //if yes, break
    }
}

std::pair<double,double> Agent::generate_random_step(){

}