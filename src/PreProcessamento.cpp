#include <string.h>
#include <iostream>
#include <fstream>
#include "PreProcessamento.hpp"

using namespace std;
map <string,int> MapaEQU;

void PreProcessamento(string NomeArquivo){
    ifstream Arquivo;
    Arquivo.open(NomeArquivo);
    string linha;
    bool FlagIF = true;
    if (!Arquivo.is_open()){
        cout << "Não foi possível abrir o arquivo " << NomeArquivo << "\n";
        return;
    }
    
    while(getline(Arquivo, linha)){

        linha = RetiraComentarios(linha);
        if(!FlagIF){
            linha = "";
            FlagIF = true;
        }
        if (VerificaDiretiva(linha) == 1){
            DiretivasEQU(linha);
            linha = "";
        }
        else if (VerificaDiretiva(linha) == 2){
            //Se for pra retirar a proxima linha
            if (!DiretivasIF(linha))
                FlagIF = false;
            linha = "";
        }
        
        
        if(!linha.empty())
            cout << linha << endl;
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
// Verifica se a linha de código é uma diretiva 
// 1 - Diretiva EQU
// 2 - Diretiva IF
int VerificaDiretiva(string linha){
    string palavra;
    istringstream iss(linha);

   while(iss){
      string Palavra;
      iss >> Palavra;
        if(Palavra.compare("EQU") == 0){
            return 1;
        }
        else if (Palavra.compare("IF") == 0){
            return 2;
        }
    }
    return 0;
}
//Armazena os valores dos labels em um dicionario (map)
void DiretivasEQU(string linha){
    
    int Flag = 0,FlagLabel = 0;
    string palavra,Label;
    istringstream iss(linha);

    while(iss){
        int numero;
        string Palavra;
        iss >> Palavra;

        // A primeira palavra da diretiva é o label
        if(FlagLabel == 0){
            Label = Palavra.substr(0, Palavra.size()-1);;
            FlagLabel = 1;
        }
        //Se a flag ja estiver acionada, a proxima palavra é o valor do label
        if (Flag == 1){
            stringstream Valor(Palavra);
            Valor >> numero;
            MapaEQU[Label] = numero;
            //cout << numero << "\n";
            return;
        }
        // Se ele achar a EQU ele aciona a flag
        if(Palavra.compare("EQU") == 0)
            Flag = 1;
        
            
    }
    return;




}
// Funcao que verifica se o a proxima linha vai se manter no programa depois do pre-processamento
// true - A proxima linha ficara
// false - A proxima linha sera deletada
bool DiretivasIF(string linha){

    int Flag = 0;
    istringstream iss(linha);

    while(iss){
        string Palavra,Label;
        iss >> Palavra;

        if( Flag == 1){
            Label = Palavra;
            if(MapaEQU.count(Label)){
                int Valor = MapaEQU[Label];
                if ( Valor != 0)
                    return true;
                else 
                    return false;
            }
            else{
                cout << "Erro! Não foi encontrado valor do label:" << Label << endl;
                return true;
            }
        }
        // Se ele achar a EQU ele aciona a flag
        if(Palavra.compare("IF") == 0)
            Flag = 1;
        
            
    }
}
