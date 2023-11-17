#ifndef STRUCTURES_TRIE_H
#define STRUCTURES_TRIE_H

#include <cstdint>
#include <stdexcept>
#include <string>

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
        for (char letter = word[i]; i < word.length(); i++) {
            bool found_in_child = false;

            // Procura pela letra no nodo atual
            for (int j = 0; j < 26; j++) {
                // Caso tenhamos encontrado, incrementamos o contador
                // interno do nodo para indicar que ele é prefixo de
                // mais uma palavra
                if (node->filhos[j] == letter) {
                    node->filhos[j]->contador++;
                    node = node->filhos[j];
                    found_in_child = true;
                    break;
                }
            }
            
            // Caso não tenhamos encontrado, acrescentamos a letra ao
            // vetor de filhos e continuamos o processo
            if (!found_in_child) {
                NoTrie * new_node = NoTrie(letter);
                node->filhos[letter - 97] = new_node;
                node = new_node;
            }
        }
        node->setComprimento(comprimento);
        node->setPosicao(posicao);
        ++size_;
    }

    // Não precisa ser implementado, mas acho bom implementar
    void remove(const T& node_data) {
        if (empty()) {
            throw std::out_of_range("Empty!");
        }
        // Lógica pra excluir
        --size_;
    }

    bool contains(const std::string& word) const {
        bool resultado = false;

        if (empty()) {
            return resultado;
        }

        NoTrie * node = root;
        
        int i = 0;
        for (char letter = word[i]; i < word.length(); i++) {
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
        explicit NoTrie(const char& letra) {
            setLetra(letra);
        }

        ~NoTrie() {
            clear();
        }

        clear() {
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
        NoTrie        *filhos[26];
        unsigned long  contador = 0;  // Representa a quantidade de sufixos que esse nodo tem
        unsigned long  posicao;
        unsigned long  comprimento = 0;  // se maior que zero, indica último caracter de uma palavra
    };

    NoTrie* root = new NoTrie();
    std::size_t size_{0};  // Representa o número de palavras na arvore
};

}  // namespace structures

#endif