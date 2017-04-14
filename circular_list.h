// Copyright 2017 Letícia do Nascimento

#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

/**
 * @brief      Implementação de uma Estrutura de Dados do tipo Lista Circular.
 *             Organização de dados linear e dinâmica, similar a Lista Encadeada -
 *             Com a diferença que o último elemento aponta para o primeiro.
 *
 * @tparam     T     Parâmetro genérico de Template
 */

template<typename T>
class CircularList {
 public:
    CircularList();
    ~CircularList();

    void clear();  // limpar lista

    void push_back(const T& data);  // inserir no fim
    void push_front(const T& data);  // inserir no início
    void insert(const T& data, std::size_t index);  // inserir na posição
    void insert_sorted(const T& data);  // inserir em ordem

    T& at(std::size_t index);  // acessar em um indice (com checagem de limites)
    const T& at(std::size_t index) const;  // versão const do acesso ao indice

    T pop(std::size_t index);  // retirar da posição
    T pop_back();  // retirar do fim
    T pop_front();  // retirar do início
    void remove(const T& data);  // remover dado específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // lista contém determinado dado?
    std::size_t find(const T& data) const;  // posição de um item na lista

    std::size_t size() const;  // tamanho da lista

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
 *   Construtor padrão da classe CircularList.
 */
template <typename T>
CircularList<T>::CircularList() {
    head = new Node((T)0, nullptr);
    head->next(head);
    size_ = 0;
}

/**
 *   Destrutor padrão da classe CircularList.
 */
template <typename T>
CircularList<T>::~CircularList() {
    clear();
    delete head;
}

/**
 *   Faz uma limpeza da lista encadeada (CircularList).
 */
template <typename T>
void CircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

/**
 *   Insere um elemento no fim da lista (CircularList).
 */
template <typename T>
void CircularList<T>::push_back(const T& data) {
    if (empty())
        return push_front(data);

    Node *previous = head->next();

    for (int i = 0; i < size_-1; ++i) {
        previous = previous->next();
    }

    previous->next(new Node(data, head));
    size_++;
}

/**
 *   Insere um elemento no início da lista (CircularList).
 */
template <typename T>
void CircularList<T>::push_front(const T& data) {
      head->next(new Node(data, head->next()));
      size_++;
}

/**
 *   Insere um elemento num determinado index da lista (CircularList).
 */
template <typename T>
void CircularList<T>::insert(const T& data, std::size_t index) {
    if (index > size_)
        throw std::out_of_range("Índice inválido!");

    if (index == 0)
        return push_front(data);

    if (index == size_)
        return push_back(data);

    Node *anterior = head->next();

    for (int i = 0; i < index-1; ++i) {
        anterior = anterior->next();
    }

    anterior->next(new Node(data, anterior->next()));
    ++size_;
}

/**
 *   Insere um elemento em ordem na lista (CircularList).
 */
template <typename T>
void CircularList<T>::insert_sorted(const T& data) {
    if (empty())
        return push_front(data);

    Node* atual = head->next();
    int index = 0;

    while (index < size_ && data > atual->data()) {
        atual = atual->next();
        ++index;
    }

    insert(data, index);
}

/**
 *   Retorna o dado num determinado index, com checagem de limites (CircularList).
 */
template <typename T>
T& CircularList<T>::at(std::size_t index) {
    if (empty())
        throw std::out_of_range("Lista está vazia!");

    if (index > size_ - 1)
        throw std::out_of_range("Índice inválido!");

    Node* current = head->next();
    if (index == 0)
        return current->data();

    for (int i = 0; i < index; i++)
      current = current->next();

    return current->data();
}

/**
 *   Retorna o dado num determinado index, sem chegagem de limites (CircularList).
 */
template <typename T>
const T& CircularList<T>::at(std::size_t index) const {
    Node* current = head->next();

    if (index == 0)
        return current->data();

    for (int i = 0; i < index; i++)
      current = current->next();

    return current->data();
}

/**
 *   Retira um elemento num index da lista (CircularList).
 */
template <typename T>
T CircularList<T>::pop(std::size_t index) {
    if (index > size_ - 1)
        throw std::out_of_range("Índice inválido!");

    if (empty())
        throw std::out_of_range("Lista vazia!");

    if (index == 0)
        return pop_front();

    Node *previous, *current;
    T return_;
    previous = head->next();

    for (int i = 0; i < index-1; ++i) {
        previous = previous->next();
    }

    current = previous->next();
    return_ = current->data();
    previous->next(current->next());
    size_--;
    delete current;
    return return_;
}

/**
 *   Retira um elemento do fim da lista (CircularList).
 */
template <typename T>
T CircularList<T>::pop_back() {
    if (empty())
        throw std::out_of_range("Lista está vazia!");

    if (size_ == 1)
        return pop_front();

    return pop(size_-1);
}

/**
 *   Retira um elemento do início da lista (CircularList).
 */
template <typename T>
T CircularList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("Lista vazia!");

    T data = head->next()->data();
    Node *aux = head->next()->next();
    delete head->next();
    head->next(aux);
    size_--;
    return data;
}

/**
 *   Remove um dado específico da lista (CircularList).
 */
template <typename T>
void CircularList<T>::remove(const T& data) {
    std::size_t test = find(data);

    if (test != size_)
        pop(test);
}

/**
 *   Verifica se a lista está vazia (CircularList).
 */
template<typename T>
bool CircularList<T>::empty() const {
    return size_ == 0;
}

/**
 *   Verifica se a lista contém determinado dado (CircularList).
 */
template<typename T>
bool CircularList<T>::contains(const T& data) const {
    if (find(data) != size_)
        return true;
    return false;
}

/**
 *   Retorna a posição de um dado na lista (CircularList).
 */
template<typename T>
std::size_t CircularList<T>::find(const T& data) const {
    if (empty())
        throw std::out_of_range("Lista está vazia!");

    std::size_t i;
    std::size_t index = size_;
    Node* current = head->next();

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

/**
 *   Verifica e retorna o tamanho da lista encadeada (CircularList).
 */
template<typename T>
std::size_t CircularList<T>::size() const {
    return size_;
}

}  // namespace structures

#endif
