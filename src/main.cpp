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

/// @brief Essa função recebe um vetor de caractéres que corresponde a um
/// dicionário contendo palavras e definições. Esse dicionário é convertido
/// para uma Trie e então retornado
/// @param buffer Vetor de caracteres correspondente ao dicionário que
/// desejamos converter
/// @return Retorna uma estrutura de dados do tipo Trie<char> contendo o
/// dado dicionário
Trie<char> * montaTrie(char * buffer) {

    Trie<char> * dictTrie = new Trie<char>();
    char char_atual = buffer[0];
    int tamanho_buffer = string(buffer).size();

    int i = 0;
    int count = 0;
    while (i < tamanho_buffer) {
        // Caso o caractere atual seja um "[" consideramos que irá
        // iniciar uma palavra nova do dicionário
        if (char_atual == '[') {
            int posicao = i;
            string temp = string();
            char_atual = buffer[++i];

            // Percorremos o buffer adicionando as letras da palavra
            // a variável "temp" até encontrar-mos um "]" indicando
            // que a palavra acabou, ou até o tamanho do buffer ser
            // ultrapassado
            while (char_atual != ']' && i < tamanho_buffer) {
                temp.push_back(char_atual);
                char_atual = buffer[++i];
            }

            // Percorremos o buffer até encontrar uma quebra de linha
            // ou até o tamanho do buffer ser ultrapassado, pois
            // buscamos o fim da descrição da palavra
            while (char_atual != 10 && i < tamanho_buffer) {
                char_atual = buffer[++i];
            }

            // Com a palavra, o comprimento e a posição
            // (Respectivamente "temp, (i-posicao) e posicao")
            // armazenamos a palavra na Trie
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

    char * buffer = arquivo_para_vetor(filename);  // Le o arquivo e o transforma em um vetor
    structures::Trie<char> * arvore = montaTrie(buffer);  // Monta a Trie do dicionario
    
    while (1) {  // leitura das palavras ate' encontrar "0"
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        arvore->isPrefix(word);  // Checa se a palavra recebida e prefixo ou nao
    }

    return 0;
}
