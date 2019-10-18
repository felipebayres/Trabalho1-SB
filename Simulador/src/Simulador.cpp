#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <string>
#include <sstream>
#include "Simulador.hpp"
using namespace std;

void Simulador(string NomeArqObjeto){

  ifstream Arquivo; //ponteiro arquivo
  string linha; // linha do arquivo objeto
  vector<int> vectorObjeto; // vector para códigos (int)

  int contador = 0; // PC
  int linker; // auxiliar para saltos
  int ACC = 0;  // registrador acumulador
  int16_t memoria[2]; // memoria simulada
  int posOP1=0;
  int posOP2=0;

  Arquivo.open(NomeArqObjeto);
  if (!Arquivo.is_open()){
    cout << "Não foi possível abrir o arquivo objeto " << NomeArqObjeto << "\n";
    return ;
  }else{
    getline(Arquivo, linha);
    istringstream iss(linha);
    string subs;
    int subs_int;
    while (iss)
    {
      iss >> subs;
      if (subs != "OO"){
        subs_int = stoi(subs);
        vectorObjeto.push_back(subs_int);
      }else{
        subs_int = 0;
        vectorObjeto.push_back(subs_int);
      }
    }
    //for (int i = 0; i < (vectorObjeto.size(); i++){
    //  cout << vectorObjeto[i];
    //}
  }

  while(vectorObjeto.at(contador) != STOP){
    switch (vectorObjeto.at(contador)){
      case ADD: // 1
        cout << "ADD:" << endl;
        posOP1 = vectorObjeto.at(++contador);
        ACC = ACC + (vectorObjeto.at(posOP1));
        contador++;
        printf("Valor do acumulador: %d\n", ACC);
        break;
      
      case SUB: //2
        cout << "SUB:" << endl;
        posOP1 = vectorObjeto.at(++contador);
        ACC = ACC - (vectorObjeto.at(posOP1));
        contador++;
        printf("Valor do acumulador: %d\n", ACC);
        break;
      
      case MUL: //3
        cout << "MUL:" << endl;
        posOP1 = vectorObjeto.at(++contador);
        ACC = ACC * (vectorObjeto.at(posOP1));
        contador++;
        printf("Valor do acumulador: %d\n", ACC);
        break;
      
      case DIV: //4
        cout << "DIV:" << endl;
        posOP1 = vectorObjeto.at(++contador);
        ACC = ACC / (vectorObjeto.at(posOP1));
        contador++;
        printf("Valor do acumulador: %d\n", ACC);
        break;
      
      case JMP: //5
        cout << "JMP:" << endl;
        linker = vectorObjeto.at(++contador);
        contador = linker;
        printf("Valor do acumulador: %d\n", ACC);
        break;
      
      case JMPN:  //6
        cout << "JMPN:" << endl;
        if(ACC < 0){
          linker = vectorObjeto.at(++contador);
          contador = linker;
        }else{
          contador = contador + 2;
        }
        cout << "Valor do acumulador:" << ACC << endl;
        break;
      
      case JMPP:  //7
        cout << "JMPP:"<< endl;
        if(ACC > 0){
          linker = vectorObjeto.at(++contador);
          contador = linker;
        }else{
          contador = contador + 2;
        }
        cout << "Valor do acumulador:" << ACC << endl;
        break;
      
      case JMPZ:  //8
        cout << "JMPZ" << endl;
        if(ACC == 0){
          linker = vectorObjeto.at(++contador);
          contador = linker;
        }else{
          contador = contador + 2;
        }
        cout << "Valor do acumulador:" << ACC << endl;
        break;
      
      case COPY:  //9
        cout << "COPY" << endl;
        posOP1 = vectorObjeto.at(contador + 1);
        posOP2 = vectorObjeto.at(contador + 2);
        vectorObjeto.at(posOP2) = vectorObjeto.at(posOP1);
        memoria[0] = posOP2;
        memoria[1] = vectorObjeto.at(posOP2);
        contador = contador + 3;

        cout << "Endereço de memoria:" << memoria[0] << endl;
        cout << "Valor de Memória:" << memoria[1] << endl;

        break;
      
      case LOAD:  //10
        cout << "LOAD:" << endl;
        posOP1 = vectorObjeto.at(++contador);
        ACC = vectorObjeto.at(posOP1);
        contador++;
        cout << "Valor do acumulador:" << ACC << endl;
        break;
      
      case STORE: //11
        cout << "STORE:" << endl;
        posOP1 = vectorObjeto.at(++contador);
        vectorObjeto.at(posOP1) = ACC;
        memoria[0] = posOP1;
        memoria[1] = ACC;
        cout << "Endereço de memoria:" << memoria[0] << endl;
        cout << "Valor de Memória:" << memoria[1] << endl;
        contador++;
        break;

      case INPUT: //12
        cout << "INPUT:" << endl;

        cout << "Favor inserir um valor numérico: ";
        cin >> linker;
        posOP1 = vectorObjeto.at(++contador);
        vectorObjeto.at(posOP1) = linker;
        memoria[0] = posOP1;
        memoria[1] = linker;
        contador++;

        cout << "Endereço de Memória:" << memoria[0] << endl;
        cout << "Valor de Memória:" << memoria[1] << endl;
        break;

      case OUTPUT:  //13
        cout << "OUTPUT" << endl;
        posOP1 = vectorObjeto.at(++contador);
        cout << "O valor de saída é:" << vectorObjeto.at(posOP1) << endl;
        contador++;
        break;

      default:
        break;
    }
    int i=0;
    cout << "Vetor objeto:";
    for (i = 0; i < vectorObjeto.size(); i++)
    {
      cout << vectorObjeto[i] << " ";
    }
    cout << endl;
    
  }
}