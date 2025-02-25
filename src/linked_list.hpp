#include <iostream>
#include <stdexcept>
#include <locale.h>
#include <utility>
#include <string>

#include "../include/linked_list.hpp"

using namespace std;

// CONSTRUTOR DA CLASSE LinkedList
template <class T>
LinkedList<T>::LinkedList() : head(nullptr), _size(0) {}

// DESTRUTOR DA CLASSE LinkedList
template <class T>
LinkedList<T>::~LinkedList() {
    clear();
}

// RETORNA O TAMANHO DA LISTA LinkedList
template <class T>
size_t LinkedList<T>::size() const {
  return _size;
}

// RETORNA SE A LISTA LinkedList ESTÁ VAZIA
template <class T>
bool LinkedList<T>::empty() const {
  return _size == 0;
}

// INSERE UM ELEMENTO EM UMA POSIÇÃO ESPECÍFICA
template <class T>
void LinkedList<T>::insert(size_t index, const T &value) {
    if (index > _size) {
        throw out_of_range("Índice inválido.");
    }
    
    if (index == 0 || head == nullptr) {
        push_front(value);
        return;
    }
    
    Node* atual = head;
    Node* prev = nullptr;
    
    for (size_t i = 0; i < index && atual != nullptr; i++) {
        prev = atual;
        atual = atual->prox;
    }
    
    Node* new_node = new Node(value);
    new_node->prox = atual;
    prev->prox = new_node;
    _size++;
}

// IMPRIMIR A LISTA LinkedList
template <class T> 
void LinkedList<T>::print() const {
    auto atual = head;
    while (atual != nullptr) {
        cout << atual->value << " -> ";
        atual = atual->prox;
    }
    cout << "NULL" << endl;
}


// ADICIONA ELEMENTO NO INÍCIO
template <class T>
void LinkedList<T>::push_front(const T& value) {
    Node* new_node = new Node(value);
    new_node->prox = head;
    head = new_node;
    _size++;
}

// COPIA OS ELEMENTOS DE OUTRA LISTA ENCADEADA PARA ESTA LISTA LinkedList
template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList &list) {
    if (this != &list) {
        clear(); // Limpa a lista atual

        Node* atual = list.head;
        while (atual != nullptr) {
            push_back(atual->value); // Adiciona os elementos diretamente
            atual = atual->prox;
        }
    }
    return *this;
}

// REMOVER O PRIMEIRO ELEMENTO
template <class T>
void LinkedList<T>::pop_front() {
    if (empty()) {
        throw out_of_range("Lista vazia.");
    }

    Node* temp = head;
    head = head->prox;

    delete temp;
    _size--;

    if (_size == 0) { // Se a lista ficou vazia
        head = nullptr;
    }
}

// REMOVER O ELEMENTO EM UMA POSIÇÃO ESPECÍFICA
template <class T>
void LinkedList<T>::remove(size_t index) {
    if (empty()) {
        throw out_of_range("Não é possível remover de uma lista vazia.");
    }

    if (index >= _size) {
        throw out_of_range("Índice inválido: " + std::to_string(index));
    }

    if (index == 0) {
        pop_front();
        return;
    }

    Node* atual = head;
    Node* prev = nullptr;

    for (size_t i = 0; i < index; i++) {
        prev = atual;
        atual = atual->prox;
    }

    prev->prox = atual->prox;
    delete atual;
    _size--;
}


// LIMPAR A LISTA LinkedList
template <class T>
void LinkedList<T>::clear() {
    while (!empty()) { // Apenas limpa se houver elementos
        pop_front();
    }
}

// ENCONTRA UM ELEMENTO NA LISTA LinkedList E RETORNA UMA REFERÊNCIA MUTÁVEL, 
// PERMITINDO MODIFICAR O VALOR ENCONTRADO
template <class T>
T& LinkedList<T>::find(const T &item) {
    Node* atual = head;

    while (atual != nullptr) {
        if (atual->value == item) {
            return atual->value; // Retorna uma referência ao valor encontrado
        }
        atual = atual->prox; // Avança para o próximo nó
    }

    throw out_of_range("Elemento não encontrado.");
}

// ENCONTRA UM ELEMENTO NA LISTA LinkedList E RETORNA UMA REFERÊNCIA CONSTANTE, 
// GARANTINDO QUE O VALOR NÃO SERÁ MODIFICADO
template <class T>
const T& LinkedList<T>::find(const T &item) const {
    Node* atual = head;
    while (atual != nullptr) {
        if (atual->value == item) {
            return atual->value;
        }

        atual = atual->prox;
    }
    throw out_of_range("Elemento não encontrado.");
}

// VERIFICAR A EXISTÊNCIA DE UM ELEMENTO NA LISTA LinkedList
template <class T>
bool LinkedList<T>::contains(const T &item) const {
    Node* atual = head;
    while (atual != nullptr) {
        if (atual->value == item) {
            return true;
        }

        atual = atual->prox;
    }
    return false;
}

// SOBRECARGA DO OPERADOR [] QUE RETORNA UMA REFERÊNCIA MUTÁVEL AO ELEMENTO NO ÍNDICE ESPECIFICADO
template <class T>
T& LinkedList<T>::operator[](size_t index) {
    if (index >= _size) {
        throw out_of_range("Índice inválido: " + std::to_string(index) + ". Tamanho da lista: " + std::to_string(_size));
    }
    Node* atual = head;
    for (size_t i = 0; i < index; i++) {
        atual = atual->prox;
    }
    return atual->value;
}


// SOBRECARGA DO OPERADOR [] QUE RETORNA UMA REFERÊNCIA CONSTANTE AO ELEMENTO NO ÍNDICE ESPECIFICADO
template <class T>
const T& LinkedList<T>::operator[](size_t index) const {
    if (index >= _size) {
        throw out_of_range("Índice inválido.");
    }
    Node* atual = head;
    for (size_t i = 0; i < index; i++) {
        atual = atual->prox;
    }
    return atual->value;
}

// CONSTRUTOR DA CLASSE Node
template <class T>
LinkedList<T>::Node::Node(const T &value) : value(value), prox(nullptr) {}

// DESTRUTOR DA CLASSE Node
template <class T>
LinkedList<T>::Node::~Node() {
    prox = nullptr;
}

// CONSTRUTOR DE CÓPIA DA CLASSE LinkedList
template <class T>
LinkedList<T>::LinkedList(const LinkedList &list) : head(nullptr), _size(0) {
    if (list.head == nullptr) return;

    Node* atual = list.head;
    Node* tail = nullptr;

    head = new Node(atual->value);
    tail = head;
    atual = atual->prox;
    _size++;

    while (atual != nullptr) {
        tail->prox = new Node(atual->value);
        tail = tail->prox;
        atual = atual->prox;
        _size++;
    }
}