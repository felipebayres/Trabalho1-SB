#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <sstream>
#include <bits/stdc++.h> 
using namespace std;
void PreProcessamento(string NomeArquivo);
string RetiraComentarios(string linha);
bool VerificaDiretiva(string linha);
void DiretivasEQU(string linha);
