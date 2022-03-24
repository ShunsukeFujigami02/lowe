#ifndef GOODNESSRUN_HH
#define GOODNESSRUN_HH
// self-introduced library
#
class GoodnessRun
{
public:
  GoodnessRun(){}
  virtual ~GoodnessRun(){}
  int GetnumberOfEvent()
  {
    return numberOfEvent;
  }
  void SetnumberOfEvent(int nofevent)
  {
    numberOfEvent = nofevent;
  }
  
private:
  int numberOfEvent;
};

#endif
