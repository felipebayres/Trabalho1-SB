#include <bits/stdc++.h>
#include "PreProcessamento.hpp"
using namespace std;

void PreProcessamento(string NomeArquivo){
    ifstream Arquivo;
    Arquivo.open(NomeArquivo);
    string linha;
    if (!Arquivo.is_open()){
        cout << "Não foi possível abrir o arquivo " << NomeArquivo << "\n";
        return;
    }
    while(getline(Arquivo, linha)){
        linha = RetiraComentarios(linha);
        cout << linha << endl;
    }
}









string RetiraComentarios(string linha){
    int i = 0,posicao = 0,AchouComentario = 0,QuantidadeApagar = 0;
    
    while(i < linha.size()){
        if(linha[i] == ';'){
            posicao = i;
            AchouComentario = 1;
            break;
        }
        i++;
    }
    QuantidadeApagar = linha.size() - posicao;
    if (AchouComentario == 1){
        linha.erase(posicao,QuantidadeApagar);
    }


    return linha;
}


