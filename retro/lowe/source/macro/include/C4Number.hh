#ifndef C4NUMBER_HH
#define C4NUMBER_HH

#include <TObject.h>

class C4Number : public TObject
{
  // 4-dimension integer class. it is mainly used to represent the number of the grid search.
public:
  C4Number(int x,int y,int z,int t);
  C4Number()
    :x(1),y(1),z(1),t(1)
  {}
  virtual ~C4Number(){}
  int GetX() const;
  int GetY() const;
  int GetZ() const;
  int GetT() const;
  void SetX(int x_set);
  void SetY(int y_set);
  void SetZ(int z_set);
  void SetT(int t_set);
  void Printnumber();
  C4Number operator + (C4Number const & right) const;
  C4Number operator - (C4Number const & right) const;
  bool operator == (C4Number const & right) const;
  bool operator != (C4Number const & right) const;
  int operator * (C4Number const & right) const;
private:
  int x;
  int y;
  int z;
  int t;
public:
  ClassDef(C4Number,1)
};

#endif
