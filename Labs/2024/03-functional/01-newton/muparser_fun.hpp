#include <muParser.h>

#include <memory>
#include <string>

class MuparserFun
{
public:
  MuparserFun(const MuparserFun &m)
    : m_parser(m.m_parser)
  {
    m_parser.DefineVar("x", &m_var); //defines the variable we are using
  };

  MuparserFun(const std::string &s)
  {
    try //this and catch are for exception handling, don't care 
      {
        m_parser.DefineVar("x", &m_var);
        m_parser.SetExpr(s);
      }
    catch (mu::Parser::exception_type &e)
      {
        std::cerr << e.GetMsg() << std::endl;
      }
  };

  double
  operator()(const double &x)
  {
    m_var = x;
    double y = m_parser.Eval();

    return y;
  };

private:
  double     m_var;
  mu::Parser m_parser;
};
