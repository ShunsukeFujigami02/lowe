// c++ STL
#include <iostream>

// Self introduced library
#include "C4Number.hh"

ClassImp(C4Number)

C4Number::C4Number(int x, int y,int z,int t)
  :x(x),y(y),z(z),t(t)
{
  if((x < 1)|| (y < 1) || (z < 1) || (t < 1)){  // error handling
    std::cout << "ilegal number is inputed!" << std::endl;
    throw "C4Number::C4Number(int x,int y,int z,int t)";
  }
}
int C4Number::GetX() const
{
  return x;
}

int C4Number::GetY() const
{
  return y;
}

int C4Number::GetZ() const
{
  return z;
}

int C4Number::GetT() const
{
  return t;
}

void C4Number::SetX(int x_set)
{
  if(x_set < 1){ // error handling
    std::cout << "ilegal number is inputed!" << std::endl;
    throw "C4Number::SetX(int x_set)";
  }
  else{
    x = x_set;
  }
}

void C4Number::SetY(int y_set)
{
  if(y_set < 1){ // error handling
    std::cout << "ilegal number is inputed!" << std::endl;
    throw "C4Number::SetY(int y_set)";
  }
  else{
    y = y_set;
  }
}

void C4Number::SetZ(int z_set)
{
  if(z_set < 1){ // error handling
    std::cout << "ilegal number is inputed!" << std::endl;
    throw "C4Number::SetZ(int z_set)";
  }
  else{
    z = z_set;
  }
}

void C4Number::SetT(int t_set)
{
  if(t_set < 1){ // error handling
    std::cout << "ilegal number is inputed!" << std::endl;
    throw "C4Number::SetT(int t_set)";
  }
  else{
    t = t_set;
  }
}

C4Number C4Number::operator + (C4Number const & right) const
{
  C4Number c4number(x + right.x, y + right.y , z + right.z ,t + right.t);
  return c4number;
}

C4Number C4Number::operator - (C4Number const & right) const
{
  C4Number c4number(x - right.x, y - right.y , z - right.z ,t + right.t);
  return c4number;
}

bool C4Number::operator == (C4Number const & right) const
{
  if( (x == right.x) && (y == right.y) && (z == right.z) && (t == right.t))
    return true;
  else 
    return false;
}

bool C4Number::operator != (C4Number const & right) const
{
  return !((*this) == right);
}

int C4Number::operator * (C4Number const & right) const
{
  return (x * right.x + y * right.y + z * right.z);
}

void C4Number::Printnumber()
{
  std::cout << "(x,y,z,t) = (" << x << "," << y << "," << z << "," << t << ")" << std::endl;
}
