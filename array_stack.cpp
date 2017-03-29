//  Copyright 2017 Letícia do Nascimento
 
#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H
     
#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
     
namespace structures {
    
    /**
     * @brief      Implementação de uma Estrutura de Dados do tipo Pilha
     *			   (Last In First Out ou LIFO) - Organização dos elementos onde
     *			   o último a ser inserido é o primeiro a ser retirado.
     *
     * @tparam     T     Parâmetro genérico de Template
     */
    

    template<typename T>
    class ArrayStack {
        public:
            ArrayStack();

            explicit ArrayStack(std::size_t max);

            ~ArrayStack();
    
            void push(const T& data);  // empilha
  
            T pop();  // desempilha
    
            T& top();
    
            void clear();  // limpa
    
            std::size_t size();  // tamanho
    
            std::size_t max_size();
    
            bool empty();  // vazia
   
            bool full();  // cheia
    
        private:
            T* contents;
            int top_;
            std::size_t max_size_;
            
            static const auto DEFAULT_SIZE = 10u;
    };
   
}   

#endif // namespace structures


//  construtor da classe

template <typename T>
structures::ArrayStack<T>::ArrayStack() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    top_ = -1;
}

//  construtor da classe com valor passado por parâmetro
//  param max do tipo size_t - representa o tamanho máximo de elementos do vetor

template <typename T>
structures::ArrayStack<T>::ArrayStack(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    top_ = -1;
}

//  destrutor da classe

template <typename T>
structures::ArrayStack<T>::~ArrayStack() {
    delete [] contents;
}

//  adiciona dados ao vetor
//  param data - um generico que representa o dado a ser armazenado

template <typename T>
void structures::ArrayStack<T>::push(const T& data) {
    if (full())
        throw std::out_of_range("Pilha atualmente cheia.");
        
    contents[top_] = data;
}

//  retira dados do vetor

template <typename T> 
T structures::ArrayStack<T>::pop() {
    if (empty())
        throw std::out_of_range("Pilha atualmente vazia.");
    
    top_ --;
    return contents[top_+1];
}

//  limpa a pilha

template <typename T>
void structures::ArrayStack<T>::clear() {
    top_ = -1;
}

//  retorna o elemento do topo da pilha

template <typename T>
T& structures::ArrayStack<T>::top() {
    if(empty()) 
        throw std::out_of_range("Pilha vazia.");
            
    return (contents[top_]);    
}

//  retorna o tamanho da pilha

template <typename T>
std::size_t structures::ArrayStack<T>::size() {
    return (top_+1);
}

//  retorna o tamanho máximo da pilha

template <typename T>
std::size_t structures::ArrayStack<T>::max_size() {
    return (max_size_);
}

//  verifica se a pilha está cheia

template <typename T>
bool structures::ArrayStack<T>::full() {
    return top_ == max_size_ -1;
}

//  verifica se a pilha está vazia

template <typename T>
bool structures::ArrayStack<T>::empty() {
    return top_ == -1;
}

