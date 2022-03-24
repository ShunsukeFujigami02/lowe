// c++ STL
#include <iostream>

// self-introduced library
#include "GoodnessParameters.hh"


GoodnessParameters::GoodnessParameters():goodnessfunctiontype(GoodnessFunctionType::normal),onegoodnessfunctiontype(OneGoodnessFunctionType::no_retro),sigma(5.),reflectivity(0.3)
{
}

GoodnessParameters::~GoodnessParameters()
{
}

void GoodnessParameters::Print()
{
  if(goodnessfunctiontype == GoodnessFunctionType::normal)
    {
      std::cout << "GoodnessFunctionType = normal" << std::endl;
    }
  if(onegoodnessfunctiontype == OneGoodnessFunctionType::no_retro)
    {
      std::cout << "OneGoodnessFunctionType = no_retro" << std::endl;
    }
  else if(onegoodnessfunctiontype == OneGoodnessFunctionType::sum)
    {
      std::cout << "OneGoodnessFunctionType = sum" << std::endl;
    }
  else if(onegoodnessfunctiontype == OneGoodnessFunctionType::compare)
    {
      std::cout << "OneGoodnessFunctionType = compare" << std::endl;
    }
  else if(onegoodnessfunctiontype == OneGoodnessFunctionType::no_retro_digital)
    {
      std::cout << "OneGoodnessFunctionType = no_retro_digital" << std::endl;
    }
  else if(onegoodnessfunctiontype == OneGoodnessFunctionType::compare_digital)
    {
      std::cout << "OneGoodnessFunctionType = compare_digital" << std::endl;
    }
  else if(onegoodnessfunctiontype == OneGoodnessFunctionType::compare_nodigital)
    {
      std::cout << "OneGoodnessFunctionType = compare_nodigital" << std::endl;
    }
  else if(onegoodnessfunctiontype == OneGoodnessFunctionType::compare_nodigital_ver3)
    {
      std::cout << "OneGoodnessFunctionType = compare_nodigital_ver3" << std::endl;
    }
  else
    {
      std::cout << "invalid onegoodnessfunctiontype " << onegoodnessfunctiontype << std::endl;
    }
  
  std::cout << "sigma = " << sigma << "(ns)" << std::endl;
  range->Printrange();
}

