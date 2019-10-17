#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <string.h>
#include "Simulador.hpp"
using namespace std;

void Simulador(string NomeArqObjeto){

  ifstream Arquivo; //ponteiro arquivo
  string linha; // linha do arquivo objeto
  //vector<string> linha_objeto; // vector para códigos (char)
  vector<int> int_linha_objeto; // vector para códigos (int)

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
    while (iss)
    {
      string subs;
      int subs_int;
      iss >> subs;
      //cout << subs << endl;
      //linha_objeto.push_back(subs);
      if (subs != "OO"){
        subs_int = stoi(subs);
        int_linha_objeto.push_back(subs_int);
      }else{
        continue;
      }
    }
    for (int i = 0; i < (int_linha_objeto.size()); i++){
      cout << int_linha_objeto[i];
    }
  }

  //while(int_linha_objeto.at(contador_posicao) != STOP){
  //  switch (int_linha_objeto.at(contador_posicao)){
  //    case ADD:
  //      ACC = ACC + int_linha_objeto.at(int_linha_objeto.at(++contador_posicao));
  //      contador_posicao++;
  //      printf("Valor do acumulador: %d\n", ACC);
  //      break;
  //    
  //    case SUB:
  //      ACC = ACC - int_linha_objeto.at(int_linha_objeto.at(++contador_posicao));
  //      contador_posicao++;
  //      printf("Valor do acumulador: %d\n", ACC);
  //      break;
  //    
  //    case MUL:
  //      ACC = ACC * int_linha_objeto.at(int_linha_objeto.at(++contador_posicao));
  //      contador_posicao++;
  //      printf("Valor do acumulador: %d\n", ACC);
  //      break;
  //    
  //    case DIV:
  //      ACC = ACC / int_linha_objeto.at(int_linha_objeto.at(++contador_posicao));
  //      contador_posicao++;
  //      printf("Valor do acumulador: %d\n", ACC);
  //      break;
  //    
  //    case JMP:
  //      linker = int_linha_objeto.at(++contador_posicao);
  //      contador_posicao = linker;
  //      printf("Valor do acumulador: %d\n", ACC);
  //      break;
  //    
  //    case JMPN:
  //      if(ACC < 0){
  //        linker = int_linha_objeto.at(++contador_posicao);
  //        contador_posicao = linker;
  //      }else{
  //        contador_posicao = contador_posicao + 2;
  //      }
  //      printf("Valor do acumulador: %d\n", ACC);
  //      break;
  //    
  //    case JMPP:
  //      if(ACC > 0){
  //        linker = int_linha_objeto.at(++contador_posicao);
  //        contador_posicao = linker;
  //      }else{
  //        contador_posicao = contador_posicao + 2;
  //      }
  //      printf("Valor do acumulador: %d\n", ACC);
  //      break;
  //    
  //    case JMPZ:
  //      if(ACC == 0){
  //        linker = int_linha_objeto.at(++contador_posicao);
  //        contador_posicao = linker;
  //      }else{
  //        contador_posicao = contador_posicao + 2;
  //      }
  //      printf("Valor do acumulador: %d\n", ACC);
  //      break;
  //    
  //    case COPY:
  //      int_linha_objeto.at(int_linha_objeto.at(contador_posicao + 2)) = int_linha_objeto.at(int_linha_objeto.at(contador_posicao + 1));
  //      memoria[0] = int_linha_objeto.at(contador_posicao + 2);
  //      memoria[1] = int_linha_objeto.at(int_linha_objeto.at(contador_posicao + 1));
  //      contador_posicao = contador_posicao + 3;
//
  //      printf("Endereço de Memória: %d\n", memoria[0]);
  //      printf("Valor de Memória: %d\n", memoria[1]);
//
  //      break;
  //    
  //    case LOAD:
  //      ACC = int_linha_objeto.at(int_linha_objeto.at(++contador_posicao));
  //      contador_posicao++;
  //      printf("Valor do acumulador: %d\n", ACC);
  //      break;
  //    
  //    case STORE:
  //      int_linha_objeto.at(int_linha_objeto.at(++contador_posicao)) = ACC;
  //      memoria[0] = int_linha_objeto.at(contador_posicao);
  //      memoria[1] = ACC;
  //      contador_posicao++;
  //      break;
//
  //    case INPUT:
  //      cout << "Favor inserir um valor numérico: ";
  //      cin >> linker;
  //      int_linha_objeto.at(int_linha_objeto.at(++contador_posicao)) = linker;
  //      memoria[0] = int_linha_objeto.at(contador_posicao);
  //      memoria[1] = linker;
  //      contador_posicao++;
//
  //      printf("Endereço de Memória: %d\n", memoria[0]);
  //      printf("Valor de Memória: %d\n", memoria[1]);
  //      break;
//
  //    case OUTPUT:
  //      cout << "O valor de saída é:" << int_linha_objeto.at(int_linha_objeto.at(++contador_posicao)) << endl;
  //      contador_posicao++;
  //      printf("Valor do acumulador: %d\n", ACC);
  //      break;
//
  //    default:
  //      break;
  //  }
  //}
}