// Copyright 2017 Letícia do Nascimento

#include <stdexcept>  // C++ exception

namespace structures {

    /**
     * @brief      Implementação de uma Estrutura de Dados do tipo Fila
     *             (First In First Out ou FIFO) - Organização dos elementos onde
     *             o primeiro a ser inserido é o primeiro a ser retirado.
     *
     * @tparam     T     Parâmetro genérico de Template
     */

template<typename T>
class LinkedQueue {
 public:
    LinkedQueue();

    ~LinkedQueue();

    void clear();  // limpar

    void enqueue(const T& data);  // enfilerar

    T dequeue();  // desenfilerar

    T& front() const;  // primeiro dado

    T& back() const;  // último dado

    bool empty() const;  // fila vazia

    std::size_t size() const;  // tamanho

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

    Node* head;  // nodo-cabeça
    Node* tail;  // nodo-fim
    std::size_t size_;  // tamanho
};

/**
 *   Construtor padrão da classe LinkedQueue.
 */
template <typename T>
LinkedQueue<T>::LinkedQueue() {
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

/**
 *   Destrutor padrão da classe LinkedQueue.
 */
template<typename T>
LinkedQueue<T>::~LinkedQueue() {
    Node *current, *previous;
    current = head;
    while (current != nullptr) {
        previous = current;
        current = current->next();
        delete previous;
    }
}

/**
 *   Faz uma limpeza da fila encadeada LinkedQueue.
 */
template<typename T>
void LinkedQueue<T>::clear() {
    Node *current, *previous;
    current = head;
    while (current != nullptr) {
        previous = current;
        current = current->next();
        delete previous;
    }
    size_ = 0;
    head = nullptr;
    tail = nullptr;
}

/**
 *   Verifica se a fila encadeada (LinkedQueue) está vazia.
 */
template<typename T>
bool LinkedQueue<T>::empty() const {
    return size_ == 0;
}

/**
 *   Verifica e retorna o tamanho da fila encadeada (LinkedQueue).
 */
template<typename T>
std::size_t LinkedQueue<T>::size() const {
    return size_;
}

/**
 * Inserir novo elemento na fila (LinkedQueue).
 */
template<typename T>
void LinkedQueue<T>::enqueue(const T& data) {
    Node* new_node = new Node(data, nullptr);
    if (size_ == 0) {
        head = new_node;
    } else {
        tail->next(new_node);
    }
    tail = new_node;
    size_++;
}

/**
 *   Remove um elemento da fila encadeada (LinkedQueue).
 */
template<typename T>
T LinkedQueue<T>::dequeue() {
    if (empty())
        throw std::out_of_range("Fila vazia!");
    if (size_ == 1)
        tail = nullptr;
    Node* left_ = head;
    T return_ = left_->data();
    head = left_->next();
    delete left_;
    size_--;
    return return_;
}

/**
 *   Retorna o primeiro elemento da fila encadeada (LinkedQueue).
 */
template<typename T>
T& LinkedQueue<T>::front() const {
    if (empty())
        throw std::out_of_range("Fila vazia.");
    return head->data();
}

/**
 *   Retorna o último elemento da fila encadeada (LinkedQueue).
 */
template<typename T>
T& LinkedQueue<T>::back() const {
    if (empty())
        throw std::out_of_range("Fila vazia.");
    return tail->data();
}
}  // namespace structures

