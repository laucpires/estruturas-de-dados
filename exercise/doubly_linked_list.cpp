#include "../include/doubly_linked_list.hpp"
#include <iostream>

using namespace std;

int main() {
    DoublyLinkedList<int> list;

    // Teste: push_front
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    cout  <<  "Lista após push_front(30), push_front(20), push_front(10): ";
    list.print();

    // Teste: push_back
    list.push_back(40);
    list.push_back(50);
    cout  <<  "Lista após push_back(40), push_back(50): ";
    list.print();

    // Teste: pop_front
    cout  <<  "\nTESTE: pop_front"  <<  endl;
    list.pop_front();
    cout  <<  "Lista após pop_front(): ";
    list.print();

    // Teste: pop_back
    cout  <<  "\nTESTE: pop_back"  <<  endl;
    list.pop_back();
    cout  <<  "Lista após pop_back(): ";
    list.print();

    // Teste: size e empty
    cout  <<  "\nTESTE: size e empty"  <<  endl;
    cout  <<  "Tamanho da lista: "  <<  list.size()  <<  endl;
    cout  <<  "A lista está vazia? "  <<  (list.empty() ? "Sim" : "Não")  <<  endl;

    // Teste: insert
    cout  <<  "\nTESTE: insert"  <<  endl;
    auto it = list.begin();
    ++it; // Move o iterador para o segundo elemento
    list.insert(it, 25);
    cout  <<  "Lista após insert(25) na segunda posição: ";
    list.print();

    // Teste: erase
    cout  <<  "\nTESTE: erase"  <<  endl;
    auto it1 = list.begin();
    auto it2 = it1;
    ++it2; ++it2; // Pega o terceiro elemento
    list.erase(it1, it2);
    cout  <<  "Lista após erase do primeiro ao terceiro elemento: ";
    list.print();

    // Teste: find e contains
    cout  <<  "\nTESTE: find e contains"  <<  endl;
    int item = 40;
    auto found = list.find(item);
    if (found != list.end()) {
        cout  <<  "Elemento "  <<  item  <<  " encontrado na lista."  <<  endl;
        cout  <<  "A lista contém o elemento? " 
              <<  (list.contains(item) ? "Sim" : "Não") 
              <<  endl;
    } else {
        cout  <<  "Elemento "  <<  item  <<  " não encontrado na lista."  <<  endl;
        cout  <<  "A lista contém o elemento? Não"  <<  endl;
    }

    // Teste: operador []
    cout  <<  "\nTESTE: operador []"  <<  endl;
    try {
        cout  <<  "Elemento no índice 0: "  <<  list[0]  <<  endl;
        cout  <<  "Elemento no índice 1: "  <<  list[1]  <<  endl;
        // Acessando índice inválido para testar exceção
        cout  <<  "Elemento no índice 10 (inválido): ";
        cout  <<  list[10]  <<  endl; 
    } catch (const std::out_of_range& e) {
        cout  <<  e.what()  <<  endl;
    }

    // Teste: clear
    cout << "\nTESTE: clear" << endl;
    list.clear();
    cout << "Lista após clear(): ";
    list.print();
    
	// Verifica se está vazia após clear()
	cout << "A lista está vazia agora? " << (list.empty()? "Sim":"Não") << endl;

	// Teste de cópia com construtor de cópia
	cout << "\nTESTE CONSTRUTOR DE CÓPIA" << endl; 
	list.push_back(100); 
	list.push_back(200); 
	DoublyLinkedList<int> copia(list); 
	cout << "Cópia da lista original:" << endl; 
	copia.print(); 


	cout << "Fim dos testes!" << endl; 

	return 0; 
}

