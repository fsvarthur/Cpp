#include <fstream>

int main(){
  std::ofstream file{"time.txt",std::ios::out|std::ios::app};
  file << "Time is an illusion." << std::endl;
  file << "Luch time, " << 2 << "x so." << std::endl;
  
}
