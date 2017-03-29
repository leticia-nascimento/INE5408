//  Copyright 2017 Letícia do Nascimento
 
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H
     
#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
     
namespace structures {
    
    /**
     * @brief      Implementação de uma Estrutura de Dados do tipo Fila
     *			   (First In First Out ou FIFO) - Organização dos elementos onde
     *			   o primeiro a ser inserido é o primeiro a ser retirado.
     *
     * @tparam     T     Parâmetro genérico de Template
     */
    

    template<typename T>
    class ArrayQueue {
        public:
            ArrayQueue();

            explicit ArrayQueue(std::size_t max);

            ~ArrayQueue();
    
            void enqueue(const T& data);  // enfila
  
            T dequeue();  // desenfila
    
            T& back();
    
            void clear();  // limpa
    
            std::size_t size();  // tamanho
    
            std::size_t max_size();
    
            bool empty();  // vazia
   
            bool full();  // cheia
    
        private:
            T* contents;
            int size_;
            std::size_t max_size_;
            
            static const auto DEFAULT_SIZE = 10u;
    };
   
}   

#endif // namespace structures


//  construtor da classe

template <typename T>
structures::ArrayQueue<T>::ArrayQueue() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    size_ = 0;
}

//  construtor da classe com valor passado por parâmetro
//  param max do tipo size_t - representa o tamanho máximo de elementos do vetor

template <typename T>
structures::ArrayQueue<T>::ArrayQueue(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    size_ = 0;
}

//  destrutor da classe

template <typename T>
structures::ArrayQueue<T>::~ArrayQueue() {
    delete [] contents;
}

//  adiciona dados ao vetor
//  param data - um generico que representa o dado a ser armazenado

template <typename T>
void structures::ArrayQueue<T>::enqueue(const T& data) {
    if (full())
        throw std::out_of_range("Fila atualmente cheia.");
        
    contents[size_] = data;
    size_++;
}

//  retira dados do vetor

template <typename T> 
T structures::ArrayQueue<T>::dequeue() {
    if (empty())
        throw std::out_of_range("Fila atualmente vazia.");
        
    int first = contents [0];
    size_ --;
    for (int i = 0; i < size_; i++) {
        contents[i] = contents[i+1];
    }
    return first;
}

//  limpa a fila

template <typename T>
void structures::ArrayQueue<T>::clear() {
    size_ = 0;
}

//  retorna o último elemento da fila

template <typename T>
T& structures::ArrayQueue<T>::back() {
    if(empty()) 
        throw std::out_of_range("Fila vazia.");
        
    return (contents[size_ - 1]);    
}

//  retorna o tamanho da fila

template <typename T>
std::size_t structures::ArrayQueue<T>::size() {
    return (size_);
}

//  retorna o tamanho máximo da fila

template <typename T>
std::size_t structures::ArrayQueue<T>::max_size() {
    return (max_size_);
}

//  verifica se a fila está cheia

template <typename T>
bool structures::ArrayQueue<T>::full() {
    return size_ == max_size_;
}

//  verifica se a fila está vazia

template <typename T>
bool structures::ArrayQueue<T>::empty() {
    return size_ == 0;
}

