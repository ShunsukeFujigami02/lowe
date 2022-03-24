// c++ STL
#include <iostream>

// ROOT library
#include <TFile.h>
#include <TChain.h>

void convert(char *treename,char* infilehead,char *outname,int eventsPerJob,int maxEvents)
{
  TFile *fout = new TFile(outname,"recreate");
  TChain *tree = new TChain(treename);
  for(int startEvent = 0;startEvent < maxEvents;startEvent += eventsPerJob){
    tree->Add(Form("analize/divided/%s%05d.root",infilehead,startEvent));
  }
  if(tree->GetEntries() == 0){
    delete tree;
    delete fout;
    throw 0;
  }
  fout->Add(tree);
  fout->Write();
  fout->Close();
  //  delete tree;
  delete fout;
}
int main(int argc,char *argv[])
{
  if(argc != 6){
    std::cout<<"err : number of variable is wrong.\n";
  }
  else{
    char *treename = argv[1];
    char* infilehead = argv[2];
    char *outname = argv[3];
    int eventsPerJob = atoi(argv[4]);
    int maxEvents = atoi(argv[5]);
    convert(treename,infilehead,outname,eventsPerJob,maxEvents);
  }
  return 0;
}
