#include "tinytiffreader.h"
#include "config.hh"
#include <iostream>
#include <TH2D.h>
#include <TFile.h>
int main(){
  config_TinyTIFF_test config;
  TFile* fout = new TFile(config.outfile,"recreate");
  TinyTIFFReaderFile* tiffr=NULL;
  tiffr=TinyTIFFReader_open(config.filename); 
  if (!tiffr) { 
    std::cout<<"    ERROR reading (not existent, not accessible or no TIFF file)\n"; 
  } else { 
    if (TinyTIFFReader_wasError(tiffr)) std::cout<<"   ERROR:"<<TinyTIFFReader_getLastError(tiffr)<<"\n"; 
    std::cout<<"    ImageDescription:\n"<< TinyTIFFReader_getImageDescription(tiffr) <<"\n"; 
    uint32_t frames=TinyTIFFReader_countFrames(tiffr); 
    std::cout<<"    frames: "<<frames<<"\n"; 
    if (TinyTIFFReader_wasError(tiffr)) std::cout<<"   ERROR:"<<TinyTIFFReader_getLastError(tiffr)<<"\n"; 
    uint32_t frame=0; 
    std::cout << TinyTIFFReader_getBitsPerSample(tiffr,0) << std::endl;
    std::cout << TinyTIFFReader_getImageDescription(tiffr) << std::endl;
    do { 
      uint32_t width=TinyTIFFReader_getWidth(tiffr); 
      uint32_t height=TinyTIFFReader_getHeight(tiffr); 
      bool ok=true;
      if (width>0 && height>0) std::cout<<"    size of frame "<<frame<<": "<<width<<"x"<<height<<"\n"; 
      else { std::cout<<"    ERROR IN FRAME "<<frame<<": size too small "<<width<<"x"<<height<<"\n"; ok=false; } 
      if (ok) { 
	frame++; 
	uint8_t* image=(uint8_t*)calloc(width*height, sizeof(uint8_t));
	TinyTIFFReader_getSampleData(tiffr, image, 0);
	if (TinyTIFFReader_wasError(tiffr)) { ok=false; std::cout<<"   ERROR:"<<TinyTIFFReader_getLastError(tiffr)<<"\n"; } 
	TH2D* h1 = new TH2D("h1",";x;y",(int)width/20,0.,(double)width,(int)height/20,0.,(double)height);
	TH2D* h2 = new TH2D("h2",";x;y",(int)width/20,0.,(double)width,(int)height/20,-(double)height,0.);
	for(int row_number = 0;row_number < (int)height;row_number++){
	  for(int column_number = 0;column_number < (int)width;column_number++){
	    if(column_number%20 == 0 && row_number%20 == 0){
	      int i = row_number*((int)width) + column_number;
	      if((unsigned)image[i] > 20){
		std::cout << "@";
	      }
	      else{
		std::cout << "/";
	      }
	      h1->Fill((double)column_number,(double)row_number,(unsigned)image[i]);
	      h1->GetYaxis()->SetTicks("-");
	    }
	  }
	  if(row_number%20 == 0){
	    std::cout << std::endl;
	  }
	}
	std::cout << std::endl;
	for(int row_number = 0;row_number < (int)height;row_number++){
	  for(int column_number = 0;column_number < (int)width;column_number++){
	    if(column_number%20 == 0 && row_number%20 == 0){
	      int j = column_number*((int)height) + row_number;
	      if((unsigned)image[j] > 20){
		std::cout << "@";
	      }
	      else{
		std::cout << "/";
	      }
	      h2->Fill((double)column_number,-(double)row_number,(unsigned)image[j]);
	    }
	  }
	  if(row_number%20 == 0){
	    std::cout << std::endl;
	  }
	}
	free(image); 
      } 
    } while (TinyTIFFReader_readNext(tiffr)); // iterate over all frames
    std::cout<<"    read "<<frame<<" frames\n"; 
  } 
  TinyTIFFReader_close(tiffr);
  fout->Write();
  fout->Close(); 
  return 0;
}
