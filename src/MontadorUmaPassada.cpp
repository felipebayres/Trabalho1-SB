#include <string.h>
#include <iostream>
#include <fstream>
#include "MontadorUmaPassada.hpp"


void MontadorUmaPassada(string NomeArquivo){
    ifstream Arquivo;
    Arquivo.open(NomeArquivo);
    string linha;
    
    if (!Arquivo.is_open()){
        cout << "Não foi possível abrir o arquivo pre-processado " << NomeArquivo << "\n";
        return ;
    }

    while(getline(Arquivo, linha)){




    }


}

bool ValidaToken(string token){
    if (token.size() > 50){
        cout << " Tamanho da variavel ou rotulo " << token << " ultrapassa 50 caracteres" << endl;
        return false;
    }
    else if (isdigit(token[0])){
        cout << "A variavel ou rotulo " << token << " possui numero no primeiro caractere" << endl;
        return false;
    }
    if (token.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") != std::string::npos)
    {
        cout << "Foi utilizado um caractere invalido no token " << token << endl;
        return false;
    }
    return true;



}