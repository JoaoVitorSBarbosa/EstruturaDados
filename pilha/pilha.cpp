#include <iostream>
#include <stdexcept>

using namespace std;

struct Item {
    string nome;
    char tipo;
    int valor;
};

// Imprime as informações de um dado qualquer
void imprimir_item(const Item& item) {
    string valor =  to_string(item.valor);
    string tipo(1,item.tipo);
    cout << "Nome:" + item.nome + "\n Tipo: " + tipo + "\nValor: " + valor << endl;
}

class Noh {
    friend class Pilha;
    private:
        Item nItem;
        Noh* nProx;
    public:
        Noh(Item meuItem, Noh* proxNo) {
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


void Pilha::Topo() {
    if (this->Vazia()) {
        throw runtime_error("Erro: pilha vazia!");
    } else {
        Item item = this->mPtTopo->nItem;
        string valor =  to_string(item.valor);
        string tipo(1,item.tipo);
        cout << "Nome:" + item.nome + "\n Tipo: " + tipo + "\nValor: " + valor << endl;
    }
}
bool Pilha::Vazia() {
    return this->mPtTopo == NULL;
}

Item Pilha::Desempilhar() {
    if (this->Vazia()) {
        throw runtime_error("Erro: pilha vazia!");
    } else {
        Item itemAtual = mPtTopo->nItem;
        Noh* topoAtual = mPtTopo;
        this->mPtTopo = mPtTopo->nProx;
        topoAtual->~Pilha();
        return itemAtual;
    }
}

void Pilha::Empilhar(const Item& item) {
    mPtTopo = this->Vazia() ? new Noh(item,NULL) : new Noh(item,mPtTopo->nProx);
}

void Pilha::LimparTudo() {

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
    while (not pilha.Vazia()) {
        imprimir_dado(pilha.Desempilhar());
    }
    cout << endl;
    return 0;
}
