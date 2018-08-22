#include <stdio.h>       // Trabalho M2 - Estrutura de Dados II
#include <stdlib.h>     //  Implementação árvore AVL
#include <windows.h>   //   Filipe Mapelli Siqueira


typedef struct no{  //definição do nó da árvore
    struct no *esq;
    int info;
    int alt;
    struct no *dir;
}no;

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
void gotoxy(int x, int y){ //para posicionar o cursor na tela
     COORD coord;
     HANDLE handle;
     handle = GetStdHandle(STD_OUTPUT_HANDLE);
     coord.X = x;
     coord.Y = y;
     SetConsoleCursorPosition(handle, coord);
}

void exibir_arvore(no *raiz, int col, int lin, int desloc){

  if (raiz == NULL) return;
  gotoxy(col, lin);
  printf("(%d)\n", raiz->info);
  if (raiz->esq != NULL)
     exibir_arvore(raiz->esq, col - desloc, lin + 2, desloc / 2 + 1);
  if (raiz->dir != NULL)
     exibir_arvore(raiz->dir, col + desloc, lin + 2, desloc / 2 + 1);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
void inicializar(no *raiz){
    raiz = NULL;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
int diferenca_altura(no *esq, no *dir){
    if (esq == NULL && dir == NULL ){
        return 0;
    }
    if (esq == NULL){
        return dir->alt;
    }
    if (dir == NULL){
        return esq->alt;
    }
    return esq->alt - dir->alt;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
int maior_altura (no *esq, no *dir){
    if (esq == NULL && dir == NULL){
        return 0;
    }
    if (esq == NULL){
        return dir->alt;
    }
    if (dir == NULL){
        return esq->alt;
    }
    if (esq->alt > dir->alt){
        return esq->alt;
    }
    else{
        return dir->alt;
    }
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
void rotacao_simples_esquerda(no **k,no *y){  //ROTAÇÃO SIMPLES À ESQUERDA
    no *t1,*t2,*t3;

    t1 = (*k)->esq;
    t2 = y->esq;
    t3 = y->dir;

    y->esq = (*k);
    y->dir = t3;
    (*k)->esq = t1;
    (*k)->dir = t2;

    (*k)->alt = maior_altura((*k)->esq,(*k)->dir)+1;
    y->alt = maior_altura(y->esq,y->dir)+1;

    (*k) = y;

    printf("\n\n:: RSE com sucesso ::\n\n");
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
void rotacao_dupla_esquerda(no **k, no *y){  //ROTAÇÃO DUPLA À ESQUERDA
    no *z,*t1,*t2,*t3,*t4;

    z = y->esq;
    t1 = (*k)->esq;
    t2 = z->esq;
    t3 = z->dir;
    t4 = y->dir;

    z->esq = (*k);
    z->dir = y;
    (*k)->esq = t1;
    (*k)->dir = t2;
    y->esq = t3;
    y->dir = t4;

    z->alt = maior_altura(z->esq,z->dir)+1;
    (*k)->alt = maior_altura((*k)->esq,(*k)->dir)+1;
    y->alt = maior_altura(y->esq,y->dir)+1;

    (*k)=z;

    printf("\n\n:: RDE executada com sucesso  ::\n\n");
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
void rotacao_simples_direita(no **k, no *x){ // ROTAÇÃO SIMPLES À DIREITA
    no *t1, *t2, *t3;

    t1 = x->esq;
    t2 = x->dir;
    t3 = (*k)->dir;

    x->esq = t1;
    x->dir = (*k);
    (*k)->esq = t2;
    (*k)->dir = t3;

    (*k)->alt = maior_altura((*k)->esq,(*k)->dir)+1;
    x->alt = maior_altura(x->esq,x->dir)+1;

    (*k) = x;

    printf("\n\n:: RSD executada com sucesso  ::\n\n");

}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
void rotacao_dupla_direita(no **k, no *x){  //ROTAÇÃO DUPLA À DIREITA
    no *w, *t1, *t2, *t3, *t4;

    w = x->dir;
    t1 = x->esq;
    t2 = w->esq;
    t3 = w->dir;
    t4 = (*k)->dir;

    w->esq = x;
    w->dir = (*k);
    x->esq = t1;
    x->dir = t2;
    (*k)->esq = t3;
    (*k)->dir = t4;

    w->alt = maior_altura(w->esq,w->dir)+1;
    (*k)->alt = maior_altura((*k)->esq,(*k)->dir)+1;
    x->alt = maior_altura(x->esq,x->dir)+1;

    (*k) = w;

    printf("\n\n:: RDD executada com Sucesso :: \n\n");

}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
int altura(no *aux){  //FUNÇÃO QUE RETORNA ALTURA
    if (aux == NULL){
        return 0;
    }
    else{
        return aux->alt;
    }
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/


void rotacao_avl(no **k){
    no *y,*x;
    printf("\nentrou rotacao AVL\n");
    printf("\naltura esquerda de k = %d, altura direita de k = %d",altura((*k)->esq),altura((*k)->dir));
    if (altura((*k)->esq) > altura((*k)->dir)){
            x = (*k)->esq;
        if (altura(x->esq) >= altura(x->dir)){
            printf("\n\nVai executar uma rotacao simples a direita - RSD");
            rotacao_simples_direita(&(*k),x);
        }else{
            printf("\n\nVai executar uma rotacao dupla a direita - RDD");
            rotacao_dupla_direita(&(*k),x);
        }
    }else{
        y = (*k)->dir;

        if (altura(y->dir) >= altura(y->esq)){
            printf("\n\nVai executar uma rotacao simples a esquerda - RSE");
            rotacao_simples_esquerda(&(*k),y);
        }else{
            printf("\n\nVai executar uma rotacao dupla a esquerda - RDE");
            rotacao_dupla_esquerda(&(*k),y);
        }
    }

}

void balanceamento (no **raiz){
    int alt;
    alt = diferenca_altura((*raiz)->esq,(*raiz)->dir);
    if (alt == 2 || alt == -2){
            rotacao_avl(&(*raiz));
        }
        (*raiz)->alt = maior_altura((*raiz)->esq,(*raiz)->dir) + 1;

}

void verifica_avl (no **raiz){  //percorre a arvore para verificar se houve desequilibrio
    if (*raiz == NULL){
        return;
    }
    balanceamento(&(*raiz));
    verifica_avl(&(*raiz)->esq);
    verifica_avl(&(*raiz)->dir);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
void inserir (no **raiz, int elemento){
    int alt;
    if (*raiz == NULL){
        no *aux = (no*) malloc(sizeof(no));
        aux->esq = NULL;
        aux->dir = NULL;
        aux->info = elemento;
        *raiz = aux;
        aux->alt = 1;  //atribui 1 a altura
        return;
    }else{
        if (elemento < (*raiz)->info){
            inserir(&(*raiz)->esq,elemento);
        }
        if (elemento > (*raiz)->info){
            inserir(&(*raiz)->dir,elemento);
        }
        alt = diferenca_altura((*raiz)->esq,(*raiz)->dir);
        if (alt == 2 || alt == -2){
            rotacao_avl(&(*raiz));
            system("pause");
        }
        (*raiz)->alt = maior_altura((*raiz)->esq,(*raiz)->dir) + 1;
    }

}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
no *busca_maior(no *raiz){
    if(raiz==NULL){
       return NULL;
    }
    else if(raiz->esq == NULL){
       return raiz;
    }
    else
       return busca_maior(raiz->esq);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
void remover (no **raiz,int elemento){
    int alt;
    if (raiz == NULL){
        return;
    }
    if(elemento < (*raiz)->info){
       remover(&(*raiz)->esq,elemento);
    }
    else if(elemento > (*raiz)->info){
       remover(&(*raiz)->dir,elemento);
    }
    else if((*raiz)->esq!=NULL && (*raiz)->dir!=NULL){
       no *aux= NULL;
       aux = busca_maior((*raiz)->dir);
       (*raiz)->info = aux->info;
       remover(&(*raiz)->dir,(*raiz)->info);
    }
    else {
       no *aux = (*raiz);
       if((*raiz)->esq==NULL) {
           *raiz = (*raiz)->dir;
       }
       else {
           *raiz = (*raiz)->esq;
       }
        free(aux);
    }

}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
no *busca_elemento(no *raiz, int elemento){

     no *achou;
     if (raiz == NULL) {
         return NULL;
     }
     if (raiz->info == elemento){
        return raiz;
     }else
         achou = busca_elemento(raiz->esq, elemento);
     if (achou == NULL){
         achou = busca_elemento(raiz->dir, elemento);
     }
     return achou;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
void infixado(no *raiz){ //caminhamento in fixado ESQ, RAIZ, DIR
    if (raiz == NULL){
        return;
    }
    infixado(raiz->esq);
    printf("%d \t",raiz->info);
    infixado(raiz->dir);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
void prefixado (no *raiz){  //caminhamento pré fixado RAIZ, ESQ, DIR
    if (raiz == NULL){
        return;
    }
    printf("%d \t",raiz->info);
    prefixado(raiz->esq);
    prefixado(raiz->dir);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
void posfixado (no *raiz){  //caminhamento pós fixado ESQ, DIR, RAIZ
    if (raiz == NULL){
        return;
    }
    posfixado(raiz->esq);
    posfixado(raiz->dir);
    printf("%d \t",raiz->info);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
no *raiz;                   //PROGRAMA PRINCIPAL - MAIN
int info,op;

int main(){
    system("color 70");
    inicializar(raiz);
    no *aux;
    inicializar(aux);
    while(1){    //construção do menu de opções
        system("cls");
        printf(" TRABALHO ESTRUTURA DE DADOS II");
        printf("\n\n================================");
        gotoxy(6,3);   printf("[1] INSERIR");
        gotoxy(6,5);   printf("[2] REMOVER");
        gotoxy(6,7);   printf("[3] BUSCAR");
        gotoxy(6,9);   printf("[4] MOSTRA PRE-FIXADO");
        gotoxy(6,11);  printf("[5] MOSTRA IN-FIXADO");
        gotoxy(6,13);  printf("[6] MOSTRA POS-FIXADO");
        gotoxy(6,15);  printf("[7] MOSTRA ARVORE");
        gotoxy(6,17);  printf("[8] SAIR");
        gotoxy(6,19);  printf("[ ] DIGITE AQUI OPCAO\n");
        printf("================================");
        gotoxy(7,19);
        scanf("%d",&op);
        fflush(stdin);
        switch (op) {
            case 1 : printf("\n\ndigite o numero para inserir: ");
                     scanf("%d",&info);
                     inserir(&raiz,info);
                     break;
            case 2 : if(raiz == NULL){
                        printf("\n\n:: Arvore Vazia ::\n\n\n");
                     }else{
                        printf("\n\ndigite o numero para remover: ");
                        scanf("%d",&info);
                        aux = busca_elemento(raiz,info); //antes de remover busca o elemento pra saber se ele esta inserido
                        if (aux !=NULL){
                        remover(&raiz,info);
                        printf("\n:: Removido com Sucesso ::\n\n");
                           if (raiz != NULL){
                           verifica_avl(&raiz);}
                        }else{
                           printf("\n:: NAO ACHOU :: Elemento nao encontrado.\n\n");
                        }
                     }
                     system("pause");
                     break;

          case 3 :   if(raiz == NULL){
                        printf("\n\n:: Arvore Vazia ::\n\n\n");
                     }else{
                        printf("\n\ndigite o numero para buscar: ");
                        scanf("%d",&info);
                        aux = busca_elemento(raiz,info);
                        if(aux != NULL)
                            printf(":: ACHOU :: O elemento %d tem altura %d.\n",aux->info,aux->alt); //mostra a altura do no pesquisado
                        else
                            printf(":: NAO ACHOU :: Elemento nao encontrado.\n");
                        printf("\n");
                     }
                     system("pause");
                     break;

            case 4 : if(raiz == NULL){
                        printf("\n\n:: Arvore Vazia ::\n\n\n");
                     } else{
                        printf("\n\n\n");
                        prefixado(raiz);
                        printf("\n\n");
                     }
                     system("pause");
                     break;
            case 5 : if(raiz == NULL){
                        printf("\n\n:: Arvore Vazia ::\n\n\n");
                     } else{
                        printf("\n\n\n");
                        infixado(raiz);
                        printf("\n\n");
                     }
                     system("pause");
                     break;
            case 6 : if(raiz == NULL){
                        printf("\n\n:: Arvore Vazia ::\n\n\n");
                     } else{
                        printf("\n\n\n");
                        posfixado(raiz);
                        printf("\n\n");
                     }
                     system("pause");
                     break;
            case 7:  system("cls");
                     exibir_arvore(raiz,32,4,15);
                     gotoxy(1,1);
                     system("pause");
                     break;
            case 8 : exit(0);
            default: printf("\nOpcao Invalida\t \n \n");
                     system ("pause");
                     break;
        }

    }
}



