#include <iostream>
#include <stdio.h>

using namespace std;
template <typename TC, typename TV>
class DicioABB {
  private:
    typedef struct Node {
      TC chave;
      TV valor;
      Node *right;
      Node *left;
      Node *dad;
    } Node;
    Node *raiz;
  public:
    class Iterador {
      private:
        Node *p;
        
      public: 
        bool operator == (Iterador j) { return p == j.p; }
        bool operator != (Iterador j) { return p != j.p; }
        void operator ++ () { /* Faz o iterador passar para o sucessor (menor dos elementos maiores que ele) */
          if(p->right != nullptr) {
            p = p->right;
            while(p->left != nullptr)
              p = p->left;
          } else {
            if(p->dad != nullptr) {
              Node *flag = p->dad;
              while(flag != nullptr && flag->chave < p->chave) flag = flag->dad;
              p = flag;
            } 
          }
        }
        Iterador(Node *pnt) : p(pnt) {}
        TV valor() { return p->valor; }
        TC chave() { return p->chave; }
    };
    bool vazio() { return raiz == nullptr; }
    Iterador inicio() { /* Retorna um iterador para o menor elemento do dicionario */
      Node *menor = raiz;
      while(menor->left != nullptr) {
        menor = menor->left;
      }
      Iterador i(menor); return i; 
    }
    Iterador fim() { /* Retorna um iterador cujo ponteiro interno aponta para nulo */
      Iterador i(nullptr); return i; }
    Iterador buscar(TC chave) {
      Node *flag = raiz;
      while(flag != nullptr) {
        if(flag->chave == chave) {
          Iterador i(flag);
          return i;
        }

        if(flag->chave < chave) {
          flag = flag->right;
        } else if(flag->chave > chave) {
          flag = flag->left;
        }
      } 
      return fim();
    };
    void remover(Iterador j) {
      j =  buscar(j.chave());
      if(j != nullptr) {
        cout << "chave encontrada" << endl;
      } else {
        cout << "chave nao encontrada" << endl;
      }
    }
    Iterador inserir(TC chave, TV valor) { /* insere (c,v) no dicionario retornando um iterador para o par inserido ou então para o fim em caso de falha de alocação */ 
      Node *n = new(nothrow) Node;
      if(n == nullptr) return fim();
      
      n->chave = chave;
      n->valor = valor;
      n->left = nullptr;
      n->right = nullptr;
      n->dad = nullptr;
      
      if(vazio()) {
        raiz = n;
      } else {
        Node *flag = raiz;
        while(flag != nullptr) {
          if(flag->chave < chave) {
            if(flag->right == nullptr) {
              n->dad = flag;
              flag->right = n;
              break;
            } flag = flag->right;
          } else {
            if(flag->left == nullptr) {
              n->dad = flag;
              flag->left = n;
              break;
            } flag = flag->left;
          }
        }
      }
      Iterador i(n);
      return i;
    }
    DicioABB() : raiz(nullptr) {}
};

int main() {
  DicioABB<int, char> D;
  // for(int i = 45; i < 55; ++i) {
  //   auto l = D.inserir(i, (char) i);
  //   if(l == D.fim()) { cout << "Erro de insercao\n"; return 1; }
  // }
  
  // auto j = D.buscar(45);
  // if(j != nullptr) {
  //   cout << "Chave encontrada: " << "[chave: " << j.chave() << ", valor: " <<  j.valor() << "]" << '\n';
  // } else {
  //   cout << "Chave nao encontrada" << endl;
  // }
  
  // if(j != nullptr) {
  //   cout << "Chave encontrada: " << "[chave: " << j.chave() << ", valor: " <<  j.valor() << "]" << '\n';
  // } else {
  //   cout << "Chave nao encontrada" << endl;
  // }
  
  
  D.inserir(20, 'a');
  D.inserir(10, 'a');
  D.inserir(33, 'a');
  D.inserir(64, 'a');
  D.inserir(9, 'a');
  D.inserir(8, 'a');
  D.inserir(7, 'a');
  D.inserir(14, 'a');
  D.inserir(29, 'a');
  
  
  
  for(auto it = D.inicio(); it != D.fim(); ++it) {
    cout << "O codigo de [" << it.valor() << "] e " << it.chave() << '\n';
    D.remover(it);
  }
  return 0;
}