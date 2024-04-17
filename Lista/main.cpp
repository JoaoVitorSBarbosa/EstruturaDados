/* 
 * Classe Lista, uma Lista dinamicamente encadeada
 * 
 * by Joukim, 2017-2019, Estruturas de Dados
 * alterado em 2023 by Renato
 */

#include <iostream>
#include <cstdlib>

using namespace std;


struct equipe{
    string nomeEquipe;
    string lider;
    string linguagem; 
    int qtdMembros;
};

class Noh {
friend class Lista;
private:
    equipe elenco; // poderia ser outro tipo de variável
    Noh* proximo;
public:
    //Noh();
    Noh(equipe d);
};

// construindo time chamando seu construtor
Noh::Noh(equipe d){
    elenco = d;
    proximo = NULL;
}


// Lista dinamicamente encadeada
class Lista {
private:
    Noh* primeiro;
    Noh* ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da Lista
     // imprime reverso a partir de um nó -> exemplo de uso de recursão
    void imprimeReversoAux(Noh* umNoh);
public:
    // construtores e destrutor
    Lista();
    Lista(const Lista& umaLista);
    ~Lista();
    // sobrecarga do operador de atribuição
    Lista& operator=(const Lista& umaLista);  
    // inserção, remoção e procura
    inline void insere(equipe elenco);
    void insereNoFim(equipe elenco);
    void insereNoInicio(equipe elenco);
    void insereNaPosicao(int posicao, equipe elenco);
    int procura(string valor); // retorna a posição do nó com va
    // métodos adicionais (impressão, vazia)
    void imprime();
    void imprimeReverso();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
};


// constrói uma Lista inicialmente vazia
Lista::Lista() {
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

// construtor de cópia
Lista::Lista(const Lista& umaLista) {

}

// destrutor da Lista (chama função privada auxiliar)
Lista::~Lista( ) {
    if(!this->vazia()) this->removeTodos();
}    

// remove todos os elementos da Lista
void Lista::removeTodos( ) {
    while(!this->vazia()) {
        removeNoInicio();
    }
}    

// sobrecarga do operador de atribuição
Lista& Lista::operator=(const Lista& umaLista){
    // limpa a Lista atual
    removeTodos();
     // percorre a Lista recebida como parâmetro, copiando os dados
    Noh* aux = umaLista.primeiro;
    
    while (aux != NULL) {
        insereNoFim(aux->elenco);
        aux = aux->proximo;  
    }
    
    return *this; 
}  

// insere no final da Lista
void Lista::insereNoFim(equipe elenco) {
}

// insere no início da Lista
void Lista::insereNoInicio(equipe elenco) {
    Noh* aux;
    if(primeiro == NULL) {
        primeiro = new Noh(elenco);
    } else {
        aux = new Noh(elenco);
        aux->proximo = primeiro;
        primeiro = aux;
    }
    delete aux;
}

// insere em uma determinada posição da Lista
void Lista::insereNaPosicao(int posicao, equipe elenco){

}

//procura a posição de um determinado elemento
int Lista::procura(string valor) {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    } 

}


// método básico que *percorre* uma Lista, imprimindo seus elementos
// poderia percorrer fazendo outra ação (multiplicando valores, por exemplo)
void Lista::imprime() {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    } 
}

// verifica se a Lista está vazia
inline bool Lista::vazia() {
    return (primeiro == NULL);
}
   
void Lista::removeNoFim() {
    if(this->vazia()) {
        throw runtime_error("Lista vazia!");
    }
    Noh* penultimo; 
    Noh* aux = primeiro;

    while(aux != ultimo) {
        penultimo = aux;
        aux = aux->proximo;
    }
    penultimo->proximo = NULL;
    aux = ultimo;
    ultimo = penultimo;
    delete aux;
    delete penultimo;
}
    
void Lista::removeNoInicio() {
    if(this->vazia()) {
        throw runtime_error("Lista vazia!");
    }
    Noh* aux = primeiro;
    primeiro = aux->proximo;
    delete aux;

}

int main() {
    Lista minhaLista;
    equipe info;
    char comando;
    int posicao;
    string nomeEquipe;

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoInicio(info);
                    break;
                case 'h': // inserir
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoFim(info);
                    break;             
                case 'm': // inserir
                    cin >> posicao;
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNaPosicao(posicao,info);
                    break;             
                case 's': // remover
                    cin >> nomeEquipe;
                    cout << minhaLista.procura(nomeEquipe) <<endl;
                    break;                    
                case 'r': // remover
                    minhaLista.removeNoInicio();
                    break;
                case 'a': // remover
                    minhaLista.removeNoFim();
                    break;                                   
                case 'p': // limpar tudo
                    minhaLista.imprime();
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
    cout << endl;
    return 0;
}

