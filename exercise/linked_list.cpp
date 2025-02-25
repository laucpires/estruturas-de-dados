#include "../include/linked_list.hpp"
#include <iostream>

using namespace std;

int main() {
    LinkedList<int> list;

    // 1. Inserção de elementos
    cout << "Inserindo elementos na lista..." << endl;
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    cout << "Lista após push_front(30), push_front(20), push_front(10): ";
    list.print();

    list.insert(1, 25); // Insere 25 na posição 1
    cout << "Lista após insert(25) na posição 1: ";
    list.print();

    // 2. Acesso e modificação de elementos
    cout << "\nAcessando e modificando elementos..." << endl;
    cout << "Elemento no índice 1: " << list[1] << endl;
    list[1] = 35; // Modifica o elemento no índice 1
    cout << "Lista após modificar o elemento no índice 1 para 35: ";
    list.print();

    // 3. Remoção de elementos
    cout << "\nRemovendo elementos..." << endl;
    list.pop_front();
    cout << "Lista após pop_front(): ";
    list.print();

    list.remove(1); // Remove o elemento na posição 1
    cout << "Lista após remove(1): ";
    list.print();

    // 4. Busca e verificação de existência
    cout << "\nBuscando elementos..." << endl;
    int item = 10;
    if (list.contains(item)) {
        cout << "A lista contém o elemento " << item << "." << endl;
        int& found = list.find(item);
        cout << "Elemento encontrado: " << found << endl;
        found = 50; // Modifica diretamente o valor encontrado
        cout << "Lista após modificar o valor encontrado para 50: ";
        list.print();
    } else {
        cout << "O elemento " << item << " não está na lista." << endl;
    }

    // 5. Tamanho e estado da lista
    cout << "\nEstado atual da lista..." << endl;
    cout << "Tamanho da lista: " << list.size() << endl;
    cout << "A lista está vazia? " << (list.empty() ? "Sim" : "Não") << endl;

    // 6. Limpeza da lista
    cout << "\nLimpando a lista..." << endl;
    list.clear();
    cout << "Lista após clear(): ";
    list.print();
    cout << "A lista está vazia agora? " << (list.empty() ? "Sim" : "Não") << endl;

    // 7. Teste do construtor de cópia
    cout << "\nTestando o construtor de cópia..." << endl;
    list.push_front(100);
    list.push_front(200);
    
	// Cria uma cópia da lista original
	LinkedList<int> copy(list);
	cout << "Cópia da lista original:" << endl;
	copy.print();

	cout << "\nFim dos testes!" << endl;

	return 0;
}