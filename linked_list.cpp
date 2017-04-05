//  Copyright 2017 Letícia do Nascimento  

#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ exception


namespace structures {

    /**
     * @brief      Implementação de uma Estrutura de Dados do tipo Lista Encadeada
     *			   Organização de dados linear e dinâmica, composta por células que
     *             apontam para o próximo elemento da lista.
     *
     * @tparam     T     Parâmetro genérico de Template
     */

    template<typename T>
    class LinkedList {
    public:
        LinkedList(); // construtor padrão 
        ~LinkedList();  // destrutor
        void clear();  // limpar lista
        void push_back(const T& data);  // inserir no fim
        void push_front(const T& data);  // inserir no início
        void insert(const T& data, std::size_t index);   // inserir na posição
        void insert_sorted(const T& data);  // inserir em ordem
        T& at(std::size_t index);  // acessar um elemento na posição index
        T pop(std::size_t index);  // retirar da posição
        T pop_back();  // retirar do fim
        T pop_front();  // retirar do início
        void remove(const T& data);  // remover específico
        bool empty() const;  // lista vazia
        bool contains(const T& data) const;  // contém
        std::size_t find(const T& data) const;  // posição do dado
        std::size_t size() const;  // tamanho da lista
    private:
        class Node { // Elemento
        public:
            Node(const T& data):
                data_{data}
            {}
    
            Node(const T& data, Node* next):
                data_{data},
                next_{next}
            {}
    
            T& data() { // getter: dado
                return data_;
            }

            const T& data() const { // getter const: dado
                return data_;
            }

            Node* next() { // getter: próximo
                return next_;
            }

            const Node* next() const { // getter const: próximo
                return next_;
            }

            void next(Node* node) { // setter: próximo
                next_ = node;
            }
        private:
            T data_;
            Node* next_{nullptr};
        };

        Node* end() { // último nodo da lista
            auto it = head;
            for (auto i = 1u; i < size(); ++i) {
                it = it->next();
            }
            return it;
        }

        Node* head{nullptr};
        std::size_t size_{0u};
};

}  // namespace structures

#endif

//  construtor

template <typename T>
structures::LinkedList<T>::LinkedList():
    head{nullptr},
    size_{0u}
{}

template<typename T>
void LinkedList<T>::delete_contents() {
    auto current = head;
    while (current != nullptr) {
        auto prev = current;
        current = current -> next();
        delete prev;
    }
}

//  destrutor

template<typename T>
structures::LinkedList<T>::~LinkedList() {
    auto current = head;
    while (current != nullptr) {
        auto prev = current;
        current = current -> next();
        delete prev;
    }
}

//  limpa lista

template<typename T>
void structures::LinkedList<T>::clear() {
    auto current = head;
    while (current != nullptr) {
        auto prev = current;
        current = current -> next();
        delete prev;
    }
    head = nullptr;
    size_ = 0u;
}

//  verifica se a lista está vazia

template<typename T>
bool structures::LinkedList<T>::empty() const {
    return (size_ == 0);
}

//  retorna o tamanho da lista  

template<typename T>
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}

//  inserir no fim

template<typename T>
void structures::LinkedList<T>::push_back() {
    insert(data, size_ );
}

// insere numa posição específica

template<typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
    if (index < 0)
        throw std::out_of_range("Índice inválido");

    std::size_t i = 0;
    Node* atual = head;
    while (i < index - 1) {
        i++;
        atual = atual -> next();
    }
   Node *novo = new Node(data,atual->next());
   atual -> next(novo);
   size_++;
}

//  insere no começo

template<typename T>
void structures::LinkedList<T>::push_front() {
    insert(data, 0);
}

//  insere em ordem

template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    if (empty())
        push_front(data);

    std::size_t i = 0;
    Node* atual = head;
    while (atual -> next() != nullptr && atual -> data() < data) {
        i++;
        atual = atual -> next();
    }
   insert(data, i);
}

//  acessar um elemento pelo índice

template<typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
    if (index < 0 || index > size_)
        throw std::out_of_range("Índice inválido!");
    if (empty())
        throw std::out_of_range("Lista vazia!");

    std::size_t i = 0;
    Node* atual = head;
    while (i < index) {
        i++;
        atual = atual -> next();
    }
   return atual -> data();
}

//  retira um elemento no indice

template<typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
    if (index < 0 || index > size_)
        throw std::out_of_range("Índice inválido!");
    if (empty())
        throw std::out_of_range("Lista vazia!");

    std::size_t i = 0;
    Node* atual = head;
    T retorno;
    while (i < index) {
        i++;
        atual = atual -> next();
    }
    retorno = atual -> data();
    delete(atual);
    size_--;
   return retorno;
}

//  retira o ultimo elemento

template<typename T>
T structures::LinkedList<T>::pop_back(std::size_t index) {
    return pop(size_);
}

//  retira o primeiro elemento

template<typename T>
T structures::LinkedList<T>::pop_front(std::size_t index) {
    return pop(0);
}

// remove um item específico

template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
    if (!contains())
        throw std::out_of_range("Elemento inexistente.");

    std::size_t i = 0;
    Node* atual = head;
    while (atual -> != data) {
        i++;
        atual = atual -> next();
    }
    delete(find(data));
}

//  verifica se a contém um dado específico

template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
    std::size_t i = 0;
    Node* atual = head;
    while (atual -> data() != data) {
        i++;
        atual = atual -> next();
    }
    if (atual != nullptr)
        return 1;
   return 0;
}

//  retorna a posição de um dado específico

template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
    if (empty())
        throw std::out_of_range("Lista vazia!");
   
    if (!contains())
        throw std::out_of_range("Elemento inexistente.");

    std::size_t i = 0;
    Node* atual = head;
    while (atual -> data() != data) {
        i++;
        atual = atual -> next();
    }
   return i;
}
