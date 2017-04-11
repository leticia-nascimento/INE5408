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
    LinkedList();
    ~LinkedList();
    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T& at(std::size_t index);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;

 private:
    class Node {
     public:
        explicit Node(const T& data) : data_{data} { }
        Node(const T& data, Node* next) : data_{data}, next_{next} { }
        T& data() { return data_; }
        const T& data() const { return data_; }
        Node* next() { return next_; }
        const Node* next() const { return next_; }
        void next(Node* node) { next_ = node; }

     private:
        T data_;
        Node* next_{nullptr};
    };

    // último nodo da lista
    Node* end() {
        auto it = head;
        for (auto i = 1u; i < size_; ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

/**
 *   Construtor padrão da classe LinkedList.
 */
template <typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    size_ = 0;
}

/**
 *   Destrutor padrão da classe LinkedList.
 */
template<typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

/**
 *   Faz uma limpeza da lista encadeada LinkedList.
 */
template<typename T>
void LinkedList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

/**
 *   Verifica se a lista encadeada (LinkedList) está vazia.
 */
template<typename T>
bool LinkedList<T>::empty() const {
    return size_ == 0;
}

/**
 *   Verifica e retorna o tamanho da lista encadeada (LinkedList).
 */
template<typename T>
std::size_t LinkedList<T>::size() const {
    return size_;
}

/**
 *   Inserir novo elemento do fim da lista encadeada (LinkedList).
 */
template<typename T>
void LinkedList<T>::push_back(const T& data) {
    insert(data, size_);
}

/**
 *   Inserir novo elemento no índice específico da lista encadeada (LinkedList).
 */
template<typename T>
void LinkedList<T>::insert(const T& data, std::size_t index) {
    Node* novo = new Node(data);
    Node* atual = head;
    if (index < 0 || index > size_)
        throw std::out_of_range("Índice inválido");
    if (index == 0)
        return push_front(data);
    if (novo == nullptr)
        throw std::out_of_range("Lista cheia.");
    for (int i = 0; i < index - 1; i++)
      atual = atual->next();
    novo->next(atual->next());
    atual->next(novo);
    size_++;
}

/**
 * Inserir novo elemento no começo da lista encadeada (LinkedList).
 */
template<typename T>
void LinkedList<T>::push_front(const T& data) {
    Node* first_node = new Node(data);
    if (first_node == nullptr)
        throw std::out_of_range("Lista está cheia.");

    first_node->next(head);
    head = first_node;
    size_++;
}

/**
 *   Insere novo elemento na ordem definida pela lista encadeada (LinkedList).
 */
template<typename T>
void LinkedList<T>::insert_sorted(const T& data) {
    if (empty()) {
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

/**
 *   Retorna um elemento da lista encadeada que está em uma posição específica (LinkedList).
 */
template<typename T>
T& LinkedList<T>::at(std::size_t index) {
    if (index > size_ - 1)
        throw std::out_of_range("Índice inválido!");

    Node* current = head;
    if (index == 0)
        return current->data();

    for (int i = 0; i < index; i++)
      current = current->next();

    return current->data();
}

/**
 *   Remove um elemento da lista encadeada (LinkedList).
 */
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

/**
 *   Remove o último elemento da lista encadeada (LinkedList).
 */
template<typename T>
T LinkedList<T>::pop_back() {
    return pop(size_ - 1);
}

/**
 *   Remove o primeiro elemento da lista encadeada (LinkedList).
 */
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

/**
 *   Remove um item específico da lista encadeada (LinkedList).
 */
template<typename T>
void LinkedList<T>::remove(const T& data) {
    std::size_t test = find(data);
    if (test != size_)
        pop(test);
}

/**
 *   Verifica se a lista encadeada (LinkedList) possui um elemento específico de acordo com o elemento fornecido.
 */ 
template<typename T>
bool LinkedList<T>::contains(const T& data) const {
    if (find(data) != size_)
        return true;
    return false;
    // return find(data) != size_;
}

/**
 *   Retorna o índice de um elemento éspecífico na lista encadeada (LinkedList).
 */
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
}  // namespace structures
#endif
