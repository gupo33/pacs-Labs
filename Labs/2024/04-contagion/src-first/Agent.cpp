#include "Agent.hpp"
#include <cmath>
#include <numbers>


Agent::Agent( size_t seed, State initial_state, 
                      const Parameters &params):
    m_params(params),
    m_engine(seed),
    m_state(initial_state){

        // generate random initial positions
        std::uniform_real_distribution<double> real_dist(0.0,1.0);

        m_x = real_dist(m_engine) * m_params.domain.domain_size;
        m_y = real_dist(m_engine) * m_params.domain.domain_size;

    }

void Agent::move(){
    // we try to move until the next step is inside the domain
    for (int i=0; i < 1000; ++i){
        // TODO
        // try to move. If not inside the domain, generate a new move

        const auto [dx,dy] = generate_random_step();

        double newx = m_x + dx;
        double newy = m_y + dy;

        bool isInside = (newx >= 0 && newx <= 1.) && (newy >= 0 && newy <= 1.);

        if(isInside){
            m_x = newx;
            m_y = newy;
            break;
        }
    }
}

std::pair<double, double> Agent::generate_random_step(){
    // TODO: 
    // generate the random angle and step size

    std::uniform_real_distribution<double> angle_size(0., 2.*std::numbers::pi);

    const auto alpha = angle_size(m_engine);

    std::pair<double,double> step = std::make_pair(m_params.agent.dr * std::cos(alpha),
                                                   m_params.agent.dr * std::sin(alpha));

    return step;
}
