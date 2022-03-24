#include "Energy.hh"
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"
#include <memory>
#include "config.hh"

int main()
{
  AnalizeFiledata*data = new AnalizeFiledata();
  try{
    std::string sinfile = Getchar("INFILE");
    AnalizeFile file(sinfile);
    data->Construct(file);
    TFile* fout = new TFile(Getchar("OUTFILE"),"recreate");
    TTree* tree = new TTree("effNT","efficient Number of Hit Tree");
    double effNdir;
    double effNref;
    tree->Branch("effNdir",&effNdir);
    tree->Branch("effNref",&effNref);
    std::string funcname = Getchar("ENERGYFUNCNAME");
    double lambda = Getdouble("LAMBDA");
    int n_event = Getint("NEVENTS");
    for(int i = 0;i < n_event;++i)
      {
	data->GetEntry(i);
	if(funcname == "NoRetro"){
	  std::vector<double> doubleval;
	  std::shared_ptr<EnergyFunction> efunc = std::make_shared<NeffNoRetro>();
	  efunc->SetData(file,data);
	  efunc->SetLambda(lambda);
	  efunc->returnvalue(doubleval);
	  std::cout << "effN = " << doubleval[0] << std::endl;
	  effNdir = doubleval[0];
	  effNref = doubleval[1];
	  tree->Fill();
	}
	if(funcname == "NoRetroTrue"){
	  std::vector<double> doubleval;
	  std::shared_ptr<EnergyFunction> efunc = std::make_shared<NeffNoRetroTrue>();
	  efunc->SetData(file,data);
	  efunc->SetLambda(lambda);
	  efunc->returnvalue(doubleval);
	  std::cout << "effN = " << doubleval[0] << std::endl;
	  effNdir = doubleval[0];
	  effNref = doubleval[1];
	  tree->Fill();
	}
	/*	else if(funcname == "OnRetro"){
	  std::vector<int> intval;
	  std::vector<double> doubleval;
	  std::shared_ptr<EnergyFunction> efunc = std::make_shared<NeffOnRetro>();
	  efunc->SetData(file,data);
	  effN = efunc->returnvalue(intval,doubleval);
	  std::cout << "effN = " << effN << std::endl;
	  N50noretro = intval[0];
	  N100noretro = intval[1];
	  N50onretro = intval[2];
	  Ntype0 = intval[3];
	  Ntype1 = intval[4];
	  Ntype2 = intval[5];
	  Ntype3 = intval[6];
	  effNtype0 = doubleval[0];
	  effNtype1 = doubleval[1];
	  effNtype2 = doubleval[2];
	  effNtype3 = doubleval[3];
	  tree->Fill();
	  }*/
	/*	else if(funcname == "OnRetroaddretrotail"){
	  std::shared_ptr<EnergyFunction> efunc = std::make_shared<NeffOnRetroaddretrotail>();
	  efunc->SetData(file,data);
	  effN = efunc->returnvalue();
	  std::cout << "effN = " << effN << std::endl;
	  tree->Fill();
	  }*/
	if(funcname == "OnRetroFinal"){
	  double lambdaRetro = Getdouble("LAMBDARETRO");
	  std::vector<double> doubleval;
	  std::shared_ptr<EnergyFunction> efunc = std::make_shared<NeffOnRetroFinal>();
	  efunc->SetData(file,data);
	  efunc->SetN(i);
	  efunc->SetLambda(lambda);
	  efunc->SetLambdaRetro(lambdaRetro);
	  efunc->returnvalue(doubleval);
	  std::cout << "effNdirect = " << doubleval[0] << std::endl;
	  std::cout << "effNreflect = " << doubleval[1] << std::endl;
	  effNdir = doubleval[0];
	  effNref = doubleval[1];
	  tree->Fill();
	}
	if(funcname == "OnRetroFinalver2"){
	  //	  double lambdaRetro = Getdouble("LAMBDARETRO");
	  std::vector<double> doubleval;
	  std::shared_ptr<EnergyFunction> efunc = std::make_shared<NeffOnRetroFinalver2>();
	  efunc->SetData(file,data);
	  efunc->SetN(i);
	  efunc->SetLambda(lambda);
	  //	  efunc->SetLambdaRetro(lambdaRetro);
	  efunc->returnvalue(doubleval);
	  std::cout << "effNdirect = " << doubleval[0] << std::endl;
	  std::cout << "effNreflect = " << doubleval[1] << std::endl;
	  effNdir = doubleval[0];
	  effNref = doubleval[1];
	  tree->Fill();
	}
	if(funcname == "OnRetroFinalTrue"){
	  double lambdaRetro = Getdouble("LAMBDARETRO");
	  std::vector<double> doubleval;
	  std::shared_ptr<EnergyFunction> efunc = std::make_shared<NeffOnRetroFinalTrue>();
	  efunc->SetData(file,data);
	  efunc->SetN(i);
	  efunc->SetLambda(lambda);
	  efunc->SetLambdaRetro(lambdaRetro);
	  efunc->returnvalue(doubleval);
	  std::cout << "effNdirect = " << doubleval[0] << std::endl;
	  std::cout << "effNreflect = " << doubleval[1] << std::endl;
	  effNdir = doubleval[0];
	  effNref = doubleval[1];
	  tree->Fill();
	}
	if(funcname == "OnRetroFinalver2True"){
	  double lambdaRetro = Getdouble("LAMBDARETRO");
	  std::vector<double> doubleval;
	  std::shared_ptr<EnergyFunction> efunc = std::make_shared<NeffOnRetroFinalver2True>();
	  efunc->SetData(file,data);
	  efunc->SetN(i);
	  efunc->SetLambda(lambda);
	  efunc->SetLambdaRetro(lambdaRetro);
	  efunc->returnvalue(doubleval);
	  std::cout << "effNdirect = " << doubleval[0] << std::endl;
	  std::cout << "effNreflect = " << doubleval[1] << std::endl;
	  effNdir = doubleval[0];
	  effNref = doubleval[1];
	  tree->Fill();
	}
	if(funcname == "OnRetroFinalver3True"){
	  double lambdaRetro = Getdouble("LAMBDARETRO");
	  std::vector<double> doubleval;
	  std::shared_ptr<EnergyFunction> efunc = std::make_shared<NeffOnRetroFinalver3True>();
	  efunc->SetData(file,data);
	  efunc->SetN(i);
	  efunc->SetLambda(lambda);
	  efunc->SetLambdaRetro(lambdaRetro);
	  efunc->returnvalue(doubleval);
	  std::cout << "effNdirect = " << doubleval[0] << std::endl;
	  std::cout << "effNreflect = " << doubleval[1] << std::endl;
	  effNdir = doubleval[0];
	  effNref = doubleval[1];
	  tree->Fill();
	}
	if(funcname == "OnRetroFinalver3"){
	  //	  double lambdaRetro = Getdouble("LAMBDARETRO");
	  std::vector<double> doubleval;
	  std::shared_ptr<EnergyFunction> efunc = std::make_shared<NeffOnRetroFinalver3>();
	  efunc->SetData(file,data);
	  efunc->SetN(i);
	  efunc->SetLambda(lambda);
	  //	  efunc->SetLambdaRetro(lambdaRetro);
	  efunc->returnvalue(doubleval);
	  std::cout << "effNdirect = " << doubleval[0] << std::endl;
	  std::cout << "effNreflect = " << doubleval[1] << std::endl;
	  effNdir = doubleval[0];
	  effNref = doubleval[1];
	  tree->Fill();
	}
      }
    fout->Write();
    fout->Close();
  }
  catch(const char* str)
    {
      std::cout << "Error in " << str << std::endl;
    }
  catch(std::out_of_range&)
    {
      std::cout << "exception std::out_of_range" << std::endl;
    }
  return 0;
}
  
