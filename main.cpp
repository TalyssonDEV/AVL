#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
// Defini��o da estrutura do n� da �rvore AVL
typedef struct Node {
    int chave;
    struct Node *esquerda;
    struct Node *direita;
    int altura;
} Node;

// Fun��o para criar um novo n�
Node* novoNo(int chave) {
    Node* no = (Node*)malloc(sizeof(Node));
    no->chave = chave;
    no->esquerda = NULL;
    no->direita = NULL;
    no->altura = 1; // Quando um novo n� � inserido, sua altura � inicializada como 1
    return no;
}

// Fun��o para obter a altura de uma �rvore
int altura(Node* no) {
    if (no == NULL)
        return 0;
    return no->altura;
}

// Fun��o para calcular o fator de balanceamento de um n�
int fatorBalanceamento(Node* no) {
    if (no == NULL)
        return 0;
    return altura(no->esquerda) - altura(no->direita);
}

// Fun��o para atualizar a altura de um n�
void atualizarAltura(Node* no) {
    if (no == NULL)
        return;
    no->altura = 1 + ((altura(no->esquerda) > altura(no->direita)) ? altura(no->esquerda) : altura(no->direita));
}

// Fun��o para fazer uma rota��o simples � direita
Node* rotacaoDireita(Node* y) {
    Node* x = y->esquerda;
    Node* T2 = x->direita;

    // Realiza a rota��o
    x->direita = y;
    y->esquerda = T2;

    // Atualiza as alturas dos n�s afetados
    atualizarAltura(y);
    atualizarAltura(x);

    // Retorna a nova raiz (x ap�s a rota��o)
    return x;
}

// Fun��o para fazer uma rota��o simples � esquerda
Node* rotacaoEsquerda(Node* x) {
    Node* y = x->direita;
    Node* T2 = y->esquerda;

    // Realiza a rota��o
    y->esquerda = x;
    x->direita = T2;

    // Atualiza as alturas dos n�s afetados
    atualizarAltura(x);
    atualizarAltura(y);

    // Retorna a nova raiz (y ap�s a rota��o)
    return y;
}

// Fun��o para inserir um n� em uma �rvore AVL
Node* inserir(Node* no, int chave) {
    // Realiza a inser��o como em uma �rvore de busca bin�ria padr�o
    if (no == NULL)
        return novoNo(chave);

    if (chave < no->chave)
        no->esquerda = inserir(no->esquerda, chave);
    else if (chave > no->chave)
        no->direita = inserir(no->direita, chave);
    else // Ignora chaves duplicadas
        return no;

    // Atualiza a altura do n� atual
    atualizarAltura(no);

    // Verifica o fator de balanceamento e realiza as rota��es se necess�rias
    int balanceamento = fatorBalanceamento(no);

    // Caso esquerda-esquerda
    if (balanceamento > 1 && chave < no->esquerda->chave)
        return rotacaoDireita(no);

    // Caso direita-direita
    if (balanceamento < -1 && chave > no->direita->chave)
        return rotacaoEsquerda(no);

    // Caso esquerda-direita
    if (balanceamento > 1 && chave > no->esquerda->chave) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // Caso direita-esquerda
    if (balanceamento < -1 && chave < no->direita->chave) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

// Fun��o para percorrer a �rvore em ordem
void emOrdem(Node* no) {
    if (no != NULL) {
        emOrdem(no->esquerda);
        printf("%d ", no->chave);
        emOrdem(no->direita);
    }
}

void exibirPivoEFilhos(Node* no) {
    if (no != NULL) {
        printf("Pivo: %d\n", no->chave);
        if (no->esquerda != NULL)
            printf("Filho esquerdo: %d\n", no->esquerda->chave);
        if (no->direita != NULL)
            printf("Filho direito: %d\n", no->direita->chave);
    }
}
void mostra( Node * r)
{
    printf("arvore AVL em ordem: ");
    emOrdem(r);
    printf("\n");
    printf("Pivo e seus filhos:\n");
    exibirPivoEFilhos(r);

}

int main() {
    Node* raiz = NULL;
    int valor;

    do
    {
        cout<<"\nInsira um valor na Arvore: ";
        cin>>valor;
        raiz = inserir(raiz,valor);
        mostra(raiz);

    }while(valor != 99);

    cout<<"\nFinalizado!";

    ///raiz = inserir(raiz, 10);




    return 0;
}
