// ROOT library
#include <TLorentzVector.h>
#include <TVector3.h>

// self-introduced library
#include "goodness_data.hh"

ClassImp(goodness_data)

double goodness_data::GetT() const
{
  return vector.T();
}

double goodness_data::GetX() const
{
  return vector.X();
}

double goodness_data::GetY() const
{
  return vector.Y();
}

double goodness_data::GetZ() const
{
  return vector.Z();
}

TVector3 goodness_data::GetPosition() const
{
  return vector.Vect();
}

TLorentzVector goodness_data::Get4Vector() const
{
  return vector;
}

double goodness_data::Getgoodness() const
{
  return goodness;
}

void goodness_data::Set4Vector(TLorentzVector vector_input)
{
  vector = vector_input;
}

void goodness_data::Setgoodness(double goodness_input)
{
  goodness = goodness_input;
}

void goodness_data::Setdata(goodness_data data)
{
  vector = data.Get4Vector();
  goodness = data.Getgoodness();
}
