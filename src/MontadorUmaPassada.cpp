#include <string.h>
#include <iostream>
#include <fstream>
#include "MontadorUmaPassada.hpp"
map<string,int> Simbolos;
vector<list<int>> Lista;
vector<Tabela> TabelaSimbolos;
void MontadorUmaPassada(string NomeArquivo){
    ifstream Arquivo;
    Arquivo.open(NomeArquivo);
    string linha;
    bool FlagText = false , FlagData = false, FlagLabel = false;
    
    int ContadorLinhas = 0;
    
    if (!Arquivo.is_open()){
        cout << "Não foi possível abrir o arquivo pre-processado " << NomeArquivo << "\n";
        return ;
    }
    
    getline(Arquivo, linha);

    if (linha.compare("SECTION TEXT") == 0){
        FlagText = true;
        while(getline(Arquivo, linha)){
            istringstream buf(linha);
            vector<string> v;
            // Se acabar a secao de texto ele comeca a analizar a de dados
            if(linha.compare("SECTION DATA") == 0)
                break;
            //Separa todas as palavras da linha e coloca elas em um vector
            for(string palavra; buf >> palavra; ){
                v.push_back(palavra);
                // imprime todas as palavras da linha cout << palavra << endl;
            }
            
            
            
            
            int i = 0;
            string palavra = v[i];
            
            // Verifica se a primeira palavra da linha é um label
            if(palavra.back() == ':'){
                palavra = palavra.substr(0, palavra.size()-1);
                //Verifica se o label é valido
                if(ValidaToken(palavra)){
                    //Verifica se o label ja foi definido antes
                    if(Simbolos.count(palavra) != 1){
                        Tabela Aux;
                        Aux.Simbolo = palavra;
                        Aux.definido = true;
                        Aux.valor = ContadorLinhas;
                        Simbolos[palavra] = ContadorLinhas;
                        TabelaSimbolos.push_back(Aux);

                    }
                    else {
                        cout << "Simbolo na linha " << ContadorLinhas << " ja foi definido antes" << endl;
                    }
                }
                else{
                    cout << "Linha:" << ContadorLinhas << endl;



                }
                FlagLabel = true;
                i++;
            }
            
            
            // A partir daqui é feito o tratamento da instrucao em si;
            palavra = v[i];
            
            int numero = ValidaInstrucao(palavra);
            
            // Verifica se a instrucao existe no assembly inventado
            if (numero < 0){
                    cout << "Instrucao " << palavra << " inexistente" << endl;
                    cout << "Linha:" << ContadorLinhas << endl;
                }
            // Separa os argumentos da instrucao copy em dois simbolos
            if (numero == 9){
                int k = i;
                string Aux;
                Aux = v[i+1];
                v.pop_back();
                istringstream ss(Aux);
                string token;
                while(getline(ss, token, ',')){
                    int k = i+1;
                    v.push_back(token);
                    k++;

                }
                //Para printar o vector da linha depois dos ajustes
                //for(int l = 0; l < v.size();l++)
                  //  cout <<"V[" <<l<<"]=" << v[l] << " ";
            }
            int tamanho = v.size();
            if(FlagLabel){
                tamanho = tamanho - 1;
            }
            // Verifica se tem a quantidade certa de argumentos da instrucao
            if ((numero < 8 && tamanho != 2) || (numero == 9 && tamanho != 3) || ((numero > 9 && numero < 14) && tamanho != 2) || (numero == 14 && tamanho != 1)){
                cout << "Numero invalido de argumentos pra instrucao " << palavra << endl;
                cout << "Linha:" << ContadorLinhas << endl;

            }
            // A partir daqui é feito  o tratamento dos operandos
            for (int j = i+1; j < tamanho;j++){
                palavra = v[j];
                if(ValidaToken(palavra)){
                    //Verifica se o label ja foi definido antes
                    if(Simbolos.count(palavra) != 1){
                        
                        

                    }
                    //Se nao foi definido antes é escrito na tabela de simbolos
                    else {
                        Tabela Aux;
                        Aux.Simbolo = palavra;
                        Aux.definido = false;
                        Aux.valor = ContadorLinhas;
                        Simbolos[palavra] = ContadorLinhas;
                        TabelaSimbolos.push_back(Aux);
                    }
                }
                else{
                    cout << "Linha:" << ContadorLinhas << endl;



                }
            }

            FlagLabel = false;
            // REVER O CONTADOR QUANDO A INSTRUCAO É O COPY
            ContadorLinhas = ContadorLinhas + tamanho;
        }
        
    }
        



    else if (linha.compare("SECTION DATA") == 0){
        while(getline(Arquivo, linha) && linha.compare("SECTION TEXT") != 0){

        
        }


    }


}

int ValidaInstrucao(string instrucao){
    if (instrucao.compare("ADD") == 0)
        return 1;
    else if (instrucao.compare("SUB") == 0)
        return 2;
    else if (instrucao.compare("MULT") == 0)
        return 3;
    else if (instrucao.compare("DIV") == 0)
        return 4;
    else if (instrucao.compare("JMP") == 0)
        return 5;
    else if (instrucao.compare("JMPN") == 0)
        return 6;
    else if (instrucao.compare("JMPP") == 0)
        return 7;
    else if (instrucao.compare("JMPZ") == 0)
        return 8;
    else if (instrucao.compare("COPY") == 0)
        return 9;
    else if (instrucao.compare("LOAD") == 0)
        return 10;
    else if (instrucao.compare("STORE") == 0)
        return 11;
    else if (instrucao.compare("INPUT") == 0)
        return 12;
    else if (instrucao.compare("OUTPUT") == 0)
        return 13;
    else if (instrucao.compare("STOP") == 0)
        return 14;
    return -1;
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