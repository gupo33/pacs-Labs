#ifndef DERIVATIVES_HPP
#define DERIVATIVES_HPP

#include <functional>

using func_t = std::function<double(double)>;

class Naive{
    public:
    Naive(const func_t & f, double h, int deg):
    m_f(f),
    m_h(h),
    m_deg(deg){};

    double operator() (double x){
        return f_prime(x,m_f,m_deg);
    }

    private:
    double f_prime(double x, func_t f, int deg){ //performs recursive iterations
        if(deg == 0)
            return f(x);
        if(deg == 1)
            return(f(x+m_h)-f(x))/m_h;
        return (f_prime(x+m_h,f,deg-1) - f_prime(x,f,deg-1))/m_h; 
    }
    const func_t m_f; //function to evaluate
    double m_h; //spacing for finite differences
    int m_deg;
};

//template class for recursive implementation

template<unsigned DEG>
class templateForward{
    public:
    templateForward(const func_t & f, double h):
    m_f(f,h), //constructor for templateForward is called again here
    m_h(h){};

    double operator() (double x){
        return (m_f(x+m_h)-m_f(x))/m_h;
    }

    private:
    using PrevDerivative = templateForward<DEG-1>; //alias for a templateForward object with one less degree 
    const PrevDerivative m_f; //function to evaluate
    double m_h; //spacing for finite differences
};

//we must handle the case when DEG = 0 with a class specialization

template<>
class templateForward<0>{
    public:
    templateForward(const func_t & f, double h):
    m_f(f)
    m_h(h){};

    double operator() (double x){
        return m_f(x);
    }

    private:
    const func_t m_f; //function to evaluate
    double m_h; //spacing for finite differences
};

#endif /* DERIVATIVES_HPP */
