#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Limite_Nome 500
#define Limite_Tipo 500
#define Limite_Descricao 500

/*Everton Jose Santana*/

/*Dados de um prato*/
struct Prato {
    int codigo;
    char *nome;
    char *tipo; /*(massa, carne, peixe,...)*/
    char *descricao;
    float preco; /*em reais*/
    struct Prato *proximo;
};
typedef struct Prato TpPrato;

/*Dados de um cardapio*/
struct Cardapio {
    int qntPratos; /*quantidade de pratos do cardapio*/
    struct Cardapio *primeiro;
};
typedef struct Cardapio TpCardapio;

/*Inserir um prato*/
void InserirPrato (TpPrato *p, int cod, char *nm, char *tp, char *desc, float prec){
    p->codigo= cod;
    p->nome=(char*)malloc((strlen(nm)+1)*sizeof(char));
    strcpy(p->nome,nm);
    p->tipo=(char*)malloc((strlen(tp)+1)*sizeof(char));
    strcpy(p->tipo,tp);
    p->descricao=(char*)malloc((strlen(desc)+1)*sizeof(char));
    strcpy(p->descricao,desc);
    p->preco= prec;
}

/*Preparar cardapio */
void IniciarCadapio(TpCardapio *c){
    c->qntPratos=0;
    c->primeiro=NULL;
}

/*Inserir prato no cardapio****1 indica que o prato foi inserido, 0 indica que nao ha espaco*/
int InserirPratoCardapio (TpCardapio *c, int cod, char *nm, char *tp, char *desc, float prec){
    TpPrato *aux1, *aux2;

    aux1=(TpPrato*)malloc(sizeof(TpPrato));
    if(aux1==NULL){
        return 0;
    }else{
        InserirPrato(aux1, cod, nm, tp, desc, prec);
        aux2=c->primeiro;
        c->primeiro=aux1;
        aux1->proximo=aux2;
        c->qntPratos++;
        return 1;
    }
}

/*Imprimir cada prato*/
void ImprimirPrato (TpPrato q){
    printf("Co'digo do prato:%d\n\n Nome do prato:%s\n Tipo:%s\n Descrição:%s\n Preco: %.02f\n\n",
    q.codigo, q.nome, q.tipo, q.descricao, q.preco);
}

/*Imprimir todo cardapio*/
void ImprimirCardapio (TpCardapio c){
    TpPrato *q;
    printf("O cardapio possui %d prato(s). Ele(s) e' (sao):\n\n", c.qntPratos);
    for (q=c.primeiro;q!=NULL;q=q->proximo){
    ImprimirPrato(*q);
    }
}

/*Sinalizar que encontrou o prato específico*/
int EncontrouPrato(int cod, TpPrato *pprato){
    if(pprato==NULL){
        return 0;
    }
    if (cod==pprato->codigo){
        return 1;
    }else{
        return 0;
    }
}

/*Identificar prato pelo código*/
int EncontrarPrato(TpCardapio*c, int cod, char **nm, char **tp, char **desc, float *prec){
    TpPrato *pprato, *anterior;

    pprato=c->primeiro;
    anterior=NULL;
    while (!EncontrouPrato(cod, pprato)&&(pprato!=NULL)){
        anterior = pprato;
        pprato=pprato->proximo;
    }

    if (pprato==NULL){
        return 0;
    }else{
        *nm=pprato->nome;
        *tp=pprato->tipo;
        *desc=pprato->descricao;
        *prec=pprato->preco;
         printf ("O elemento %d esta' no cardapio!\n O prato e' %s, cujo tipo eh' %s.\n Ele e' %s e custa apenas %.2f. Compre ja' o seu!\n\n", cod, *nm, *tp, *desc, *prec);
        return 1;
    }
}

