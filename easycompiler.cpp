//BRUNO GUILHERME SPIRLANDELI MARINI     17037607
//MARCOS AURELIO TAVARES DE SOUSA FILHO  17042284

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 10
#define DIM 16

typedef struct {
	char var_nome[10];
	int tipo;//0:int
	int valor;
}variavel;

typedef struct no {
	variavel info;
	no* link;
}no;

void criar_vazia(no *pri[]);
int inserir(no *pri[], variavel V);
no* buscar(no* pri[], char nome[]);
int hash(char nome[]);
void contabiliza(no *pri[], char exp[]);

int main()
{
	no* pri[MAX], *ende;
	variavel v[10];
	char nome[10]; //"+" "-" "*" "/"
	char aux[40];
	int i = 0;

	criar_vazia(pri); //ler info para V

	do{
		
		scanf("%s", aux);
		if (!strcmp(aux, "int") || !strcmp(aux, "float") || !strcmp(aux, "char"))
		{
			scanf("%s %i", v[i].var_nome, &v[i].valor);



			getchar();

			if (strcmp(aux, "int") == 0)
				v[i].tipo = 0;
			else if (strcmp(aux, "float") == 0)
				v[i].tipo = 1;
			else if (strcmp(aux, "char") == 0)
				v[i].tipo = 2;
			else
				v[i].tipo = -1;

			if (v[i].var_nome != NULL && v[i].tipo != -1)
				if (!inserir(pri, v[i])) {
					printf("ERRO!");
					break;
				}
			i++;
		}
		else
		{
			contabiliza(pri, aux);
		}

	} while (true);

	
	system("pause");
}

void criar_vazia(no *pri[])
{
	for (int i = 0; i < MAX; i++) 
		pri[i] = NULL;
}

int inserir(no *pri[], variavel V)
{
	no* novo = (no*)malloc(sizeof(no));
	
	int p;
	
	if (!novo) 
		return 0;
	
	novo->info = V;
	p = hash(V.var_nome);

	pri[p] = novo;
	

	return 1;

}

no* buscar(no* pri[], char nome[])
{
	no* address;
	
	int p = hash(nome);
	address = pri[p];
	
	while (address) 
	{
		if (strcmp(address->info.var_nome, nome) == 0)
			return address;

		address = address->link;
	}

	return NULL;
}
int hash(char nome[])
{
	int j = 0, soma = 0;

	while (nome[j] != '\0')
	{
		soma += nome[j];
		j++;
	}
	
	return (soma % MAX);
}
void contabiliza(no*pri[], char exp[])
{
	//aa=bb+cc;
	char *t;
	t = exp;
	int i = 0;
	char res[20], opc, op1char[20], op2char[20];
	no *op1, *op2;

	while (isalpha(*t))
	{
		res[i] = *t;
		t++;
		i++;
	}
	res[i] = '\0';
	no *resultado = buscar(pri, res);
	t++;//para anular o '='
	i = 0;
	while (isalpha(*t))
	{
		op1char[i] = *t;
		t++;
		i++;
	}
	op1char[i] = '\0';
	opc = *t;
	t++;
	op1 = buscar(pri, op1char);
	i = 0;
	while (isalpha(*t))
	{
		op2char[i] = *t;
		t++;
		i++;
	}
	op2char[i] = '\0';
	op2 = buscar(pri, op2char);

	switch (opc)
	{
	case '+':
		resultado->info.valor = op1->info.valor + op2->info.valor;
		printf("\n%s = %s + %s\n%s = %i + %i\n%s = %i\n\n", resultado->info.var_nome, op1->info.var_nome, op2->info.var_nome, resultado->info.var_nome, op1->info.valor, op2->info.valor, resultado->info.var_nome, resultado->info.valor);
		break;
	case '-':
		resultado->info.valor = op1->info.valor - op2->info.valor;
		printf("\n%s = %s + %s\n%s = %i - %i\n%s = %i\n\n", resultado->info.var_nome, op1->info.var_nome, op2->info.var_nome, resultado->info.var_nome, op1->info.valor, op2->info.valor, resultado->info.var_nome, resultado->info.valor);
		break;
	case '*':
		resultado->info.valor = op1->info.valor * op2->info.valor;
		printf("\n%s = %s + %s\n%s = %i * %i\n%s = %i\n\n", resultado->info.var_nome, op1->info.var_nome, op2->info.var_nome, resultado->info.var_nome, op1->info.valor, op2->info.valor, resultado->info.var_nome, resultado->info.valor);
		break;
	case '/':
		resultado->info.valor = op1->info.valor / op2->info.valor;
		printf("\n%s = %s + %s\n%s = %i / %i\n%s = %i\n\n", resultado->info.var_nome, op1->info.var_nome, op2->info.var_nome, resultado->info.var_nome, op1->info.valor, op2->info.valor, resultado->info.var_nome, resultado->info.valor);
		break;
	}
}
