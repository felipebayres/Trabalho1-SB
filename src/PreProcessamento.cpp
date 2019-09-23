#include <bits/stdc++.h>
#include "PreProcessamento.hpp"
using namespace std;

void PreProcessamento(string NomeArquivo){
    ifstream Arquivo;
    Arquivo.open(NomeArquivo);
    
    if (!Arquivo.is_open()){
        cout << "Não foi possível abrir o arquivo " << NomeArquivo << "\n";
        return;
    }


}