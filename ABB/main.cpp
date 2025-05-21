#include <iostream>
#include <cstdlib>
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

class Info {
    public:
        int chave;
        std::string valor;
        bool operator == (const Info& i) { return chave == i.chave; }
        bool operator < (const Info& i) { return chave < i.chave; }
        bool operator > (const Info& i) { return chave > i.chave; }
};

typedef Info Dado; // a arvore guarda informacoes do tipo Dado

class noh {
    friend class abb;
    private:
        Dado dado;
        noh* esq;
        noh* dir;
        noh* pai;
    public:
        noh (Dado d);
        ~noh();
};


ostream& operator << (ostream& saida, const Info& info) {
    saida << '(' << info.chave << ',' << info.valor << ')';
    return saida;
}

enum posicao {dir, esq};

noh::noh(Dado d) {
    dado = d;
    esq = NULL;
    dir = NULL;
    pai = NULL;
}

noh::~noh() {
    delete esq; // não precisa checar se é nulo em C++
    delete dir;
}

class abb {
    private:
        noh* raiz;
        removeTudo(noh* umNoh);
        void percorreEmOrdemAux(noh* atual, int nivel);
    public:
        abb() { raiz = NULL; }
        ~abb();
        void insere(Dado d);
        noh* busca(Dado d, unsigned& nroNosVisitados);
        void percorreEmOrdem();
};

abb::~abb(){
    removeTudo(raiz);
}
void removeTudo(noh* umNoh) {
    removeTudo(umNoh->dir);
    removeTudo(umNoh->esq);
    delete umNoh;
}
void abb::insere(Dado d) {
    noh* novo = new noh(d);
    posicao posInsercao;

    // primeiro caso: árvore vazia
    if (raiz == NULL) {
        raiz = novo;
    } else {
        noh* atual = raiz;
        noh* anterior;

        // encontrando ponto de inserção
        while (atual != NULL) {
            anterior = atual;

            // trocar por >=, se quiser elementos iguais
            if (atual->valor > d) {
                atual = atual->esq;
                posInsercao = esq;
            } else {
                atual = atual->dir;
                posInsercao = dir;
            }
        }

        // inserindo o novo nó na árvore
        novo->pai = anterior;

        if (posInsercao == dir) {
            anterior->dir = novo;
        } else {
            anterior->esq = novo;
        }
    }

}

noh* abb::busca(Dado d, unsigned& nroNosVisitados) {
    noh* atual = raiz;
    nroNosVisitados++;
    while (atual != NULL) {
        if (atual->dado == d) {
            return atual;
        } else if (atual->dado > d) {
            atual = atual->esq;
            busca(atual, nroNosVisitados)
        } else {
            atual = atual->dir;
            busca(atual, nroNosVisitados)
        }
    }

    return atual;
}



void abb::percorreEmOrdem() {
    percorreEmOrdemAux(raiz,0);
    cout << endl;
}

void abb::percorreEmOrdemAux(noh* atual, int nivel) {
    if (atual != NULL) {
        percorreEmOrdemAux(atual->esq, nivel+1);
        cout << atual->valor << "/" << nivel << " ";
        percorreEmOrdemAux(atual->dir, nivel+1);
    }
}

int main() {
    abb arvore;
    Info info;
    char operacao;
    unsigned nroNosVisitados;
    do {
        cin >> operacao;
        switch (operacao) {
            case 'i': // Inserir
                cin >> info.chave >> info.valor;
                arvore.insere(info);
                break;
            case 'b': // Buscar
                try {
                    cin >> info.chave; // ler a chave
                    info = arvore.busca(info, nroNosVisitados);
                    cout << info.valor << ' ' << nroNosVisitados << endl;
                }
                catch (runtime_error& e) {
                    cout << "INEXISTENTE " << nroNosVisitados << endl;
                }
                break;
            case 'e': 
                arvore.percorreEmOrdem();
                break;
            case 'f': // Finalizar execução
                break;
            default:
                cerr << "Comando invalido!\n";
        }
    } while (operacao != 'f');
    return 0;
}