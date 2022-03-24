#ifdef __CINT__
#include "/home/fujigami/retro/TinyTIFF_install/include/tinytiffreader.h"
#else
#include "tinytiffreader.h"
#endif
#include "index_image.hh"
#include <iostream>
#include <TH2D.h>

TH2D* photo_to_hist(const char* infile,const char* histname){
  TinyTIFFReaderFile* tiffr=NULL;
  tiffr=TinyTIFFReader_open(infile);
  if(!tiffr){
    std::cout << "   ERROR reading (not existant, not accessable or no TIFF file)\n";
    throw "photo_to_hist";
  }
  uint32_t width=TinyTIFFReader_getWidth(tiffr); 
  uint32_t height=TinyTIFFReader_getHeight(tiffr); 
  uint8_t* image=(uint8_t*)calloc(width*height, sizeof(uint8_t));  
  TinyTIFFReader_getSampleData(tiffr, image, 0); 
  TH2D* h1 = new TH2D(histname,";x;y",(int)width,-0.5,(double)width+0.5,(int)height,-(double)height - 0.5,0.5);
  for(int row_number = 0;row_number < (int)height;row_number++){
    for(int column_number = 0;column_number < (int)width;column_number++){
      int i = index_image(row_number,column_number,(int)width);
      h1->Fill((double)column_number,-(double)row_number,(unsigned)image[i]);
    }
  }
  free(image); 
  TinyTIFFReader_close(tiffr);
  return h1;
}

TH2D* photo_to_hist_empty(const char* infile,const char* histname){
  TinyTIFFReaderFile* tiffr=NULL;
  tiffr=TinyTIFFReader_open(infile);
  if(!tiffr){
    std::cout << "   ERROR reading (not existant, not accessable or no TIFF file)\n";
    throw "photo_to_hist";
  }
  uint32_t width=TinyTIFFReader_getWidth(tiffr); 
  uint32_t height=TinyTIFFReader_getHeight(tiffr); 
  uint8_t* image=(uint8_t*)calloc(width*height, sizeof(uint8_t));  
  TinyTIFFReader_getSampleData(tiffr, image, 0); 
  TH2D* h1 = new TH2D(histname,";x;y",(int)width,-0.5,(double)width+0.5,(int)height,-(double)height - 0.5,0.5);

  free(image); 
  TinyTIFFReader_close(tiffr);
  return h1;
}

TH2D* photo_to_hist(const char* infile,const char* histname,double gamma){
  TH2D* h1 = photo_to_hist(infile,histname);
  for(int i = 1;i < h1->GetXaxis()->GetNbins() ; i++){
    for(int j = 1;j < h1->GetYaxis()->GetNbins() ; j++){
      double temp = std::pow(h1->GetBinContent(i,j),1./gamma);
      h1->SetBinContent(i,j,temp);
    }
  }
  return h1;
}
