#include <iostream>
#include <stdexcept>

using namespace std;

struct Item {
    string nome;
    char tipo;
    int valor;
};

// Imprime as informações de um dado qualquer
void imprimir_dado(const Item& item) {
    cout << "Nome: " << item.nome << " Tipo: " << item.tipo << " Valor: " << item.valor << endl;
}

class Noh {
    friend class Pilha;
    private:
        Item nItem;
        Noh* nProx;
    public:
        Noh(Item meuItem, Noh *proxNo) {
            nItem = meuItem;
            nProx = proxNo;
        }
        ~Noh() {};   
};

class Pilha {
    public:
        // Constrói pilha vazia.
        Pilha();
        // Destrutor que desaloca memória.
        ~Pilha();
        // Retira e retorna o valor que estiver no mPtTopo da pilha.
        // Escreve uma mensagem de erro se não for possível desempilhar.
        Item Desempilhar(); // retorna o mPtTopo da Pilha.
        // Insere um valor na pilha.
        void Empilhar(const Item& d);
        // Apagar todos os dados da pilha.
        void LimparTudo();
        // Imprime o valor que está no mPtTopo sem desempilhar.
        inline void Topo();
        // Informa se a pilha está Vazia.
        inline bool Vazia();
    private:
        Noh* mPtTopo;
};

Pilha::Pilha() {
    mPtTopo = NULL;
}
Pilha::~Pilha() {

}
void Pilha::Topo() {
    if (this->Vazia()) {
        throw runtime_error("Erro: pilha vazia!");
    } 
    imprimir_dado(mPtTopo->nItem);
}
bool Pilha::Vazia() {
    return (!mPtTopo);
}

Item Pilha::Desempilhar() {
    if (this->Vazia()) {
        throw runtime_error("Erro: pilha vazia!");
    }
    Item itemAtual = mPtTopo->nItem;
    Noh* topoAtual = mPtTopo;
    mPtTopo = mPtTopo->nProx;
    delete topoAtual;
    return itemAtual;
}

void Pilha::Empilhar(const Item& item) {
    mPtTopo = this->Vazia() ? new Noh(item,NULL) : new Noh(item,mPtTopo);
}

void Pilha::LimparTudo() {
     while (!this->Vazia()) this->Desempilhar();
}


int main() {
    Pilha pilha;
    Item info;
    char comando;
    do {
        try{
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nome >> info.tipo >> info.valor;
                    pilha.Empilhar(info);
                    break;
                case 'r': // remover
                    imprimir_dado(pilha.Desempilhar());
                    break;
                case 'l': // limpar tudo
                    pilha.LimparTudo();
                    break;
                case 'e': // espiar                
                    pilha.Topo();
                    break;
                case 'f': // finalizar
                    // checado no do-while
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    while (!pilha.Vazia()) {
        imprimir_dado(pilha.Desempilhar());
    }
    cout << endl;
    return 0;
}
