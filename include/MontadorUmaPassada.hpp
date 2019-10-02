#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

class Tabela{
public:
    string Simbolo;
    int valor;
    bool definido = false;
    vector<int> ListaAparicoes;
};


void MontadorUmaPassada(string NomeArquivo);
bool ValidaToken(string token);
bool ValidaLabel(string Label);
bool VerificaHexa(string Numero);
int ValidaInstrucao(string instrucao);