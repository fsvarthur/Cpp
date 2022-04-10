#include <iostream>
#include <filesystem>

using namespace std;


void descreva(const filesystem::path& p){
  cout << boolalpha << "Path: " << p << endl;
  try{
    cout << "É caminho: " << filesystem::is_directory(p) << endl;
    cout << "È arquivo regular: " << filesystem::is_regular_file(p) << endl;
  }catch (const exception& e){
    cerr << "Exception: " << e.what() << endl;
  }
}

int main(){
  filesystem::path win_path{ R"(C:/Windows/System32/kernel32.dll)"};
  descreva(win_path);
  win_path.remove_filename();
  descreva(win_path);

  filesystem::path nix_path{ R"(/bin/bash)"};
  descreva(nix_path);
  nix_path.remove_filename();
  descreva(nix_path);
}
