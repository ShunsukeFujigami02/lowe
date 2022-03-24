#ifndef COMMAND_HH
#define COMMAND_HH

class command
{
public:
  command()
  {
  }
  virtual ~command()
  {
  }
  virtual void execute() = 0;
};

#endif
