#ifndef FPTOFERROR_HH
#define FPTOFERROR_HH

class fptoferror
{
public:
  fptoferror()
  {
  }
  virtual ~fptoferror()
  {
  }
  virtual double p(double toferror) = 0;
};

#endif
