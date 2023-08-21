#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<filesystem>
#include<cstring>
#include<cstdint>
#include<limits>
void xor_cipher(const std::string&);
namespace fs = std::filesystem;
int main(int argc, char*argv[]){
  std::string path;

  if(argc > 1){
     path = argv[1];
     if(fs::exists(path)==false){
       std::cerr<<"Invalid file path!"<<std::endl;
       path.clear();
      }else
     xor_cipher(path);
  }if(path.empty() or argc==1) {
  std::cout<<"Please enter the path of the file:-"<<std::endl;
  while(true){
    std::getline(std::cin,path);
    if(fs::exists(path)==false){
      std::cerr<<"Invalid file path! Please enter a correct path:-"<<std::endl;
      path.clear();
      }
    else
      break;
     }
    xor_cipher(path);
   }
  std::cout<<"Please press any key to close this program..."<<std::endl;
  std::cin.get();
  return EXIT_SUCCESS;
}
void xor_cipher(const std::string&path){
  std::fstream file(path,std::ios::in|std::ios::out|std::ios::binary);
  if(not file.is_open()){
    std::cerr<<"Unable to open the file!"<<std::endl;
    exit(EXIT_FAILURE);
    }
  std::string buffer((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
  std::uint32_t key = 0xF54CE456; // just a random key
  for(char& c : buffer)
    c^= key;
  file.seekp(std::ios::beg);
  file<<buffer;
  file.close();
  std::cout<<"The file has been successfully encrypted\\decrypted!"<<std::endl;
}
