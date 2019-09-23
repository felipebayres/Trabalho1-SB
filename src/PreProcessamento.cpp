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
        if(!linha.empty()){
            linha = TransformaMaiusculo(linha);
            cout << linha << endl;
        }
    }
}
// Funcao que retira os comentarios do código e retira as tabulacoes do comeco do codigo
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
    i = 0;
    while(i < linha.size()){
            if(isspace(linha[i])){
                linha.erase(i,1);
            }
            else
            {
                    break;
            }
            
        }

    return linha;
}

string TransformaMaiusculo(string linha){
    // convert string to upper case
    std::for_each(linha.begin(), linha.end(), [](char & c){
        c = ::toupper(c);
    });

    return linha;
}

