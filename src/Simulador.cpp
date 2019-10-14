#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include "Simulador.hpp"
using namespace std;

int ACC;  // registrador acumulador

void Simulador(string NomeArqObjeto){

  ifstream Arquivo;
  string linha;
  int ContadorLinhas = 0;
  ACC = 0;
  Arquivo.open(NomeArqObjeto);
    
  if (!Arquivo.is_open()){
    cout << "Não foi possível abrir o arquivo objeto " << NomeArqObjeto << "\n";
    return ;
  }

  while(Arquivo.peek() != EOF){
    string operando;
    int COD;
    operando = getline(Arquivo, linha);
    COD = stoi(operando);

    switch (COD){
      case ADD:
        /* code */
        break;
      
      case SUB:
        /* code */
        break;
      
      case MUL:
        /* code */
        break;
      
      case DIV:
        /* code */
        break;
      
      case JMP:
        /* code */
        break;
      
      case JMPN:
        /* code */
        break;
      
      case JMPP:
        /* code */
        break;
      
      case JMPZ:
        /* code */
        break;
      
      case COPY:
        /* code */
        break;
      
      case LOAD:
        /* code */
        break;
      
      case STORE:
        /* code */
        break;
      
      case INPUT:
        int input;
        cout << "Favor inserir um valor numérico: " << endl;
        cin >> input;
        break;
      
      case OUTPUT:
        cout << "O valor de saída é:" << endl;
        break;
      
      case STOP:
        /* code */
        break;
      
      default:
        break;
    }
}