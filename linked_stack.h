// Copyright 2017 Letícia do Nascimento

#include <stdexcept>  // C++ exception

namespace structures {

    /**
     * @brief      Implementação de uma Estrutura de Dados do tipo Pilha
     *             (Last In First Out ou LIFO) - Organização dos elementos onde
     *             o último a ser inserido é o primeiro a ser retirado.
     *
     * @tparam     T     Parâmetro genérico de Template
     */

template<typename T>
class LinkedStack {
 public:
    LinkedStack();

    ~LinkedStack();

    void clear();  // limpa pilha

    void push(const T& data);  // empilha

    T pop();  // desempilha

    T& top() const;  // dado no topo

    bool empty() const;  // pilha vazia

    std::size_t size() const;  // tamanho da pilha

 private:
    class Node {
     public:
        explicit Node(const T& data) : data_{data} { }
        Node(const T& data, Node* next) : data_{data}, next_{next} { }

        T& data() { return data_; }  // getter: info
        const T& data() const { return data_; }  // getter-constante: info

        Node* next() { return next_; }  // getter: próximo
        const Node* next() const { return next_; }  // getter-constante: próximo

        void next(Node* next) { next_ = next; }  // setter: próximo
     private:
        T data_;
        Node* next_;
    };

    Node* top_;  // nodo-topo
    std::size_t size_;  // tamanho
};

/**
 *   Construtor padrão da classe LinkedStack.
 */
template <typename T>
LinkedStack<T>::LinkedStack() {
    top_ = nullptr;
    size_ = 0;
}

/**
 *   Destrutor padrão da classe LinkedStack.
 */
template<typename T>
LinkedStack<T>::~LinkedStack() {
    clear();
}

/**
 *   Faz uma limpeza da pilha encadeada LinkedStack.
 */
template<typename T>
void LinkedStack<T>::clear() {
    while (!empty()) {
        pop();
    }
}

/**
 *   Verifica se a pilha encadeada (LinkedStack) está vazia.
 */
template<typename T>
bool LinkedStack<T>::empty() const {
    return top_ == nullptr;
}

/**
 *   Verifica e retorna o tamanho da pilha encadeada (LinkedStack).
 */
template<typename T>
std::size_t LinkedStack<T>::size() const {
    return size_;
}

/**
 * Inserir novo elemento no fim da pilha (LinkedStack).
 */
template<typename T>
void LinkedStack<T>::push(const T& data) {
    Node* first_node = new Node(data);
    if (first_node == nullptr)
        throw std::out_of_range("Pilha está cheia.");

    first_node->next(top_);
    top_ = first_node;
    size_++;
}

/**
 *   Remove um elemento da pilha encadeada (LinkedStack).
 */
template<typename T>
T LinkedStack<T>::pop() {
    if (empty())
        throw std::out_of_range("Pilha vazia!");
    Node* left_ = top_;
    T return_ = left_->data();
    top_ = top_->next();
    size_--;
    delete left_;
    return return_;
}

/**
 *   Retorna o último elemento inserido na pilha encadeada (LinkedStack).
 */
template<typename T>
T& LinkedStack<T>::top() const {
    if (empty())
        throw std::out_of_range("Pilha vazia.");
    return top_->data();
}
}  // namespace structures
