#ifndef STRUCTURES_TRIE_H
#define STRUCTURES_TRIE_H

#include <cstdint>
#include <stdexcept>
#include <string>

using namespace std;

namespace structures {

template<typename T>
class Trie {
public:
    /// @brief Destrutor, antes do Trie ser desalocada
    /// esse método é chamado
    ~Trie() {
        delete root;
    }

    /// @brief Insere um elemento novo na Trie
    /// @param word Palavra a ser inserida
    /// @param comprimento Comprimento da descricao da palavra
    /// @param posicao Posicao em que a palavra se encontra no dicicionario
    void insert(const std::string& word, int comprimento, int posicao) {
        // Caso a árvore já contenha a palavra, não precisamos inserir
        if (contains(word)) {
            return;
        }

        NoTrie *node = root;
        
        // Laco para alocacao de novos nodos, caso seja necessario
        int i = 0;
        for (char letter = word[i]; i < static_cast<int>(word.length()); letter = word[++i]) {
            bool found_in_child = false;

            // Percorremos o caminho que a palavra faria caso ela estivesse no dicionario.
            if (node->filhos[letter-97] != nullptr) {
                node->filhos[letter-97]->contador++;
                node = node->filhos[letter-97];
                found_in_child = true;
            }

            // Caso uma de suas letras nao esteja alocada, realizamos a sua alocacao
            if (!found_in_child) {
                NoTrie * new_node = new NoTrie(letter);
                node->filhos[letter - 97] = new_node;
                node = new_node;
            }
        }
        node->setComprimento(comprimento);
        node->setPosicao(posicao);
        ++size_;
    }

    /// @brief Checa se uma dada palavra e prefixo de outra na trie
    /// @param word Palavra ser checada se e prefixo
    void isPrefix(string word) {
        NoTrie * node = root;

        int i = 0;
        for (char letter = word[i]; i < static_cast<int>(word.length()); letter = word[++i]) {
            // Percorremos o caminho que a palavra faria caso ela estivesse no dicionario.
            // Caso uma de suas letras nao esteja alocada significa que ela nao está na Trie
            if (node->filhos[letter-97] != nullptr) {
                node = node->filhos[letter-97];
            } else {
                cout << word << " is not prefix" << endl;
                break;
            }

            // Caso tenhamos chegado na ultima letra da palavra revelamos de quantas palavras
            // ela e prefixo e caso ela esteja no dicionario tambem revelamos onde ela esta
            // e o comprimento de sua descricao
            if (i == word.length() - 1) {
                cout << word << " is prefix of " << node->contador << " words" << endl;
                if (node->comprimento) {
                    cout << word << " is at " << "(" << node->posicao << "," << node->comprimento << ")" << endl;
                }
            }
        }
    }

    /// @brief Metodo que checa se a trie contem uma dada palavra
    /// @param word Palavra que desejamos checar se nossa trie contem
    /// @return Valor logico, verdadeiro caso contenha, falso caso nao contenha
    bool contains(const std::string& word) const {
        bool resultado = false;

        // Caso a trie esteja vazia, a palavra nao esta no dicionario
        if (empty()) {
            return resultado;
        }

        NoTrie * node = root;
        
        int i = 0;
        for (char letter = word[i]; i < word.length(); letter = word[++i]) {
            // Percorre o caminho que a palavra teria caso ela estivesse no dicionario.
            // Caso uma de suas letras nao estiver alocada significa que a palavra nao
            // esta no dicionario 
            if (node->filhos[letter-97] != nullptr) {
                node = node->filhos[letter-97];
            } else {
                break;
            }
            // Caso seja o ultimo NoTrie, se seu comprimento for diferente de zero
            // quer dizer que nosso dicionario contem a palavra
            if (i == word.length() -1 && node->comprimento) {
                resultado == true;
            }
        }

        return resultado;
    }

    /// @brief Função que verifica se a Trie está vazia
    /// @return Valor lógico indicando se a Trie está vazia.
    /// == 0 -> Trie vazia, != 0 -> Trie contém elementos
    bool empty() const {
        return static_cast<int>(size()) == 0;
    }

    /// @brief Função que retorna a quantidade de palavras
    /// já armazenada na Trie
    /// @return Variavel do tipo size_t indicando o a
    /// quantidade de palavras já armazenada na Trie
    std::size_t size() const {
        return size_;
    }

private:
    struct NoTrie {
        /// @brief Construtor padrao, sem letra
        NoTrie() {};
        
        /// @brief Construtor explicito
        /// @param letra Letra que o NoTrie contera
        explicit NoTrie(char& letra) {
            setLetra(letra);
        }

        /// @brief Destrutor, antes do NoTrie ser desalocado
        /// esse método é chamado
        ~NoTrie() {
            clear();
        }

        /// @brief Função que limpa todos os ponteiros de um NoTrie
        void clear() {
            for (int i = 0; i < 26; i++) {
                if (this->filhos[i] != nullptr) {
                    delete this->filhos[i];
                }
            }
        };

        /// @brief Setter para substituir o valor da letra do NoTrie
        /// @param nova_letra Nova letra que desejamos guardar no
        /// NoTrie
        void setLetra(char& nova_letra) {
            this->letra = nova_letra;
        }

        /// @brief Setter para substituir o valor da posicao do NoTrie
        /// @param nova_posicao Nova posicao que desejamos guardar no
        /// NoTrie
        void setPosicao(int& nova_posicao) {
            this->posicao = nova_posicao;
        }

        /// @brief Setter para substituir o valor do comprimento  do NoTrie
        /// @param novo_comprimento Novo comprimento que desejamos guardar no
        /// NoTrie
        void setComprimento(int& novo_comprimento) {
            this->comprimento = novo_comprimento;
        }

        char           letra;  // Primeiro nó não tem letra
        NoTrie        *filhos[26] = {};  // Todos os ponteiros comecam como nulos
        unsigned long  contador = 1;  // Representa a quantidade de sufixos que esse nodo tem
        unsigned long  posicao = 0;
        unsigned long  comprimento = 0;  // se maior que zero, indica último caracter de uma palavra
    };

    NoTrie* root = new NoTrie();  // A Trie comeca apenas com a raiz, a qual nao contem letra
    std::size_t size_{0};  // Representa o número de palavras na arvore
};

}  // namespace structures

#endif