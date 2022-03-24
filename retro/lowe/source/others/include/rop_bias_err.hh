#ifndef ROP_BIAS_ERR_HH
#define ROP_BIAS_ERR_HH

class rop_bias_err
{
public:
  rop_bias_err(){};
  virtual ~rop_bias_err(){};
  static int xnum;
  static double xverwidth;
  static char* infilehead_onretro;
  static char* infilehead_noretro;

#endif
