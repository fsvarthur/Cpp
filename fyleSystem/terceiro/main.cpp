#include <iostream>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

struct Atributos {
  Atributos& operator+=(const Atributos& other){
    this->size_bytes += other.size_bytes;
    this->n_diretorios += other.n_diretorios;
    this->n_arquivos += other.n_arquivos;
    return *this;
  }

  size_t size_bytes;
  size_t n_diretorios;
  size_t n_arquivos;
};

void exiba_linha(const Atributos& atributos, string_view path){
  cout << setw(14) << atributos.size_bytes
      << setw(7) << atributos.n_arquivos
      << setw(7) << atributos.n_diretorios
      << " " << path << "\n";
}

Atributos explorador(const directory_entry& diretorio){
  Atributos atributos{};
  for(const auto& entry : recursive_directory_iterator{diretorio.path()}){
    if(entry.is_directory()){
      atributos.n_diretorios++;
    }else{
      atributos.n_arquivos++;
      atributos.size_bytes += entry.file_size();
    }
  }
  return atributos;
}

int main(int argc, const char** argv){
  if(argc != 2){
    cerr << "Uso: treedir PATH";
    return -1;
  }
  const path sys_path{argv[1]};
  cout << "Size                Files  Dirs   Name\n";
  cout << "----------------------------------------";
  Atributos atributos_raiz{};
  for( const auto& entry : directory_iterator{sys_path}){
    try{
      if(entry.is_directory()){
        const auto atributos = explorador(entry);
        atributos_raiz += atributos;
        exiba_linha(atributos, entry.path().string());
        atributos_raiz.n_diretorios++;
      }else{
        atributos_raiz.n_arquivos++;
        error_code ec;
        atributos_raiz.size_bytes += entry.file_size(ec);
        if (ec) cerr << "Error reading file size: " 
                    << entry.path().string() << endl;
      }
    } catch(const exception&){
    }
  }
  exiba_linha(atributos_raiz, argv[1]);
}
