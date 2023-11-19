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
    ~Trie() {
        delete root;
    }

    void insert(const std::string& word, int comprimento, int posicao) {
        // Caso a árvore já contenha a palavra, não precisamos inserir
        if (contains(word)) {
            return;
        }

        NoTrie *node = root;
        
        int i = 0;
        for (char letter = word[i]; i < static_cast<int>(word.length()); letter = word[++i]) {
            bool found_in_child = false;

            if (node->filhos[letter-97] != nullptr) {
                node->filhos[letter-97]->contador++;
                node = node->filhos[letter-97];
                found_in_child = true;
            }

            // Caso não tenhamos encontrado, acrescentamos a letra ao
            // vetor de filhos e continuamos o processo
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

    void isPrefix(string word) {
        NoTrie * node = root;

        int i = 0;
        for (char letter = word[i]; i < static_cast<int>(word.length()); letter = word[++i]) {
            if (node->filhos[letter-97] != nullptr) {
                node = node->filhos[letter-97];
            } else {
                cout << word << " is not prefix" << endl;
                break;
            }
            if (i == word.length() - 1) {
                cout << word << " is prefix of " << node->contador << " words" << endl;
                if (node->comprimento) {
                    cout << word << " is at " << "(" << node->posicao << "," << node->comprimento << ")" << endl;
                }
            }
        }
    }

    bool contains(const std::string& word) const {
        bool resultado = false;

        if (empty()) {
            return resultado;
        }

        NoTrie * node = root;
        
        int i = 0;
        for (char letter = word[i]; i < word.length(); letter = word[++i]) {
            if (node->filhos[letter-97] != nullptr) {
                node = node->filhos[letter-97];
            } else {
                break;
            }
            if (i == word.length() -1 && node->comprimento) {
                resultado == true;
            }
        }

        return resultado;
    }

    bool empty() const {
        return static_cast<int>(size()) == 0;
    }

    std::size_t size() const {
        return size_;
    }

private:
    struct NoTrie {
        NoTrie() {};
        
        explicit NoTrie(char& letra) {
            setLetra(letra);
        }

        ~NoTrie() {
            clear();
        }

        void clear() {
            for (int i = 0; i < 26; i++) {
                if (this->filhos[i] != nullptr) {
                    delete this->filhos[i];
                }
            }
        };

        void setLetra(char& nova_letra) {
            this->letra = nova_letra;
        }

        void setPosicao(int& nova_posicao) {
            this->posicao = nova_posicao;
        }

        void setComprimento(int& novo_comprimento) {
            this->comprimento = novo_comprimento;
        }

        char           letra;  // Primeiro nó não tem letra
        NoTrie        *filhos[26] = {};
        unsigned long  contador = 1;  // Representa a quantidade de sufixos que esse nodo tem
        unsigned long  posicao = 0;
        unsigned long  comprimento = 0;  // se maior que zero, indica último caracter de uma palavra
    };

    NoTrie* root = new NoTrie();
    std::size_t size_{0};  // Representa o número de palavras na arvore
};

}  // namespace structures

#endif