/* 
 * Classe lista, uma lista dinamicamente encadeada
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

class noh {
friend class lista;
private:
    equipe elenco; // poderia ser outro tipo de variável
    noh* proximo;
public:
    //noh();
    noh(equipe d);
};

// construindo time chamando seu construtor
noh::noh(equipe d){
    elenco = d;
    proximo = NULL;
}


// lista dinamicamente encadeada
class lista {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista
     // imprime reverso a partir de um nó -> exemplo de uso de recursão
    void imprimeReversoAux(noh* umNoh);
public:
    // construtores e destrutor
    lista();
    lista(const lista& umaLista);
    ~lista();
    // sobrecarga do operador de atribuição
    lista& operator=(const lista& umaLista);  
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


// constrói uma lista inicialmente vazia
lista::lista() {
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

// construtor de cópia
lista::lista(const lista& umaLista) {

}

// destrutor da lista (chama função privada auxiliar)
lista::~lista( ) {
    if(vazia()) {
        throw runtime_error("Remoção em lista vazia!");
    }
    removeTodos();
}    

// remove todos os elementos da lista
void lista::removeTodos( ) {
    while(!vazia()) {
        removeNoInicio();
    }
}    

// sobrecarga do operador de atribuição
lista& lista::operator=(const lista& umaLista){
    // limpa a lista atual
    removeTodos();
     // percorre a lista recebida como parâmetro, copiando os dados
    noh* aux = umaLista.primeiro;
    
    while (aux != NULL) {
        insereNoFim(aux->elenco);
        aux = aux->proximo;  
    }
    
    return *this; 
}  

// insere no final da lista
void lista::insereNoFim(equipe elenco) {
    noh* aux;
    if (vazia()) {
        ultimo = new noh(elenco);
        primeiro = ultimo;
    } else {
        if(primeiro == ultimo) {
            ultimo = new noh(elenco);
            primeiro->proximo = ultimo;
        } else {
            aux = new noh(elenco);
            aux->proximo = primeiro;
            primeiro = aux;
        }
    }
    tamanho++;
    delete aux;
}

// insere no início da lista
void lista::insereNoInicio(equipe elenco) {
    noh* aux;
    if (vazia()) {
        primeiro = new noh(elenco);
        ultimo = primeiro;
    } else {
        if(primeiro == ultimo) {
            primeiro = new noh(elenco);
            primeiro->proximo = ultimo;
        } else {
            aux = new noh(elenco);
            ultimo->proximo = aux;
            ultimo = aux;
        }
    }
    tamanho++;
    delete aux;
 
}

// insere em uma determinada posição da lista
void lista::insereNaPosicao(int posicao, equipe elenco){
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    } 
    if ((posicao > tamanho) || posicao < tamanho) {
        throw runtime_error("Posição Inexistente!");
    }
    if(posicao == 1) {
        insereNoInicio(elenco);
    } else if ( posicao == tamanho) {
        insereNoFim(elenco);
    } else {

    }
}

//procura a posição de um determinado elemento
int lista::procura(string valor) {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    } 

}


// método básico que *percorre* uma lista, imprimindo seus elementos
// poderia percorrer fazendo outra ação (multiplicando valores, por exemplo)
void lista::imprime() {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    } 
}

// verifica se a lista está vazia
inline bool lista::vazia() {
    return (primeiro == NULL);
}
   
void lista::removeNoFim() {
}
    
void lista::removeNoInicio() {
}

int main() {
    lista minhaLista;
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
