#ifndef FUNCTION_HH
#define FUNCTION_HH

class function
{
public:
  function(){};
  virtual ~function()
  {
  }
  virtual double returnvalue() = 0;
};

#endif
