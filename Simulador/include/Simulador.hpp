#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <sstream>
#include <stdint.h>
#include <bits/stdc++.h>

// OPCODES do Assembly inventado:
#define ADD 1
#define SUB 2
#define MUL 3
#define DIV 4
#define JMP 5
#define JMPN 6
#define JMPP 7
#define JMPZ 8
#define COPY 9
#define LOAD 10
#define STORE 11
#define INPUT 12
#define OUTPUT 13
#define STOP 14

using namespace std;

void Simulador(string NomeArqObjeto);

