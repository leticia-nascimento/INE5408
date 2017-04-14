// Copyright 2017 Letícia do Nascimento

#include <stdexcept>  // C++ exception
#include <cstdint>

namespace structures {

/**
 * @brief      Implementação de uma Estrutura de Dados do tipo Lista Duplamente
 *             Encadeada. Organização de dados linear e dinâmica, composta por
 *             células que apontam para o próximo elemento da lista, e para
 *             o anterior.
 *
 * @tparam     T     Parâmetro genérico de Template
 */

template<typename T>
class DoublyLinkedList {
 public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

 private:
    class Node {
     public:
        explicit Node(const T& data)  : data_{data} { }
        Node(const T& data, Node* next)  : data_{data}, next_{next} { }
        Node(const T& data, Node* prev, Node* next)  : data_{data}, prev_{prev},
        next_{next} { }

        T& data()  { return data_; }
        const T& data() const  { return data_; }

        Node* prev()  { return prev_; }
        const Node* prev() const  { return prev_; }

        void prev(Node* node) { prev_ = node; }

        Node* next()  { return next_; }
        const Node* next() const  { return next_; }

        void next(Node* node)  { next_ = node; }
     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head;
    std::size_t size_;
};

/**
 *   Construtor padrão da classe DoublyLinkedList.
 */
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
    head = nullptr;
    size_ = 0;
}

/**
 *   Destrutor padrão da classe DoublyLinkedList.
 */
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

/**
 *   Faz uma limpeza da lista encadeada DoublyLinkedList.
 */
template<typename T>
void DoublyLinkedList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

/**
 *   Verifica se a lista encadeada (DoublyLinkedList) está vazia.
 */
template<typename T>
bool DoublyLinkedList<T>::empty() const {
    return size_ == 0;
}

/**
 *   Verifica e retorna o tamanho da lista encadeada (DoublyLinkedList).
 */
template<typename T>
std::size_t DoublyLinkedList<T>::size() const {
    return size_;
}

/**
 *   Inserir novo elemento do fim da lista encadeada (DoublyLinkedList).
 */
template<typename T>
void DoublyLinkedList<T>::push_back(const T& data) {
    insert(data, size_ - 1);
}

/**
 *   Inserir novo elemento no índice específico da lista encadeada (DoublyLinkedList).
 */
template<typename T>
void DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
    Node* new_ = new Node(data);
    Node* current = head;

    if (index < 0 || index > size_)
        throw std::out_of_range("Índice inválido");

    if (index == 0)
        return push_front(data);

    if (new_ == nullptr)
        throw std::out_of_range("Lista cheia.");

    for (int i = 0; i < index - 1; i++)
        current = current->next();
        new_->next()->prev(new_);

      //  current->next(current->next());
      //  current->next(new_);

    if (new_->next() != nullptr)
        new_->next()->prev(new_);

    size_++;
}

/**
 * Inserir novo elemento no começo da lista encadeada (DoublyLinkedList).
 */
template<typename T>
void DoublyLinkedList<T>::push_front(const T& data) {
    Node* first_node = new Node(data);
    if (first_node == nullptr)
        throw std::out_of_range("Lista está cheia.");

    first_node->next(head);
    first_node->prev(nullptr);
    head = first_node;

    if (first_node->next() != nullptr)
        first_node->next()->prev(first_node);

    size_++;
}

/**
 *   Insere novo elemento na ordem definida pela lista encadeada
 * (DoublyLinkedList).
 */
template<typename T>
void DoublyLinkedList<T>::insert_sorted(const T& data) {
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
 *   Retorna um elemento da lista encadeada que está em uma posição específica
 * (DoublyLinkedList).
 */
template<typename T>
T& DoublyLinkedList<T>::at(std::size_t index) {
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
 *   Remove um elemento da lista encadeada (DoublyLinkedList).
 */
template<typename T>
T DoublyLinkedList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("Lista vazia!");

    if (index > (size_ - 1))
        throw std::out_of_range("Índice inválido!");

    if (index == 0)
        return pop_front();

    std::size_t i = 0;
    Node* previous = head;

    for (i = 0; i < index - 1; i++) {
      previous = previous->next();
    }

    Node* current = previous->next();
    T return_ = current->data();
    previous->next(current->next());

    if (current->next() != nullptr)
        current->next()->prev(previous);

    size_--;
    delete current;
    return return_;
}

/**
 *   Remove o último elemento da lista encadeada (DoublyLinkedList).
 */
template<typename T>
T DoublyLinkedList<T>::pop_back() {
    return pop(size_ - 1);
}

/**
 *   Remove o primeiro elemento da lista encadeada (DoublyLinkedList).
 */
template<typename T>
T DoublyLinkedList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("Lista está vazia!");

    Node* previous = head;
    T out_ = previous->data();
    head = previous->next();

    if (head != nullptr)
        head->prev(nullptr);

    delete previous;
    size_--;
    return out_;
}

/**
 *   Remove um item específico da lista encadeada (DoublyLinkedList).
 */
template<typename T>
void DoublyLinkedList<T>::remove(const T& data) {
    std::size_t test = find(data);
    if (test != size_)
        pop(test);
}

/**
 *   Verifica se a lista encadeada (DoublyLinkedList) possui um elemento
 * específico de acordo com o elemento fornecido.
 */ 
template<typename T>
bool DoublyLinkedList<T>::contains(const T& data) const {
    if (find(data) != size_)
        return true;
    return false;
}

/**
 *   Retorna o índice de um elemento específico na lista encadeada
 * (DoublyLinkedList).
 */
template<typename T>
std::size_t DoublyLinkedList<T>::find(const T& data) const {
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

 /** 
 *  Retorna um elemento específico na lista encadeada sem checagens
 * (DoublyLinkedList).
 */
template<typename T>
const T& DoublyLinkedList<T>::at(std::size_t index) const {
    std::size_t i;
    Node* current = head;

    while (index < i) {
        i++;
        current = current->next();
    }

    return current->data();
}

}  // namespace structures
