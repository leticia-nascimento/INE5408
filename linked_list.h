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
    LinkedList();  // construtor padrão
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
    class Node {  // Elemento
     public:
        explicit Node(const T& data) : data_{data}{}
        Node(const T& data, Node* next) : data_{data},next_{next}{}
        T& data() { return data_; }  // getter: dado
        const T& data() const { return data_; }  // getter const: dado
        Node* next() { return next_; }  // getter: próximo
        const Node* next() const { return next_; }  // getter const: próximo 
        void next(Node* node) { next_ = node; }  // setter: próximo

     private:
        T data_;
        Node* next_{nullptr};
    };

    // último nodo da lista
    Node* end() {
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

// Construtor
template <typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    size_ = 0;
}

// Destrutor
template<typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

//  limpa lista
template<typename T>
void LinkedList<T>::clear() {
    while(!empty()) {
        pop_front();
    }
}

//  verifica se a lista está vazia
template<typename T>
bool LinkedList<T>::empty() const {
    return size_ == 0;
}

//  retorna o tamanho da lista
template<typename T>
std::size_t LinkedList<T>::size() const {
    return size_;
}

//  inserir no fim
template<typename T>
void LinkedList<T>::push_back(const T& data) {
    insert(data, size_);
}

// insere numa posição específica
template<typename T>
void LinkedList<T>::insert(const T& data, std::size_t index) {
    if (index < 0 || index > size())
        throw std::out_of_range("Índice inválido");
        
    if (index == 0)
        return push_front(data);
    
    Node* novo = new Node(data);
    if (novo == nullptr)
        throw std::out_of_range("Lista cheia.");
    
    Node* atual = head;
    for (int i = 0; i < index - 1; i++) {
      atual = atual->next();
    }
    novo->next(atual->next());
    atual->next(novo);
    size_++;
}

//  insere no começo
template<typename T>
void LinkedList<T>::push_front(const T& data) {
    Node* first_node = new Node(data);
    if (first_node == nullptr)
        throw std::out_of_range("Lista está cheia.");

    first_node->next(head);
    head = first_node;
    size_++;
}

//  insere em ordem
template<typename T>
void LinkedList<T>::insert_sorted(const T& data) {
    if (empty()){
        push_front(data);
    } else {
        std::size_t i = 0;
        Node* current = head;
        for (i = 0; i < size_ && data > current->data(); i++) {
          current = current->next();
        }
        insert(data, i);
    }
}

//  acessar um elemento pelo índice
template<typename T>
T& LinkedList<T>::at(std::size_t index) {
    Node* current = head;
    if (index > size_ - 1)
        throw std::out_of_range("Índice inválido!");
    
    if (index == 0)
        return current->data();
    
    for (int i = 0; i < index; i++) {
      current = current->next();
    }
    return current->data();
}

//  retira um elemento no indice
template<typename T>
T LinkedList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("Lista vazia!");

    if (index > (size_ - 1))
        throw std::out_of_range("Índice inválido!");

    if (index == 0) 
        return pop_front();

    std::size_t i = 0;
    Node* anterior = head;
    for (i = 0; i < index - 1; i++) {
      anterior = anterior->next();
    }
    Node* atual = anterior->next();
    T retorno = atual->data();
    anterior->next(atual->next());
    size_--;
    delete atual;
    return retorno;
}

//  retira o ultimo elemento
template<typename T>
T LinkedList<T>::pop_back() {
    return pop(size() - 1);
}

//  retira o primeiro elemento
template<typename T>
T LinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("Lista está vazia!");
    }
    Node* anterior = head;
    T out_ = anterior->data();
    head = anterior->next();
    delete anterior;
    size_--;
    return out_;
}

// remove um item específico
template<typename T>
void LinkedList<T>::remove(const T& data) {
    std::size_t test = find(data);
    if (test != size_)
        pop(test);
}

//  verifica se a contém um dado específico
template<typename T>
bool LinkedList<T>::contains(const T& data) const {
    if (find(data) != size_)
        return true;
    return false;
    // return find(data) != size_;
}

//  retorna a posição de um dado específico
template<typename T>
std::size_t LinkedList<T>::find(const T& data) const {
    std::size_t i;
    std::size_t index = size_;
    Node* current = head;

    for (i = 0; i < size_; i++) {
        if (current->data() == data) {
            index = i;
            break;
        }
        if (i != size_)
            current = current->next();
    }
    return index;
}

}  // namespace
#endif