/*Remover prato*/
int RemoverPrato(TpCardapio*c, int cod, char **nm, char **tp, char **desc, float *prec){
    TpPrato *pprato, *anterior;

    pprato=c->primeiro;
    anterior=NULL;
    while (!EncontrouPrato(cod, pprato)&&(pprato!=NULL)){
        anterior = pprato;
        pprato=pprato->proximo;
    }

    if (pprato==NULL){
        return 0;
    }else{
        *nm=pprato->nome;
        *tp=pprato->tipo;
        *desc=pprato->descricao;
        *prec=pprato->preco;
        if (pprato==c->primeiro){
            c->primeiro=pprato->proximo;
        }else {
            anterior->proximo=pprato->proximo;
        }
     c->qntPratos--;
     free(pprato);
     return 1;
    }
}

/*Sinalizar que encontrou um prato barato*/
int EncontrouBarato(float prec, TpPrato *pprato){
    if(pprato==NULL){
        return 0;
    }
    if (prec<pprato->preco){
        return 1;
        }
}

/*Determinar o prato mais barato*/
int DeterminarBarato(TpCardapio*c, int *cod, float prec){
TpPrato *pprato, *anterior;

    pprato=c->primeiro;
    anterior=NULL;
    while (!EncontrouBarato(prec, pprato)&&(pprato!=NULL)){
        anterior = pprato;
        pprato=pprato->proximo;
    }

    if (pprato==NULL){
        return 0;
    }else{
        prec=pprato->preco;
        *cod=pprato->codigo;
         return 1;
     }
}


int main(){
TpCardapio cardapio;
int codigo;
float preco;
char nome[Limite_Nome], tipo[Limite_Tipo], descricao[Limite_Descricao];
int opc=10;

IniciarCadapio(&cardapio);
InserirPratoCardapio(&cardapio, 9003, "Bife grelhado", "Carne", "O melhor da regiao",6.99);
InserirPratoCardapio(&cardapio, 9002, "File de merluza", "Peixe", "Frito com azeite",9.99);
InserirPratoCardapio(&cardapio, 9001, "Lasanha", "Massa", "Igual da vovo", 5.99);

printf("\n     Gerenciamento de um Restaurante       \n");
printf("    _________________________________      \n\n\n");

/*e) Menu de opcoes*/
    while (opc!=0){
      printf("Escolha uma entre as seguintes opcoes:\n\n 0:Sair\n 1:Inserir novo Prato ao Cardapio\n 2:Imprimir Pratos do Cardapio\n 3:Com o codigo, mostrar detalhes do Prato\n 4:Com o codigo, remover Prato do Cardapio\n 5:Consultar Prato mais barato\n\n");
      scanf("%d",&opc);
            switch (opc) {
            case 1:
                printf("Codigo:\t");
                scanf("%d", &codigo);
                printf("Nome:\t");
                gets(nome);
                gets(nome);
                printf("Tipo:\t");
                gets(tipo);
                printf("Descricao:\t");
                gets(descricao);
                printf("Preco:\t");
                scanf("%f", &preco);
                InserirPratoCardapio(&cardapio, codigo, nome, tipo, descricao, preco);
                printf("\n");
            break;
            case 2:
                printf("Eis o seu cardapio:\n");
                ImprimirCardapio(cardapio);
            break;
            case 3:
                printf("Digite o codigo do prato que deseja consultar:\n");
                scanf("%d", &codigo);
                EncontrarPrato(&cardapio, codigo, &nome, &tipo, &descricao, &preco);
            break;
            case 4:
                printf("Digite o codigo do prato que deseja remover:\n");
                scanf("%d", &codigo);
                RemoverPrato(&cardapio, codigo, &nome, &tipo, &descricao, &preco);
            break;
            case 5:
                DeterminarBarato(&cardapio, &codigo, preco);
                printf("O prato mais barato e' o de codigo %d.\n Para informacoes do prato, digite 3.\n\n",  codigo);
            break;
            case 0:
                return 0;
            break;
            default:
                printf("Opcao invalida\n\n");
            }
    }
}
