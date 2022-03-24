#ifndef LIKELIHOODTOF_HH
#define LIKELIHOODTOF_HH

class onelikelihoodtof : public function
{
public:
  likelihoodtof(){}
  virtual ~ likelihoodtof()
  {
  }
  void SetHitInfo(hitinfo infoin)
  {
    info = infoin;
  }
  void SetReconstructdata(Reconstructdata datain)
  {
    data = datain;
  }
  void 
private:
  std::shared_ptr<fptoferror> ptoferror;
  hitinfo info;
  Reconstructdata data;
};

#endif
  
