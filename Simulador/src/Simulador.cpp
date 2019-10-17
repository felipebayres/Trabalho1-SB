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

  int contador_posicao = 0; // PC
  int linker; // auxiliar para saltos
  int ACC = 0;  // registrador acumulador
  int16_t memoria[2]; // memoria simulada

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
        continue;
      }
    }
    for (int i = 0; i < (vectorObjeto.size()); i++){
      cout << vectorObjeto[i];
    }
  }

  //while(vectorObjeto.at(contador_posicao) != STOP){
  //  switch (vectorObjeto.at(contador_posicao)){
  //    case ADD:
  //      ACC = ACC + vectorObjeto.at(vectorObjeto.at(++contador_posicao));
  //      contador_posicao++;
  //      printf("Valor do acumulador: %d\n", ACC);
  //      break;
  //    
  //    case SUB:
  //      ACC = ACC - vectorObjeto.at(vectorObjeto.at(++contador_posicao));
  //      contador_posicao++;
  //      printf("Valor do acumulador: %d\n", ACC);
  //      break;
  //    
  //    case MUL:
  //      ACC = ACC * vectorObjeto.at(vectorObjeto.at(++contador_posicao));
  //      contador_posicao++;
  //      printf("Valor do acumulador: %d\n", ACC);
  //      break;
  //    
  //    case DIV:
  //      ACC = ACC / vectorObjeto.at(vectorObjeto.at(++contador_posicao));
  //      contador_posicao++;
  //      printf("Valor do acumulador: %d\n", ACC);
  //      break;
  //    
  //    case JMP:
  //      linker = vectorObjeto.at(++contador_posicao);
  //      contador_posicao = linker;
  //      printf("Valor do acumulador: %d\n", ACC);
  //      break;
  //    
  //    case JMPN:
  //      if(ACC < 0){
  //        linker = vectorObjeto.at(++contador_posicao);
  //        contador_posicao = linker;
  //      }else{
  //        contador_posicao = contador_posicao + 2;
  //      }
  //      printf("Valor do acumulador: %d\n", ACC);
  //      break;
  //    
  //    case JMPP:
  //      if(ACC > 0){
  //        linker = vectorObjeto.at(++contador_posicao);
  //        contador_posicao = linker;
  //      }else{
  //        contador_posicao = contador_posicao + 2;
  //      }
  //      printf("Valor do acumulador: %d\n", ACC);
  //      break;
  //    
  //    case JMPZ:
  //      if(ACC == 0){
  //        linker = vectorObjeto.at(++contador_posicao);
  //        contador_posicao = linker;
  //      }else{
  //        contador_posicao = contador_posicao + 2;
  //      }
  //      printf("Valor do acumulador: %d\n", ACC);
  //      break;
  //    
  //    case COPY:
  //      vectorObjeto.at(vectorObjeto.at(contador_posicao + 2)) = vectorObjeto.at(vectorObjeto.at(contador_posicao + 1));
  //      memoria[0] = vectorObjeto.at(contador_posicao + 2);
  //      memoria[1] = vectorObjeto.at(vectorObjeto.at(contador_posicao + 1));
  //      contador_posicao = contador_posicao + 3;
//
  //      printf("Endereço de Memória: %d\n", memoria[0]);
  //      printf("Valor de Memória: %d\n", memoria[1]);
//
  //      break;
  //    
  //    case LOAD:
  //      ACC = vectorObjeto.at(vectorObjeto.at(++contador_posicao));
  //      contador_posicao++;
  //      printf("Valor do acumulador: %d\n", ACC);
  //      break;
  //    
  //    case STORE:
  //      vectorObjeto.at(vectorObjeto.at(++contador_posicao)) = ACC;
  //      memoria[0] = vectorObjeto.at(contador_posicao);
  //      memoria[1] = ACC;
  //      contador_posicao++;
  //      break;
//
  //    case INPUT:
  //      cout << "Favor inserir um valor numérico: ";
  //      cin >> linker;
  //      vectorObjeto.at(vectorObjeto.at(++contador_posicao)) = linker;
  //      memoria[0] = vectorObjeto.at(contador_posicao);
  //      memoria[1] = linker;
  //      contador_posicao++;
//
  //      printf("Endereço de Memória: %d\n", memoria[0]);
  //      printf("Valor de Memória: %d\n", memoria[1]);
  //      break;
//
  //    case OUTPUT:
  //      cout << "O valor de saída é:" << vectorObjeto.at(vectorObjeto.at(++contador_posicao)) << endl;
  //      contador_posicao++;
  //      printf("Valor do acumulador: %d\n", ACC);
  //      break;
//
  //    default:
  //      break;
  //  }
  //}
}