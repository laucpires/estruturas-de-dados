#include <iostream>
#include <locale.h>
#include <stdexcept>
#include "../include/doubly_linked_list.hpp"

using namespace std;

// CONSTRUTOR DA CLASSE Node
template <class T>
DoublyLinkedList<T>::Node::Node(const T& value)
    : value{value}, next{nullptr}, prev{nullptr} {}

// DESTRUTOR DA CLASSE Node
template <class T>
DoublyLinkedList<T>::Node::~Node() {
    next = nullptr; 
    prev = nullptr;
}

// CONSTRUTOR DA CLASSE DoublyLinkedList
template <class T>
DoublyLinkedList<T>::DoublyLinkedList()
    : head(nullptr), tail(nullptr), _size(0) {}

// DESTRUTOR DA CLASSE DoublyLinkedList
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (!empty()) {
        pop_back();
    }
}

// VERIFICA O TAMANHO DA LISTA DoublyLinkedList
template <class T> 
size_t DoublyLinkedList<T>::size() const {
    return _size;
}

// VERIFICA SE A LISTA DoublyLinkedList ESTÁ VAZIA
template <class T>
bool DoublyLinkedList<T>::empty() const {
    return _size == 0;
}

// INSERE UM ELEMENTO NO INÍCIO DA LISTA DoublyLinkedList
template <class T>
void DoublyLinkedList<T>::push_front(const T& value) {
    auto new_node = new Node(value);

    if (empty()) {
        tail = new_node;
    } else {
        new_node->next = head;
        head->prev = new_node;
    }

    head = new_node;
    _size++;
}

// INSERE UM ELEMENTO NO FINAL DA LISTA DoublyLinkedList
template <class T>
void DoublyLinkedList<T>::push_back(const T& value) {
    auto new_node = new Node(value);

    if (empty()) {
        head = new_node;
    }

    else {
      new_node->prev = tail;
      tail->next = new_node;
    }

    tail = new_node;

    _size++;
}

// REMOVE O PRIMEIRO ELEMENTO DA LISTA DoublyLinkedList
template <class T>
void DoublyLinkedList<T>::pop_front() {
    if (empty()) {
        throw out_of_range("Lista vazia.");
    }

    auto tmp = head;

    head = head->next;

    if (head != nullptr) {
        head->prev = nullptr;
    }

    else {
        tail = nullptr;
    }

    delete tmp;

    _size--;
}

// REMOVE O ÚLTIMO ELEMENTO DA LISTA DoublyLinkedList
template <class T>
void DoublyLinkedList<T>::pop_back() {
    if (empty()) {
        throw out_of_range("Lista vazia.");
    }

    Node* old_tail = tail;

    if (head == tail) {
        head = nullptr;
        tail = nullptr;

    } else {
        tail = tail->prev;

        if (tail) { 
            tail->next = nullptr;
        }
    }

    delete old_tail;
    _size--;

    if (_size == 0) {  
        head = nullptr;
        tail = nullptr;
    }
}

// IMPRIME A LISTA DoublyLinkedList
template <class T>
void DoublyLinkedList<T>::print() const {
    auto pos = head;

    if (!pos) {
        cout << "Lista vazia." << endl;
        return;
    }

    while (pos != nullptr) {
        cout << pos->value;

        if (pos->next != nullptr) {
            cout << " <-> ";
        }

        pos = pos->next;
    }

    cout << " -> NULL" << endl;
}

// ITERADOR DA LISTA DoublyLinkedList
template <class T>
template <class U>
DoublyLinkedList<T>::Iterator<U>::Iterator(U* p, bool end)
    : node{p}, end{end} {}

// ITERADOR INICIAL DA LISTA DoublyLinkedList
// PERMITE MODIFICAÇÃO
template <class T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::begin() {
    return iterator(head, empty());
}

// ITERADOR CONSTANTE INICIAL DA LISTA DoublyLinkedList
// NÃO PERMITE MODIFICAÇÃO
template <class T>
typename DoublyLinkedList<T>::const_iterator DoublyLinkedList<T>::begin() const {
    return const_iterator(head, empty());
}

// ITERADOR FINAL DA LISTA DoublyLinkedList
// PERMITE MODIFICAÇÃO
template <class T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::end() {
    return iterator(tail, true);
}

