#include "config.hh"
#include "integral_photo.hh"
#include <iostream>
#include <exception>
int main(){
  try{
    config_integral_photo config;
    std::cout << "integral remove background:" << integral_photo(config.infile,config.sigarea,config.bgarea,config.gamma) << std::endl;
    std::cout << "integral all:" << integral_all(config.infile,config.gamma) << std::endl;
  }
  catch(std::exception& e){
    std::cout << "exception is occured" << std::endl;
    std::cout << e.what() << std::endl;
  }
  catch(const char* str){
    std::cout << "Error in " << str << std::endl;
  }
  return 0;
}
