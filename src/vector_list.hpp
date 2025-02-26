#include <iostream>
#include <stdexcept>

#include "../include/vector_list.hpp"

using namespace std;

// CONSTRUTOR DA CLASSE VectorList
template <class T>
VectorList<T>::VectorList(size_t capacity) 
  : data{new T[capacity]},_size{0},_capacity{capacity} {}

// DESTRUTOR DA CLASSE VectorList
template  <class T>
VectorList<T>::~VectorList() {
  delete[] data;
}

// RETORNA A CAPACIDADE DA LISTA
template <class T>
size_t VectorList<T>::capacity() const {
    return _capacity;
}

// RETORNA O TAMANHO DA LISTA
template <class T>
size_t VectorList<T>::size() const {
  return _size;
}

// ADICIONA UM ELEMENTO NO FINAL DA LISTA
template <class T>
void VectorList<T>::push_back(const T& value){
    if(size()>=capacity()){
        throw length_error("Lista cheia.");
    }

    data[size()] = value;

    _size++;
}

// RETORNA UM BOOL PARA SE A LISTA FOR VAZIA
template <class T> 
bool VectorList<T>::empty() const {
    return size() == 0;
}

// DELETA UM ELEMENTO DA LISTA
template <class T>
void VectorList<T>::pop_back()  {
    if(empty()){
        throw out_of_range("Lista vazia.");
    }
    _size--;
}

// IMPRIME A LISTA
template <class T>
void VectorList<T>::print() const {
    for(size_t i = 0; i < size(); i++){
        cout << data[i] << " ";
    }
    cout << "\n";
}

// INSERE UM ELEMENTO NA LISTA EM UMA POSIÇÃO ESPECÍFICA
template <class T>
void VectorList<T>::insert(size_t index,const T& value) {
    if(size() >= capacity()){
        throw length_error("Lista cheia");
    } else if (index > size()){
        throw out_of_range("Posição inválida.");
    }

    if(index == size()){
        return push_back(value);
    }

    for(size_t i = size(); i<=index ;i--){
        data[i] = data[i-1];
    }
    data[index] = value;

    _size++;
}

// REMOVE UM ELEMENTO BASEADO NA SUA POSIÇÃO
template <class T>
void VectorList<T>::remove(size_t index) {
    if(index >= size()){
        throw out_of_range("Posição inválida.");
    }

    if(index == size()-1){
        return pop_back();
    }

    for (size_t i = index; i < size()-1; i++) {
        data[i] = data[i+1];
    }

    _size--;
}

// BUSCA UM ITEM EM UM ARRAY E RETORNA UM PONTEIRO PARA ELE, OU nullptr SE NÃO ENCONTRADO
template <class T> 
T* find_item_in_data(T* data, size_t size, const T& item) {
    for (size_t i = 0; i < size; i++) {
        if (data[i] == item) {
            return &data[i];
        }
    }

    return nullptr;
}

// PROCURA UM ITEM EM UM VETOR E RETORNA UMA REFERÊNCIA PARA ELE, LANÇANDO UMA EXCEÇÃO SE NÃO FOR ENCONTRADO
template <class T>
T& VectorList<T>::find(const T& item){
    auto elemento = find_item_in_data(data, size(), item);

    if(elemento == nullptr){
        throw out_of_range("Item não encontrado.");
    } else {
        return *elemento;
    }
}

// PROCURA UM ITEM EM UM VETOR E RETORNA UMA REFERÊNCIA CONSTANTE PARA ELE, LANÇANDO UMA EXCEÇÃO SE NÃO FOR ENCONTRADO
template <class T>
const T& VectorList<T>::find(const T& item) const {
    auto elemento = find_item_in_data(data, size(), item);

    if(elemento == nullptr){
        throw out_of_range("Item não encontrado.");
    } else {
        return *elemento;
    }
}

// VERIFICA SE UM ITEM EXISTE NO VETOR E RETORNA true SE ENCONTRADO, OU false CASO CONTRÁRIO
template <class T>
bool VectorList<T>::contains(const T& item) const {
    auto elemento = find_item_in_data(data, size(), item);

    return elemento != nullptr;
}

// LIMPA O VETOR DEFININDO O TAMANHO (_size) COMO 0, SEM ALTERAR A CAPACIDADE ALOCADA
template <class T>
void VectorList<T>::clear() {
    _size = 0;
}

// CONSTRUTOR DE CÓPIA QUE CRIA UMA NOVA INSTÂNCIA DE VectorList, 
// COPIANDO OS DADOS, TAMANHO E CAPACIDADE DO VETOR ORIGINAL
template <class T>
VectorList<T>::VectorList(const VectorList &list) 
    : data{new T[list._capacity]}, _size{list._size}, _capacity{list._capacity} {
    for (size_t i = 0; i < list._size; i++) {
        data[i] = list.data[i];
    }
}

// SOBRECARGA DO OPERADOR DE ATRIBUIÇÃO QUE COPIA OS DADOS, 
// TAMANHO E CAPACIDADE DE OUTRO VectorList, GARANTINDO UMA CÓPIA PROFUNDA
template <class T>
VectorList<T> &VectorList<T>::operator=(const VectorList &list) {
    if (this != &list) {
        delete[] data;
        _capacity = list._capacity;
        _size = list._size;
        data = new T[_capacity];
        for (size_t i = 0; i < _size; i++) {
            data[i] = list.data[i];
        }
    }
    return *this;
}

// SOBRECARGA DO OPERADOR [] QUE RETORNA UMA REFERÊNCIA AO ELEMENTO 
// NO ÍNDICE ESPECIFICADO, LANÇANDO UMA EXCEÇÃO SE O ÍNDICE FOR INVÁLIDO.
template <class T>
T &VectorList<T>::operator[](size_t index) {
    if (index >= _size) {
        throw out_of_range("Índice inválido.");
    }
    return data[index];
}

// SOBRECARGA DO OPERADOR [] QUE RETORNA UMA REFERÊNCIA CONSTANTE 
// AO ELEMENTO NO ÍNDICE ESPECIFICADO, LANÇANDO UMA EXCEÇÃO SE O ÍNDICE FOR INVÁLIDO
template <class T>
const T &VectorList<T>::operator[](size_t index) const {
    if (index >= _size) {
        throw out_of_range("Índice inválido.");
    }
    return data[index];
}