//  Copyright 2017 Letícia do Nascimento
 
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H
     
#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
     
namespace structures {
    
    /**
     * @brief      Implementação de uma Estrutura de Dados do tipo Lista
     *			   Organização dos elementos onde pode ou não possuir uma
     *			   ordem.
     *
     * @tparam     T     Parâmetro genérico de Template
     */
    

    template<typename T>
    class ArrayList {
    public:
        ArrayList();  // construtor
        explicit ArrayList(std::size_t max_size);  // construtor
        ~ArrayList();  // destrutor

        void clear();  // limpa vetor
        void push_back(const T& data);  // insere um dado por trás
        void push_front(const T& data);  // insere um dado pela frente
        void insert(const T& data, std::size_t index);  // insere elemento
        void insert_sorted(const T& data);  // insere um dado em ordem
        T pop(std::size_t index);  // retira um elemento em um indice e o retorna
        T pop_back();  // retira o elemento por trás e o retorna
        T pop_front();  // retira elemento pela frente e o retorna 
        void remove(const T& data);  // remove um elemento pre definido
        bool full() const;  // verifica se está cheio
        bool empty() const;  // verifica se está vazio
        bool contains(const T& data) const;  // verifica se o elemento está na lista
        std::size_t find(const T& data) const;  // retorna endereço do elemento
        std::size_t size() const;  // retorna tamanho atual 
        std::size_t max_size() const;  // retorna tamanho máximo
        T& at(std::size_t index);  // retorna o dado num determinado endereço - v1
        T& operator[](std::size_t index);  // retorna o dado num determinado endereço - v2
        const T& at(std::size_t index) const;  // retorna o dado num determinado endereço - v3
        const T& operator[](std::size_t index) const;  // retorna o dado num determinado endereço - v4

    private:
        T* contents;
        std::size_t size_;
        std::size_t max_size_;

        static const auto DEFAULT_MAX = 10u;
    };

}  // namespace structures

#endif

//  construtor da classe

template <typename T>
structures::ArrayList<T>::ArrayList() {
    max_size_ = DEFAULT_MAX;
    contents = new T[max_size_];
    size_ = 0;
}

//  construtor da classe com valor passado por parâmetro
//  param max do tipo size_t - representa o tamanho máximo de elementos do vetor

template <typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
    max_size_ = max_size;
    contents = new T[max_size_];
    size_ = 0;
}

//  destrutor da classe

template <typename T>
structures::ArrayList<T>::~ArrayList() {
    delete [] contents;
}

//  adiciona dados ao vetor
//  param data - um generico que representa o dado a ser armazenado
//  param index - um indice para ser inserido o dado

template <typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("Lista atualmente cheia."); 
    } else if (index > size_ || index < 0) {
            throw std::out_of_range("Erro! Posição inexistente.");
      }
    
    int i = size_;
    while (i > index) {
        contents[i] = contents[i - 1];
        i--;
    }    
    contents[index] = data;
    size_++;
}

//  retira dados do vetor por trás

template <typename T> 
T structures::ArrayList<T>::pop_back() {
   return pop(size_-1);
}

//  retira dados do vetor pela frente

template <typename T> 
T structures::ArrayList<T>::pop_front() {
    return pop(0); 
}

//  retira dados do vetor com parametro
//  param index - representa o endereço onde o dado será retirado

template <typename T> 
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Lista atualmente vazia.");
    } else if (index > size_ || index < 0) {
            throw std::out_of_range("Erro! Posição inexistente.");
      }
    
    T retorno = contents[index];
    int i = size_ -1;
    while (i > index) {
        contents[i] = contents[i+1];
        i--;
    }    
    size_--;
    return retorno; 
}

//  remove um elemento da lista
//  param data - representa o elemento a ser removido

template <typename T>
void structures::ArrayList<T>::remove(const T& data) {
    if (!contains(data))
        throw std::out_of_range("Elemento inexistente");
   pop(find(data));
}

//  encontra um elemento na lista
//  param data - representa o elemento a ser encontrado

template <typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    std:: size_t i;
    for (i = 0; i < size_; i++) {
        if (contents[i] == data) {
            break;
        }
    }
    return i;
}

//  verifica se um elemento está na lista
//  param data - representa o elemento a ser verificado

template <typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    return (find(data) != size_);
}

//  limpa a lista

template <typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

//  retorna o tamanho da lista

template <typename T>
std::size_t structures::ArrayList<T>::size() const {
    return (size_);
}

//  retorna o tamanho máximo da lista

template <typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return (max_size_);
}

//  verifica se a lista está cheia

template <typename T>
bool structures::ArrayList<T>::full() const {
    return size_ == max_size_;
}

//  verifica se a lista está vazia

template <typename T>
bool structures::ArrayList<T>::empty() const {
    return size_ == 0;
}

//  insere um elemento por trás

template <typename T> 
void structures::ArrayList<T>::push_back(const T& data) {
   insert(data, 0);
}

//  insere um elemento pela frente

template <typename T> 
void structures::ArrayList<T>::push_front(const T& data) {
    insert(data, size_); 
}

//  insere um elemento em ordem

template <typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full())
        throw std::out_of_range("Lista atualmente cheia."); 
    
    std:: size_t i = 0;
    while (i < size_ && data > contents[i]) {
        i++;
    }
    insert(data, i);    
}

//  retorna o dado num determinado endereço - v1

template <typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (index > size_ || index < 0) 
        throw std::out_of_range("Erro! Posição inexistente."); 
        
    return contents[index];
}

//  retorna o dado num determinado endereço - v2

template <typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    if (index > size_ || index < 0) 
        throw std::out_of_range("Erro! Posição inexistente."); 
        
    return contents[index];
}
   
//  retorna o dado num determinado endereço - v3 
    
template <typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (index > size_ || index < 0) 
        throw std::out_of_range("Erro! Posição inexistente."); 
        
    return contents[index];
}

//  retorna o dado num determinado endereço - v4

template <typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    if (index > size_ || index < 0) 
        throw std::out_of_range("Erro! Posição inexistente."); 
        
    return contents[index];
}
