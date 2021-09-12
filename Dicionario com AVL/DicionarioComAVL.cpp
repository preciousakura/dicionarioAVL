// Nome: Isabel Cristina de Oliveira Lopes
// Matrícula: 493948

#include <iostream>
#include <stdio.h>

using namespace std;

template <typename TC, typename TV>
class DicioAVL {
   public: 
     typedef struct Noh
       {
        TC chave;  TV valor;
        Noh *pai;
        Noh *dir; Noh *esq;
        int altura;
  
        Noh* obter_dir () { return dir; }
        Noh* obter_esq () { return esq; }
        Noh* obter_pai () { return pai; }
        Noh* obter_altura () { return altura; }
       } Noh; 
  
     Noh* obter_raiz () { 
      if(raiz == nullptr) return nullptr;
      return raiz;
     }

   private:
    Noh* raiz;

   public:
   DicioAVL() : raiz(nullptr) {}
   ~DicioAVL () {  }
    class Iterador {
      private: 
      Noh *p;
      
      friend DicioAVL;
      
      public: 
        bool operator == (Iterador j) { return p == j.p; }
        bool operator != (Iterador j) { return p != j.p; }
        void operator ++ () { 
          p = sucessor(p);
        }
        Noh* sucessor(Noh* node) {
          if(node->obter_dir() != nullptr) {
            node = node->obter_dir();
            while(node->obter_esq() != nullptr)
              node = node->obter_esq();
            return node;
          } else {
            if(node->obter_pai() != nullptr) {
              Noh *flag = node->obter_pai();
              while(flag != nullptr && flag->chave < node->chave) flag = flag->obter_pai();
              return flag;
            } else {
              return nullptr;
            }
          }
        }
        Iterador(Noh *pnt) : p(pnt) {}
        TV valor() { return p->valor; }
        TC chave() { return p->chave; }
     };

    Iterador inicio() { 
      if(obter_raiz() == nullptr) return fim();
      Noh *menor = obter_raiz();
      while(menor->obter_esq() != nullptr) {
        menor = menor->obter_esq();
      }
      Iterador i(menor); return i; 
    }
    
    Iterador fim() { 
      Iterador i(nullptr); return i; 
    }
      
    int altura(Noh *node) {
      if (node == nullptr)
        return 0;
      return node->altura;
    }
      
    int maior(int a, int b) {
      return (a > b)? a : b;
    }
    
    Noh *leftRotate(Noh *x) {
      Noh *pai = x->obter_pai();
      Noh *y = x->obter_dir();
      Noh *T2 = y->obter_esq();
      if(T2 != nullptr) T2->pai = x;

      y->esq = x;
      y->pai = pai;
      if(pai == nullptr) raiz = y;
      else {
        if(pai->dir == x)
          pai->dir = y;
        else if(pai->esq == x)
          pai->esq = y;
      }
      x->pai = y;
      x->dir = T2;
 
      x->altura = maior(altura(x->obter_esq()), altura(x->obter_dir())) + 1;
      y->altura = maior(altura(y->obter_esq()), altura(y->obter_dir())) + 1; 
                      
      return y;
    }
    
    Noh *rightRotate(Noh *y) {
      Noh *pai = y->obter_pai();
      Noh *x = y->obter_esq();
      Noh *T2 = x->obter_dir();
      if(T2 != nullptr) T2->pai = y;

      x->dir = y;
      x->pai = pai;
      if(pai == nullptr) raiz = x;
      else {
        if(pai->dir == y)
          pai->dir = x;
        else if(pai->esq == y)
          pai->esq = x;
      }
      y->pai = x;
      y->esq = T2;
 
      y->altura = maior(altura(y->obter_dir()), altura(y->obter_esq())) + 1;
      x->altura = maior(altura(x->obter_dir()), altura(x->obter_esq())) + 1; 
                      
      return x;
    }
    
    void balancear(Noh* node) {
      if(node == nullptr) return;
      node->altura = maior(altura(node->obter_esq()), altura(node->obter_dir())) + 1;
      int balance = balanceamento(node);
      
      if(balance > 1) { 
        if(balanceamento(node->obter_dir()) < 0) {
          rightRotate(node->obter_dir());
          node = leftRotate(node);
        } else {
          node = leftRotate(node);
        }
      } else if(balance < -1) {
        if(balanceamento(node->obter_esq()) > 0) {
          leftRotate(node->obter_esq());
          node = rightRotate(node);
        } else {
          node = rightRotate(node);
        }
      } 

      if(node->pai != nullptr) balancear(node->obter_pai());
  
    }
    
    int balanceamento(Noh *node) {
      if (node == nullptr)
          return 0;
      return altura(node->obter_dir()) - altura(node->obter_esq());
    }
  
