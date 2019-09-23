#include "PreProcessamento.hpp"
using namespace std;
int main (int argc, char** argv) {
    string NomeArquivo;
    if (argc < 2){
        cout << "Insira o nome do arquivo a ser usado!";
        return 0;
    }   
    NomeArquivo = argv[1];
    PreProcessamento(NomeArquivo);


    return 0;
}