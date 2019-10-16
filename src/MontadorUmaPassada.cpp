#include <string.h>
#include <iostream>
#include <fstream>
#include "MontadorUmaPassada.hpp"
map<string,TabelaSimbolos> TabelaDeSimbolos;

string MontadorUmaPassada(string NomeArquivo){
    ifstream Arquivo;
    Arquivo.open(NomeArquivo);
    string linha;
    bool FlagText = false , FlagData = false, FlagLabel = false;
    int ContadorLinhas = 0;
    
    //Verifica se existe a secao text e coloca ela na primeira posicao
    PadronizaSection(NomeArquivo);
    string NomeArquivoObjeto;
    NomeArquivoObjeto = NomeArquivo.substr(0, NomeArquivo.size()-4) + ".obj";
    ofstream ArquivoObjeto(NomeArquivoObjeto);

    vector<string> VetorObjeto;

    if(!ArquivoObjeto.is_open()){
        cout << "Não foi possivel gerar o arquivo objeto " << "\n";
        return "";
    }
    if (!Arquivo.is_open()){
        cout << "Não foi possível abrir o arquivo pre-processado " << NomeArquivo << "\n";
        return "";
    }
    getline(Arquivo, linha);
    while(Arquivo.peek() != EOF){
        
        if (linha.compare("SECTION TEXT") == 0 && FlagText == false){
            FlagText = true;
            while(getline(Arquivo, linha)){
                istringstream buf(linha),aux(linha);
                vector<string> v;
                string auxiliar;
                //Verificar se existe a declaracao de outra section
                aux >> auxiliar;
                if(auxiliar.compare("SECTION") == 0){
                    break;
                }
                //Separa todas as palavras da linha e coloca elas em um vector
                for(string palavra; buf >> palavra; ){
                    v.push_back(palavra);
                    // imprime todas as palavras da linha cout << palavra << endl;
                }
                
                
                
                
                int i = 0;
                string palavra = v[i];
                // Essas variaveis guardam o numero que o argumento pode receber(vetor);
                int VetorArgumento[2] = {0,0};
                
                // Verifica se a primeira palavra da linha é um label
                if(palavra.back() == ':'){
                    palavra = palavra.substr(0, palavra.size()-1);
                    //Verifica se o label é valido
                    if(ValidaToken(palavra)){
                        //Verifica se o label ja foi visto antes
                        if(TabelaDeSimbolos.count(palavra) == 1){
                            //Verifica se o label esta definido
                            if (TabelaDeSimbolos[palavra].definido == false){
                                TabelaDeSimbolos[palavra].definido = true;
                                TabelaDeSimbolos[palavra].Valor = ContadorLinhas;
                            }
                            else
                            {
                                cout << "Simbolo na linha " << ContadorLinhas << " ja foi definido antes" << endl;    
                            }
                        }
                        //Se o simbolo nao tiver na tabela ainda
                        else {
                            TabelaDeSimbolos[palavra].definido = true;
                            TabelaDeSimbolos[palavra].Tipo = 0;
                            TabelaDeSimbolos[palavra].Valor = ContadorLinhas;
                        }
                    }
                    //Caso o label nao seja valido
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
                      //cout <<"V[" <<l<<"]=" << v[l] << " ";
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
                ContadorLinhas++;
                //Escreve as instrucoes no arquivo
                VetorObjeto.push_back(to_string(numero));
                
                
                // A partir daqui é feito  o tratamento dos operandos
                int l = 0;
                for (int j = i+1; j < v.size();j++){
                    palavra = v[j];
                    //Verifica se a instrucao pode receber vetor como operando
                    if (numero >=5 && numero <= 13){
                        int pos = palavra.find_first_of('+');
                        
                        //Se tiver um vetor com mais de uma posicao
                        if (pos != -1){
                            string TamanhoVetor_str;
                            TamanhoVetor_str = v[j].substr(pos+1,-1);
                            v[j].erase(pos,v[j].size()-pos);
                            palavra = v[j];
                            VetorArgumento[l] = stoi(TamanhoVetor_str);
                        }
                    }
                    if(ValidaToken(palavra)){
                        //Verifica se o label ja foi definido antes
                        if(TabelaDeSimbolos.count(palavra) == 1){
                            if(TabelaDeSimbolos[palavra].definido == true){
                                //Escreve no arquivo a posicao correta se o label ja foi definido
                                VetorObjeto.push_back(to_string(TabelaDeSimbolos[palavra].Valor + VetorArgumento[l]));
                            }
                            // Se ele nao estiver definido, é colocado o lugar de uso na tabela e o valor inicial do vetor  
                            else{
                                TabelaDeSimbolos[palavra].LugaresUsados.push_back(ContadorLinhas);  
                                VetorObjeto.push_back(to_string(VetorArgumento[l]));
                            }
                        }
                        //Se nao foi definido antes é escrito na tabela de simbolos
                        else {
                            VetorObjeto.push_back(to_string(VetorArgumento[l]));
                            TabelaDeSimbolos[palavra].definido = false;
                            TabelaDeSimbolos[palavra].Valor = -1;
                            TabelaDeSimbolos[palavra].LugaresUsados.push_back(ContadorLinhas);
                        
                        }
                    }
                    else{
                        cout << "Linha:" << ContadorLinhas << endl;
                    }
                ContadorLinhas++;
                l++;
                }
                // Para debuggar a quantidade de espacos se for um vetor
                    //cout << "instrucao:" << v[i] << endl;
                    //cout << VetorArgumento[0] << " " << VetorArgumento[1] << endl;
                FlagLabel = false;
            }
            
        }
            
        if (linha.compare("SECTION DATA") == 0 && FlagData == false){
            FlagData = true;
            while(getline(Arquivo, linha)){
                istringstream buf(linha),aux(linha);
                vector<string> v;
                string auxiliar;
                
                //Verificar se existe a declaracao de outra section
                aux >> auxiliar;
                if(auxiliar.compare("SECTION") == 0){
                    break;
                }
                
                // Separa a linha por palavras e armazena cada uma em uma posicao do vector
                for(string palavra; buf >> palavra; ){
                    v.push_back(palavra);
                    //cout << palavra << endl;
                }
                int i = 0;
                string palavra = v[i];
                string Label;
                
                // Verifica se a primeira palavra da linha é um label
                if(palavra.back() == ':'){
                    palavra = palavra.substr(0, palavra.size()-1);
                    Label = palavra;
                    //Verifica se o label é valido   
                    if(ValidaToken(palavra)){
                        //Verifica se o label ja foi visto antes
                        if(TabelaDeSimbolos.count(palavra) == 1){
                            //Se o label ja estiver definido
                            if(TabelaDeSimbolos[palavra].definido == true)
                                cout << "Label ja foi definido antes" << endl;
                            //Se o label ainda nao estiver definido
                            else{
                                TabelaDeSimbolos[palavra].definido = true;
                                TabelaDeSimbolos[palavra].Valor = ContadorLinhas;

                            }
                        }
                        else {
                            TabelaDeSimbolos[palavra].definido = true;
                            TabelaDeSimbolos[palavra].Valor = ContadorLinhas;
                        }
                    }
                    else
                        cout << "Linha:" << ContadorLinhas << endl;
                }
                else
                    cout << " Comandos na Section Data devem comecar com um label" << endl;
                
                i++;
                palavra = v[i];
                
                // Verifica a diretiva presente na linha 
                if (palavra.compare("SPACE") == 0){
                    TabelaDeSimbolos[Label].Tipo = 2; 
                    int QuantidadeSpaces = 1;
                    //Se houver um numero em seguida da palavra SPACE
                    if(v.size() == 3)
                        QuantidadeSpaces = stoi(v[2]);
                    else if (v.size() > 3){
                        cout << "Quantidade de argumentos invalidos para SPACE"<< endl;
                        cout << "Linha:" << ContadorLinhas << endl;  
                    }    
                    for(int i = 0 ; i < QuantidadeSpaces;i++)
                        VetorObjeto.push_back("OO"); 
                    ContadorLinhas = ContadorLinhas + QuantidadeSpaces;
                }
                else if (palavra.compare("CONST") == 0){
                    string numero;
                    TabelaDeSimbolos[Label].Tipo = 1;
                    bool FlagNegativo = false;
                    if (v.size() != 3){
                        cout << "Numero de argumentos para CONST invalido!" << endl;
                        cout << "Linha:" << ContadorLinhas << endl;
                    }
                    int ValorFinal = 0,ValorHexa;
                    numero = v[2]; 
                    if(numero[0] == '-'){
                        FlagNegativo = true;
                        numero.erase(0,1);
                    } 
                    if(VerificaHexa(numero)){
                        stringstream stream;
                        stream << numero;
                        stream >> std::hex >> ValorFinal;
                    }
                    else{
                        ValorFinal = stoi(numero);

                    }
                    if (FlagNegativo)
                        ValorFinal = ValorFinal*(-1);
                    // Mostrar o valor do const
                    //cout << ValorFinal << endl;
                    VetorObjeto.push_back(to_string(ValorFinal));
                    
                    ContadorLinhas++;


                }
                else{
                    cout << "Diretiva inexistente" << endl;
                    cout << ContadorLinhas << endl;
                }
            }
        }
        else{
            if(Arquivo.peek() != EOF){
                cout << "Secao invalida ou ja definida:" << linha << endl;
                cout << "Linha:" << ContadorLinhas << endl;
                break;
            }
        }
    }
    if(FlagText == false)
        cout << "Linha:"<< ContadorLinhas << endl;
    //ArquivoObjeto.close();
    
    //Essa parte do codigo coloca os valores dos labels que faltam no codigo
    for(auto& Simbolo : TabelaDeSimbolos){
	    vector<int> ListaUsos;
        if (Simbolo.second.definido == false){
            cout << "Simbolo nao definido";
            cout << Simbolo.first << endl;
        }
        // Se todos os simbolos estiverem definidos
        
        
        else{
            //Se tiver local em que ele nao foi definido corretamente
            if(!Simbolo.second.LugaresUsados.empty()){
                int j = 0;
                while(j < Simbolo.second.LugaresUsados.size()) {
                    int PosicaoUsada = Simbolo.second.LugaresUsados[j];
                    //Procura no VetorObjeto o local a ser substituido
                    for(int i = 0 ; i < VetorObjeto.size() ; i++){
                        if(PosicaoUsada == i){
                            //cout << "Simbolo:" << Simbolo.first << " " ;
                            //cout << "Lugar usado: " << Simbolo.second.LugaresUsados[j] << endl;
                            //cout << "VetorObjeto["<< i<<"]"<<"="<< VetorObjeto[i] <<"+"<<Simbolo.second.Valor << endl;
                            VetorObjeto[i] = to_string(stoi(VetorObjeto[i]) + Simbolo.second.Valor);
                            //cout << VetorObjeto[i] << endl;
                            break;
                        }
                    }
                    j++;
                }
            }   
        }
        
    
    }
    for (int i = 0 ; i < VetorObjeto.size() ; i++){
        cout << VetorObjeto[i] << " ";
        ArquivoObjeto << VetorObjeto[i] << " ";
    }
    cout << endl;
    ArquivoObjeto.close();
    Arquivo.close();
    return NomeArquivoObjeto;
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
bool VerificaHexa(string s){
  return s.compare(0, 2, "0X") == 0
      && s.size() > 2
      && s.find_first_not_of("0123456789abcdefABCDEF", 2) == std::string::npos;
}

void PadronizaSection(string NomeArquivo){
    ifstream Arquivo;
    ofstream ArquivoNovo;
    Arquivo.open(NomeArquivo);
    string linha;
    bool FlagText = false;
    vector<string> VetorText,VetorArquivo;
    
    if (!Arquivo.is_open()){
        cout << "Não foi possível abrir o arquivo pre-processado " << NomeArquivo << "\n";
        return ;
    }
    while(getline(Arquivo, linha)){
        
        if (linha.compare("SECTION TEXT") == 0){
            FlagText = true;
            VetorText.push_back(linha);
            while(getline(Arquivo, linha))
                VetorText.push_back(linha);
            VetorText.insert(std::end(VetorText), std::begin(VetorArquivo), std::end(VetorArquivo));
        }
        VetorArquivo.push_back(linha);

    }
    Arquivo.close();
    ArquivoNovo.open(NomeArquivo,std::ofstream::out | std::ofstream::trunc);
    if (!FlagText)
        cout << "Section text nao declarada" << endl;
    for(int i = 0 ; i < VetorText.size() ; i++){
        ArquivoNovo << VetorText[i] << endl;
    }
    ArquivoNovo.close();
}