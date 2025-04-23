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
     void removeTodos(); 
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
     void removeNaPosicao(int posicao);
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
 
 inline bool lista::vazia() {
    return tamanho == 0;
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
     int cont = 0;
     noh *auxiliar; 
     noh *novo;
     auxiliar = primeiro;
     if (vazia()) {
         throw runtime_error("Lista vazia!");
     } 
     if ((posicao > tamanho) || posicao < tamanho) {
         throw runtime_error("Posição Inexistente!");
     }
     if(posicao == 1) {
         insereNoInicio(elenco);
     } else if ( posicao == tamanho + 1) {
         insereNoFim(elenco);
     } else {
        
        while(cont < posicao -1) {
            auxiliar = auxiliar->proximo;
            cont++;
        }
        novo = new noh(elenco);
        novo->proximo = auxiliar->proximo;
        auxiliar->proximo = novo;
        tamanho++;
     }
 }
 
 //procura a posição de um determinado elemento
 int lista::procura(string valor) {
    int id = 0;  
    if (vazia()) {
         throw runtime_error("Lista vazia!");
     } 
     return id;
 }
 
 
 // método básico que *percorre* uma lista, imprimindo seus elementos
 // poderia percorrer fazendo outra ação (multiplicando valores, por exemplo)
 void lista::imprime() {
     if (vazia()) {
         throw runtime_error("Lista vazia!");
     } 
 }
 
 void lista::removeNoFim() {
    equipe temp;
    temp = ultimo->elenco;




    //return temp;
 }
     
 void lista::removeNoInicio() {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    }
    noh *auxiliar = primeiro;
    //int removido = auxiliar->id;
    primeiro = primeiro->proximo;
    
    if(ultimo == auxiliar) ultimo = NULL;

    tamanho--;
    delete auxiliar;
    //return removido;
 }
 void lista::removeNaPosicao(int posicao) {
    int cont = 0;
    noh *auxiliar;
    noh *anterior;
    auxiliar = primeiro;
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    } 
    if ((posicao > tamanho) || posicao < tamanho) {
        throw runtime_error("Posição Inexistente!");
    }
    if(posicao == 1) {
        removeNoInicio();
    } else if ( posicao == tamanho) {
        removeNoFim();
    } else {
        
        while(cont < posicao -1) {
            anterior = auxiliar;
            auxiliar = auxiliar->proximo;
            cont++;
        }

    }
    delete auxiliar;

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