   Iterador inserir (TC c, TV v) {
    Noh *n = new(nothrow) Noh;
    if(n == nullptr) return fim();
    
    n->chave = c;
    n->valor = v;
    n->altura = 1;
    n->esq = nullptr;
    n->dir = nullptr;
    n->pai = nullptr;
    
    if(obter_raiz() == nullptr) {
      raiz = n;
    } else {
      Noh* flag = obter_raiz();
      while(flag != nullptr) {
        if(c > flag->chave) {
          if(flag->obter_dir() == nullptr) {
            n->pai = flag;
            flag->dir = n;
            break;
          } flag = flag->obter_dir();
        } else if(c < flag->chave) {
          if(flag->obter_esq() == nullptr) {
            n->pai = flag;
            flag->esq = n;
            break;
          } flag = flag->obter_esq();
        }
      }  
      balancear(n); 
    }

    Iterador i(n);
    return i;
  }
  
  Noh* busca(Noh* flag, TC c) {
    if(flag == nullptr) return flag; 
    if(flag->chave < c) return busca(flag->obter_dir(), c);
    else if(flag->chave > c) return busca(flag->obter_esq(), c);
    else return flag; 
  }

  Iterador buscar(TC c) {
    Noh *flag = busca(obter_raiz(), c);
    if(flag != nullptr) {
      Iterador i(flag);
      return i;
    } return fim();
  };
  
  Noh* remove(Iterador i) {
    if(i.p->altura == 1) { // caso o no a ser removido seja folha
      if(i.p->pai == nullptr) {
        raiz = nullptr;
        return nullptr;
      } else {
        if(i.p->pai->dir != nullptr && i.p->pai->dir->chave == i.chave()) i.p->pai->dir = nullptr;
        else if(i.p->pai->esq != nullptr && i.p->pai->esq->chave == i.chave()) i.p->pai->esq = nullptr;
        
        balancear(i.p->pai);
      }
    } else {
      if(i.p->dir != nullptr && i.p->esq == nullptr) { // tem filho a direita
        if(i.p->pai == nullptr) {
          raiz = i.p->dir;
          i.p->dir->pai = nullptr;
        } else {
          if(i.p->pai->dir->chave == i.chave()) i.p->pai->dir = i.p->dir;
          else if(i.p->pai->esq->chave == i.chave()) i.p->pai->esq = i.p->dir;
          i.p->dir->pai = i.p->pai;
        }
        balancear(i.p->dir); 
      } else if(i.p->esq != nullptr && i.p->dir == nullptr) { // tem filho a esquerda
        if(i.p->pai == nullptr) {
          raiz = i.p->esq;
          i.p->esq->pai = nullptr;
        } else {
          if(i.p->pai->dir->chave == i.chave()) i.p->pai->dir = i.p->esq;
          else if(i.p->pai->esq->chave == i.chave()) i.p->pai->esq = i.p->esq;
          i.p->esq->pai = i.p->pai;
        }
        balancear(i.p->esq);
      } else { // tem os dois filhos
        Iterador sucessor(i.sucessor(i.p));
        Noh* noh_removido = remove(sucessor);
        
        noh_removido->dir = i.p->dir;
        noh_removido->esq = i.p->esq;
        
        if(i.p->dir != nullptr)i.p->dir->pai = noh_removido;
        if(i.p->esq != nullptr)i.p->esq->pai = noh_removido;
        
        if(i.p->pai == nullptr) {
          raiz = noh_removido;
          noh_removido->pai = nullptr;
          
        } else {
          if(i.p->pai->dir->chave == i.chave()) i.p->pai->dir = noh_removido;
          else if(i.p->pai->esq->chave == i.chave()) i.p->pai->esq = noh_removido;
      
          noh_removido->pai = i.p->pai;
        }
        balancear(noh_removido);
      }
    }
    return i.p;
  }

  void remover (Iterador i) {
    if(i == fim()) return;
    remove(i);
    free(i.p);
  }
}; 

int main () {
  DicioAVL<double,double> D; int i;

  D.inserir(271.25, 83);
  D.inserir(81.25, 43);
  D.inserir(-215, 21);
  D.inserir(-290, -51);
    
  
  auto it = D.buscar(81.25); 
  if (it != D.fim()) D.remover(it);

   it = D.buscar(-215); 
  if (it != D.fim()) D.remover(it);

   it = D.buscar(20); 
  if (it != D.fim()) D.remover(it);


  
  for (auto it = D.inicio(); it != D.fim(); ++it) {
    cout << "O codigo de " << it.valor() << " e " << it.chave() << '\n';
  }

}
