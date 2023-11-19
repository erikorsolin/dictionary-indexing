#include <iostream>
#include <string>
#include <fstream>
#include "trie.h"

using namespace std;
using namespace structures;

/// @brief Essa função lê um arquivo dado, guarda as 
/// informações em um vetor e retorna o ponteiro desse vetor
/// @param filename Nome do arquivo que queremos transformar
/// em vetor de caracteres
/// @return Retorna um ponteiro para o buffer alocado em memória
char * arquivo_para_vetor(string filename) {
    
    // Abre o arquivo
    ifstream myfile;
    myfile.open(filename);
    // Pega o ponteiro do buffer
    filebuf* pbuf = myfile.rdbuf();

    // Pega o tamanho do buffer
    size_t size = pbuf->pubseekoff (0,myfile.end,myfile.in);
    pbuf->pubseekpos (0,myfile.in);

    // Aloca memória para os caracteres
    char* buffer=new char[size];

    // Le os caracteres
    pbuf->sgetn (buffer,size);

    // Fecha o arquivo
    myfile.close();

    return buffer;
}

Trie<char> * montaTrie(char * buffer) {

    Trie<char> * dictTrie = new Trie<char>();
    
    char char_atual = buffer[0];
    int tamanho_buffer = string(buffer).size();
    
    int i = 0;
    int count = 0;
    while (i < tamanho_buffer) {
        if (char_atual == '[') {
            int posicao = i;
            string temp = string();
            char_atual = buffer[++i];
            while (char_atual != ']' && i < tamanho_buffer) {
                temp.push_back(char_atual);
                char_atual = buffer[++i];
            }
            while (char_atual != 10 && i < tamanho_buffer) {
                char_atual = buffer[++i];
            }
            dictTrie->insert(temp, (i - posicao), posicao);
        }
        // Le o próximo caractere
        char_atual = buffer[++i];
    }
    return dictTrie;
}

int main() {
    
    string filename;
    string word;

    cin >> filename;  // entrada

    char * buffer = arquivo_para_vetor(filename);
    structures::Trie<char> * arvore = montaTrie(buffer);
    
    while (1) {  // leitura das palavras ate' encontrar "0"
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        arvore->isPrefix(word);
    }

    return 0;
}