// ITERADOR CONSTANTE FINAL DA LISTA DoublyLinkedList
// NÃO PERMITE MODIFICAÇÃO
template <class T>
typename DoublyLinkedList<T>::const_iterator DoublyLinkedList<T>::end() const {
    return const_iterator(tail, true);
}

// ITERADOR CONSTANTE DE ADIÇÃO DA LISTA DoublyLinkedList
template <class T>
template <class U>
typename DoublyLinkedList<T>::template Iterator<U> 
DoublyLinkedList<T>::Iterator<U>::operator+(size_t n) const {
    auto result = *this;

    for (size_t i = 0; i < n && result.node != nullptr; ++i) {
        ++result;
    }

    return result;
}

// ITERADOR CONSTANTE DE SUBTRAÇÃO DA LISTA DoublyLinkedList
template <class T>
template <class U>
typename DoublyLinkedList<T>::template Iterator<U> 
DoublyLinkedList<T>::Iterator<U>::operator-(size_t n) const {
    auto result = *this;

    for (size_t i = 0; i < n && result.node != nullptr; ++i) {
        --result;
    }

    return result;
}

// RETORNA UMA REFERÊNCIA CONSTANTE AO VALOR ARMAZENADO NO NÓ ATUAL DO ITERADOR DA LISTA DoublyLinkedList
template <class T>
template <class U>
auto& DoublyLinkedList<T>::Iterator<U>::operator*() const {
    return node->value;
}

// ITERA PARA O PRÓXIMO NÓ
template <class T>
template <class U>
typename DoublyLinkedList<T>::template Iterator<U>&
DoublyLinkedList<T>::Iterator<U>::operator++() {
    if (node->next == nullptr) {
        end = true;
    } else {
        node = node->next;
    }

    return *this;
}

// MOVE O ITERADOR PARA O NÓ ANTERIOR NA LISTA DoublyLinkedList E RETORNA UMA REFERÊNCIA A ELE MESMO
template <class T>
template <class U>
DoublyLinkedList<T>::Iterator<U> & DoublyLinkedList<T>::Iterator<U>::operator--() {
    if (end) {
        end = false;
    } else {
        node = node->prev;
    }

    return *this;
}

// INSERE UM NOVO ELEMENTO NA POSIÇÃO ESPECIFICADA PELO ITERADOR, AJUSTANDO OS PONTEIROS DA LISTA DoublyLinkedList
template <class T>
void DoublyLinkedList<T>::insert(iterator pos, const T& value) {
    if (pos == begin()) {
        push_front(value);
        return;
    } 

    if (pos == end()) {
        push_back(value);
        return;
    }

    Node* node_pos = pos.node;
    Node* node_prev = node_pos->prev;

    auto new_node = new Node(value);
    new_node->next = node_pos;
    new_node->prev = node_prev;

    if (node_prev) {
        node_prev->next = new_node;
    }

    node_pos->prev = new_node;

    _size++;
}

// VERIFICA SE DOIS ITERADORES SÃO IGUAIS, COMPARANDO OS PONTEIROS DOS NÓS E O ESTADO FINAL
template <class T>
template <class U>
bool DoublyLinkedList<T>::Iterator<U>::operator==(const Iterator<U>& other) const {
    return node == other.node && end == other.end;
}

// VERIFICA SE DOIS ITERADORES SÃO DIFERENTES, BASEANDO-SE NA NEGAÇÃO DO OPERADOR DE IGUALDADE
template <class T>
template <class U>
bool DoublyLinkedList<T>::Iterator<U>::operator!=(const Iterator<U>& other) const {
    return !(*this == other);
}

// REMOVE TODOS OS NÓS ENTRE OS ITERADORES ESPECIFICADOS (FIRST, LAST), 
// AJUSTANDO OS PONTEIROS DA LISTA DoublyLinkedList
template <class T>
void DoublyLinkedList<T>::erase(iterator first, iterator last) {
    if (empty() || first == last) {
        return;
    }

    Node* atual = first.node;
    Node* final = last.end? nullptr: last.node;

    if (atual == head) {
        head = final;
    } else if (atual->prev) {
        atual->prev->next = final;
    }

    if (final == nullptr || last.end) {
        tail = atual->prev;
        if (tail) {
            tail->next = nullptr;
        }
    } else {
        final->prev = atual->prev;
    }

    while (atual && atual != final) {
        Node* next = atual->next;
        delete atual;
        _size--;
        atual = next;
    }

    if (_size == 0) {
        head = nullptr;
        tail = nullptr;
    }
}

