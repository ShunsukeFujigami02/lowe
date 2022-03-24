#include "MultiRunAnalizeManager.hh"
#include <TCanvas.h>
int main()
{
  MultiRunAnalizeManager* mram = new  MultiRunAnalizeManager();
  mram->SetBasefile("~/store/goodnessfile/SIG5GTcGRn_21_-600_50_21_-500_50_21_-500_50_300_-300_1GN10000DETskPePOSf_-100_0_0DIRf_0_0Ef_5RFtz_0.0_20_60RSnsTT24TW200PR-400PO950DR4.2ANfN10000.root");
  mram->SetAllfile();
  std::vector<std::string> vexclusionname;
  vexclusionname.push_back("RFtrmax");
  mram->SetComparefile(vexclusionname);
  TH1D* hx = new TH1D("","",21,-550.,550.);
  TH1D* hy = new TH1D("","",21,-550.,550.);
  TH1D* hz = new TH1D("","",21,-550.,550.);
  TCanvas* c1 = new TCanvas();
  for(auto itr = mram->vrunanalizemanager.begin();itr != mram->vrunanalizemanager.end();itr++)
    {
      std::string base = "/home/fujigami/retro/lowe/picture/2021January/dis";
      std::string r = std::to_string((*itr)->Getdatamanager()->GetDataParameters()->trapezoidreflectivity);
      (*itr)->GetTH1DEvent(hx,10000,"xbiasgoodness");
      (*itr)->GetTH1DEvent(hy,10000,"ybiasgoodness");
      (*itr)->GetTH1DEvent(hz,10000,"zbiasgoodness");
      hx->Draw();
      std::string xfilename = base + "xr" + r + ".png";
      c1->SaveAs(xfilename.c_str());
      hy->Draw();
      std::string yfilename = base + "yr" + r + ".png";
      c1->SaveAs(yfilename.c_str());
      hz->Draw();
      std::string zfilename = base + "zr" + r + ".png";
      c1->SaveAs(zfilename.c_str());
      hx->Reset();
      hy->Reset();
      hz->Reset();
    }
}

