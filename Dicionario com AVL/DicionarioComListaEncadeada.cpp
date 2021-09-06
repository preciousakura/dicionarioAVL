#include <stdio.h>
#include <iostream>
using namespace std;
template <typename TC, typename TV>
class DicioLista {
  private:
  
  typedef struct Noh {
    TC chave;
    TV valor;
    Noh *next;
    Noh *prev;
  } Noh;
  
  Noh *first;
  
  public:
  
  class Iterador {
    private:
    Noh *p;
    public:
    bool operator == (Iterador j) { // comparar objetos
      return p == j.p;
    }
    
    bool operator != (Iterador j) { // comparar objetos
      return p != j.p;
    }
    
    void operator ++ () { // comparar objetos
      p = p->next;
    }
    
    Iterador(Noh *pnt) : p(pnt) {}
    
    TV valor() {
      return p->valor;
    }
    
    TC chave() {
      return p->chave;
    }
  };
  
  DicioLista() : first(nullptr) {}
  
  Iterador inicio() {
    Iterador i(first);
    return i;
  };
  
  Iterador fim() {
    Iterador i(nullptr);
    return i;
  }
  
  bool vazio() {
    return first == nullptr;
  }
  
  Iterador inserir(TC c, TV v) {
    Noh *n = new(nothrow) Noh;
    if(n == nullptr) return fim();
    n->chave = c;
    n->valor = v;
    n->prev = nullptr;
    n->next = first;
    if(not vazio()) first->prev = n;
    first = n;
    Iterador i(n);
    return i;
  }
};


int main(){
  DicioLista<int, char> D;
  for(int i = 45; i < 55; ++i) {
    auto l = D.inserir(i, (char) i);
    if(l == D.fim()) { cout << "Erro de insercao\n"; return 1; }
  }
  for(auto it = D.inicio(); it != D.fim(); ++it) {
  
    cout << "O codigo de [" << it.valor() << "] e " << it.chave() << '\n';
  
  }
  return 0;
}