// CALCULA A DISTÂNCIA ENTRE DOIS ITERADORES NA LISTA DoublyLinkedList, 
// RETORNANDO O NÚMERO DE PASSOS NECESSÁRIOS OU -1 SE NÃO ESTIVEREM CONECTADOS
template <class T>
template <class U>
size_t DoublyLinkedList<T>::Iterator<U>::operator-(Iterator<U> other) const {
    if (this->node == other.node) {
        return 0;
    }

    size_t distance = 0;
    auto it = other;

    while (it.node && it.node != this->node) {
        it.node = it.node->next;
        ++distance;
    }

    if (it.node == this->node) {
        return distance;
    }

    distance = 0;
    it = other;
    while (it.node && it.node != this->node) {
        it.node = it.node->prev;
        ++distance;
    }

    return (it.node == this->node) ? distance : static_cast<size_t>(-1);
}

// PROCURA O PRIMEIRO ELEMENTO NA LISTA DoublyLinkedList QUE SEJA IGUAL AO ITEM ESPECIFICADO 
// E RETORNA UM ITERADOR PARA ELE, OU END() SE NÃO FOR ENCONTRADO
template <class T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::find(const T& item) {
    auto it = begin();
    while (it != end()) {
        if (*it == item) {
            break;
        }
        ++it;
    }

    return it;
}

// PROCURA O PRIMEIRO ELEMENTO NA LISTA DoublyLinkedList QUE SEJA IGUAL AO ITEM ESPECIFICADO E 
// RETORNA UM ITERADOR CONSTANTE PARA ELE, OU END() SE NÃO FOR ENCONTRADO
template <class T>
typename DoublyLinkedList<T>::const_iterator DoublyLinkedList<T>::find(const T& item) const {
    auto it = begin();
    while (it != end()) {
        if (*it == item) {
            break;
        }
        ++it;
    }
    return it;
}

// VERIFICA SE A LISTA CONTÉM O ITEM ESPECIFICADO, 
// RETORNANDO TRUE SE ENCONTRADO OU FALSE CASO CONTRÁRIO
template <class T>
bool DoublyLinkedList<T>::contains(const T& item) const {
    return find(item) != end();
}

// ACESSA O ELEMENTO NA POSIÇÃO ESPECIFICADA PELO ÍNDICE, 
// LANÇANDO UMA EXCEÇÃO SE O ÍNDICE FOR INVÁLIDO
template <class T>
T& DoublyLinkedList<T>::operator[](size_t index) {
    if (index >= size()) {
        throw out_of_range("Índice inválido.");
    }

    auto it = begin();

    for (size_t i=0; i < index; ++i){
        ++it;
    }

    return *it;
}

// ACESSA O ELEMENTO CONSTANTE NA POSIÇÃO ESPECIFICADA PELO ÍNDICE, 
// LANÇANDO UMA EXCEÇÃO SE O ÍNDICE FOR INVÁLIDO
template <class T>
const T& DoublyLinkedList<T>::operator[](size_t index) const {
    if (index >= size()) {
        throw out_of_range("Índice inválido.");
    }

    return *(begin() + index);
}

// REMOVE TODOS OS ELEMENTOS DA LISTA, LIBERANDO A MEMÓRIA E REINICIALIZANDO OS PONTEIROS E O TAMANHO
template <class T>
void DoublyLinkedList<T>::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    head = nullptr;
    tail = nullptr;
    _size = 0;
}

// CONSTRUTOR DE CÓPIA QUE CRIA UMA NOVA LISTA 
// DUPLAMENTE ENCADEADA A PARTIR DE OUTRA, COPIANDO TODOS OS ELEMENTOS
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& list): head(nullptr), tail(nullptr), _size(0) {
    for (const auto& i : list) {
        push_back(i);
    }
}