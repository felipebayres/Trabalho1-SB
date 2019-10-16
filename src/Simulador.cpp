#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include "Simulador.hpp"
using namespace std;

void Simulador(string NomeArqObjeto){

  ifstream Arquivo; //ponteiro arquivo
  string linha;
  string espaco = " ";
  vector<int> linha_objeto; // linha do arquivo objeto
  char codigo_char[2];
  int codigo_int;
  char codigo[3];

  int contador_posicao = 0; // PC
  int linker; // auxiliar para saltos
  int ACC = 0;  // registrador acumulador
  int16_t memoria[2]; // memoria simulada

  Arquivo.open(NomeArqObjeto);
    
  if (!Arquivo.is_open()){
    cout << "Não foi possível abrir o arquivo objeto " << NomeArqObjeto << "\n";
    return ;
  }else{
    while(!Arquivo.eof())
    {
      Arquivo.read(codigo_char, 1);
      if (!Arquivo.eof()){
        if(espaco.compare(codigo_char)){   // se for espaço
          Arquivo.read(codigo_char, 1);    // lẽ próxima posição
          if(!espaco.compare(codigo_char) || Arquivo.eof()){
            codigo_int = stoi(string(codigo));
						linha_objeto.push_back(codigo_int);
          } else if(!Arquivo.eof()){
            codigo[1] = codigo_char[0];
						codigo_int = stoi(string(codigo));
						linha_objeto.push_back(codigo_int);
          }
        }else{
          continue;
        }
      }
    }
  }

  while(linha_objeto.at(contador_posicao) != STOP){

    switch (linha_objeto.at(contador_posicao)){
      case ADD:
        ACC = ACC + linha_objeto.at(linha_objeto.at(++contador_posicao));
        contador_posicao++;
        printf("Valor do acumulador: %d\n", ACC);
        break;
      
      case SUB:
        ACC = ACC - linha_objeto.at(linha_objeto.at(++contador_posicao));
        contador_posicao++;
        printf("Valor do acumulador: %d\n", ACC);
        break;
      
      case MUL:
        ACC = ACC * linha_objeto.at(linha_objeto.at(++contador_posicao));
        contador_posicao++;
        printf("Valor do acumulador: %d\n", ACC);
        break;
      
      case DIV:
        ACC = ACC / linha_objeto.at(linha_objeto.at(++contador_posicao));
        contador_posicao++;
        printf("Valor do acumulador: %d\n", ACC);
        break;
      
      case JMP:
        linker = linha_objeto.at(++contador_posicao);
        contador_posicao = linker;
        printf("Valor do acumulador: %d\n", ACC);
        break;
      
      case JMPN:
        if(ACC < 0){
          linker = linha_objeto.at(++contador_posicao);
          contador_posicao = linker;
        }else{
          contador_posicao = contador_posicao + 2;
        }
        printf("Valor do acumulador: %d\n", ACC);
        break;
      
      case JMPP:
        if(ACC > 0){
          linker = linha_objeto.at(++contador_posicao);
          contador_posicao = linker;
        }else{
          contador_posicao = contador_posicao + 2;
        }
        printf("Valor do acumulador: %d\n", ACC);
        break;
      
      case JMPZ:
        if(ACC == 0){
          linker = linha_objeto.at(++contador_posicao);
          contador_posicao = linker;
        }else{
          contador_posicao = contador_posicao + 2;
        }
        printf("Valor do acumulador: %d\n", ACC);
        break;
      
      case COPY:
        linha_objeto.at(linha_objeto.at(contador_posicao + 2)) = linha_objeto.at(linha_objeto.at(contador_posicao + 1));
        memoria[0] = linha_objeto.at(contador_posicao + 2);
        memoria[1] = linha_objeto.at(linha_objeto.at(contador_posicao + 1));
        contador_posicao = contador_posicao + 3;

        printf("Endereço de Memória: %d\n", memoria[0]);
        printf("Valor de Memória: %d\n", memoria[1]);

        break;
      
      case LOAD:
        ACC = linha_objeto.at(linha_objeto.at(++contador_posicao));
        contador_posicao++;
        printf("Valor do acumulador: %d\n", ACC);
        break;
      
      case STORE:
        linha_objeto.at(linha_objeto.at(++contador_posicao)) = ACC;
        memoria[0] = linha_objeto.at(contador_posicao);
        memoria[1] = ACC;
        contador_posicao++;
        break;

      case INPUT:
        cout << "Favor inserir um valor numérico: ";
        cin >> linker;
        linha_objeto.at(linha_objeto.at(++contador_posicao)) = linker;
        memoria[0] = linha_objeto.at(contador_posicao);
        memoria[1] = linker;
        contador_posicao++;

        printf("Endereço de Memória: %d\n", memoria[0]);
        printf("Valor de Memória: %d\n", memoria[1]);
        break;

      case OUTPUT:
        cout << "O valor de saída é:" << linha_objeto.at(linha_objeto.at(++contador_posicao)) << endl;
        contador_posicao++;
        printf("Valor do acumulador: %d\n", ACC);
        break;

      default:
        break;
    }
}