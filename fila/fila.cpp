 #include <iostream>

 using namespace std;
 
 const int FILAVAZIA = -1;
 const int CAPACIDADE_FILA = 6;
 
 struct Dado {
     string nome;
     int premio;
     char tipo;
     int tempo;
 };
 
 // Imprime informações de um dado qualquer.
 void imprimir_dado(const Dado& umDado){
     cout << "Nome: " << umDado.nome << " Premio: " << umDado.premio << " Tipo: " << umDado.tipo << " tempo: " << umDado.tempo << endl;
 }
 
 class Fila {
     private:
         Dado fila[CAPACIDADE_FILA];
         int primeiraPosVazia;
     public:
         // Constrói fila vazia.
         Fila();
         // Destrutor que desaloca memória.
         ~Fila();
         // Retira e retorna o elemento que estiver na primeira posição.
         Dado Desenfileirar(); 
         // Insere um elemento na fila.
         void Enfileirar(const Dado& d);
         // Apagar todos os dados da fila.
         void LimparTudo();
         // Imprime os valores do elemento que está na frente da fila, sem Desenfileirar.
         inline void PrimeiroDaFila();
         // Informa se a fila está Vazia.
         inline bool Vazia();
         // Informa se a fila está Cheia.
         inline bool Cheia();
         //Contabiliza premios
         int Contabilizar(char tipo);
         int GetPrimeiraPosVazia();
 };
 
 Fila::Fila(){
     primeiraPosVazia = 0;
 }
 
 Fila::~Fila() {
 
 }
 int Fila::GetPrimeiraPosVazia() {
    return primeiraPosVazia;
 }
 Dado Fila::Desenfileirar() {
     if (this->Vazia()) throw runtime_error("Erro: Fila vazia!");
     Dado dado = fila[0];
     for(int i = 0; i < primeiraPosVazia; i++) {
         fila[i] = fila[i + 1];
     }
     primeiraPosVazia--;
     return dado;
     
 }
 
 void Fila::Enfileirar(const Dado& d) {
     if (this->Cheia()) throw runtime_error("Erro: Fila cheia!");
     fila[primeiraPosVazia] = d;
     primeiraPosVazia ++;
 }
 
 void Fila::LimparTudo() {
     while(!this->Vazia()) Desenfileirar();
 }
 
 void Fila::PrimeiroDaFila() {
     if (this->Vazia()) throw runtime_error("Erro: Fila vazia!");
     imprimir_dado(fila[0]);    
 }
 
 bool Fila::Vazia() {
     return (this->primeiraPosVazia == 0);
 }
 
 bool Fila::Cheia() {
     return (this->primeiraPosVazia >= 5);
 }
 int Fila::Contabilizar(char tipo) {
    Fila aux1,aux2;
    int cont = 0;
    int total = 0;
    int tam = 0;
    Dado atual;

    tam = GetPrimeiraPosVazia();
    for(int i = 0; i < tam; i++) {
        atual = Desenfileirar();
        aux1.Enfileirar(atual);
        if(atual.tipo == tipo) {
            total = total + atual.premio;
            aux2.Enfileirar(atual);
            cont++;
        }
    }

    for(int i = 0; i <  tam; i++) {
        if(!aux1.Vazia()) {
            atual = aux1.Desenfileirar();
            if(atual.tipo != tipo) {
                aux2.Enfileirar(atual);
                cont++;
            }
        }
    }

    for(int i = 0; i < tam; i++) {
        atual = aux2.Desenfileirar();
        Enfileirar(atual);
    }
    return total;
 }
 
 int main() {
     Fila fila;
     Dado info;
     char comando;
     char tipo;
     do {
         try {
             cin >> comando;
             switch (comando) {
                 case 'i': // inserir
                     cin >> info.nome >> info.premio >> info.tipo >> info.tempo;
                     fila.Enfileirar(info);
                     break;
                 case 'r': // remover
                     imprimir_dado(fila.Desenfileirar());
                     break;
                 case 'l': // limpar tudo
                     fila.LimparTudo();
                     break;
                 case 'e': // espiar 
                     if(!fila.Vazia())               
                         fila.PrimeiroDaFila();
                     else
                         cout << "Erro: Fila vazia!"<< endl;
                     break;
                case 'p':
                    cin >> tipo;
                    cout << fila.Contabilizar(tipo) << endl;
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
     while (not fila.Vazia()) {
         imprimir_dado(fila.Desenfileirar());
     }
     cout << endl;
     return 0;
 }
