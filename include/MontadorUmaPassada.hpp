#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

struct  TabelaSimbolos {
bool definido = false;
vector<int> LugaresUsados;
// Esse campo define se ele é um endereco ou uma constante
// 0 - Label
// 1 - constante
// 2 - dado (Space)
int Tipo;
int Valor;
};


string MontadorUmaPassada(string NomeArquivo);
bool ValidaToken(string token);
bool ValidaLabel(string Label);
bool VerificaHexa(string Numero);
int ValidaInstrucao(string instrucao);
void PadronizaSection(string NomeArquivo);