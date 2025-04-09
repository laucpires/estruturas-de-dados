#include <cstdlib>
#include <ctime>
#include <iostream>

#include "../include/doubly_linked_list.hpp"

using namespace std;

struct Cliente {
  int filaTempo;
  int atendTempo;
};

class Fila {
 private:
  DoublyLinkedList<Cliente> lista;

 public:
  void push_back(const Cliente& c) { lista.push_back(c); }

  Cliente pop_front() {
    auto temp = lista[0];

    lista.pop_front();

    return temp;
  }

  bool empty() const { return lista.empty(); }

  int size() const { return lista.size(); }
};

struct Caixa {
  Fila fila;
  int tempoFalta;
  int totalClientes;
  int tempoEspera;

  Caixa() : tempoFalta(0), totalClientes(0), tempoEspera(0) {}
};

int main() {
  int numFilas, taxaChegada, duraçãoSimulação;
  cout << "Quantidade de filas: ";
  cin >> numFilas;
  cout << "Taxa de chegada: ";
  cin >> taxaChegada;
  cout << "Duração da simulação: ";
  cin >> duraçãoSimulação;

  Caixa* caixa = new Caixa[numFilas];
  srand(time(0));

  for (int time = 0; time < duraçãoSimulação; ++time) {
    for (int i = 0; i < taxaChegada; ++i) {
      int randValue = rand() % 10;
      int atendTempo = (randValue < 5) ? 1 : (randValue < 8) ? 4 : 6;

      int menorFila = 0;
      for (int j = 1; j < numFilas; ++j) {
        if (caixa[j].fila.size() < caixa[menorFila].fila.size()) {
          menorFila = j;
        }
      }

      Cliente cliente{time, atendTempo};
      caixa[menorFila].fila.push_back(cliente);
    }

    for (int i = 0; i < numFilas; ++i) {
      if (caixa[i].tempoFalta > 0) {
        caixa[i].tempoFalta--;
      } else {
        if (!caixa[i].fila.empty()) {
          Cliente cliente = caixa[i].fila.pop_front();
          caixa[i].tempoEspera += (time - cliente.filaTempo);
          caixa[i].totalClientes++;
          caixa[i].tempoFalta = cliente.atendTempo;
        }
      }
    }
  }

  int totalClientes = 0, tempoEspera = 0;
  for (int i = 0; i < numFilas; ++i) {
    totalClientes += caixa[i].totalClientes;
    tempoEspera += caixa[i].tempoEspera;
  }

  cout << "\n=== Relatório Final ===" << endl;
  cout << "Tempo médio de espera: "
       << (totalClientes > 0 ? (double)tempoEspera / totalClientes : 0)
       << " unidades de tempo" << endl;

  cout << "\nFluxo por caixa:" << endl;
  for (int i = 0; i < numFilas; ++i) {
    cout << "Caixa " << i + 1 << ": " << caixa[i].totalClientes << " clientes"
         << endl;
  }

  int totalPessoas = 0;
  for (int i = 0; i < numFilas; ++i) {
    totalPessoas += caixa[i].fila.size();
  }
  cout << "\nMédia de pessoas por fila: " << (double)totalPessoas / numFilas
       << endl;

  delete[] caixa;
  return 0;
}