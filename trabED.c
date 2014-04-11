/*
Lista Encadeada com No Descritor
Usa um no especial chamado de descritor para
armazenar inicio, final e qtd de elementos da lista
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct elemento {
	struct elemento *ant;
	int algarismo;
	struct elemento *prox;
} Elem;

typedef struct descritor {
	struct elemento *inicio;
	struct elemento *final;
	int qtd;
} Lista;

Lista* cria_lista() {
	Lista* li = (Lista*) malloc(sizeof(Lista));
	if(li != NULL) {
		li->inicio = NULL;
		li->final = NULL;
		li->qtd = 0;
	}
	return li;
}

int insere_inicio(Lista* li, int alg){
	if(li == NULL)
		return 0;
		
	Elem *no = (Elem*) malloc(sizeof(Elem));
	
	if(no == NULL)
		return 0;
		
	no->algarismo = alg;
	no->ant = NULL;
	no->prox = li->inicio;
	li->inicio = no; // primeiro elemento da lista passa a ser o elemento no
	if(li->qtd == 0) { //lista vazia: insere inicio
		li->final = no;
	} 
	li->qtd=li->qtd+1;
	return 1;
}

int insere_fim(Lista* li, int alg){
	if(li == NULL)
		return 0;
		
	Elem *no = (Elem*) malloc(sizeof(Elem));
	
	if(no == NULL)
		return 0;
		
	no->algarismo = alg;
	no->prox = NULL;
	
	if(li->qtd == 0) { //lista vazia: insere inicio
		no->ant = NULL;
		li->inicio = no; // primeiro elemento da lista passa a ser o elemento no
	} else {
		Elem *aux = li->inicio; // aux (ponteiro auxiliar) recebe inicio da lista
		
		while (aux->prox != NULL) //busca onde inserir
			aux = aux->prox;
		aux->prox = no; //insere depois de aux
		no->ant = aux;
	}
	li->final = no;
	li->qtd=li->qtd+1;
	return 1;
}

int lista_vazia(Lista *li){
	if(li->qtd == 0)
		return 1;
	return 0;
}

void imprime(Lista *li) {
	Elem *aux = li->inicio;
	int i = 0;
	if(lista_vazia(li)){
		printf("lista vazia\n");
		return;
	}
	for( i = 0; i < li->qtd; i++){
		printf("%d ", aux->algarismo);
		aux = aux->prox;
	}
	printf("\n");
}

void libera(Lista *li){
	Elem *aux;
	int i = 0;
	if(lista_vazia(li)){
		return;
	}
	for(i = 0; i < li->qtd; i++){
		aux = li->inicio;
		li->inicio = aux->prox;
		free(aux);
	}
	li->qtd = 0;
}

int retorna_algarismo(Lista *li, int posicao){
	Elem *aux = li->inicio;
	int i;
	for(i = 0; i < posicao; i++){
		aux = aux->prox;
	}
//	printf("%d\n", aux->algarismo);
	return aux->algarismo;
}

// soma listas que iniciam com o mesmo sinal
Lista* soma(Lista *n1, Lista *n2){
	Lista* resultado = cria_lista();
	int i, j;
	
	if(n1->qtd < n2->qtd){
		while(n1->qtd != n2->qtd){
			insere_inicio(n1, 0);
		}
	}else{
		while(n1->qtd != n2->qtd){
			insere_inicio(n2, 0);
		}
	}

	j = 0;
	for(i = n1->qtd - 1; i >= 0; i--){ // -1 devido as posicoes serem de 0 a n-1
		if(retorna_algarismo(n1, i) + retorna_algarismo(n2, i) + j <= 9){
			insere_inicio(resultado, retorna_algarismo(n1, i) + retorna_algarismo(n2, i) + j);
			j = 0;
		}else{
			insere_inicio(resultado, retorna_algarismo(n1, i) + retorna_algarismo(n2, i) + j - 10);
			j = 1;
		}
	}
	
	return resultado;
}

Lista *subtracao(Lista *n1, Lista *n2){
	Lista *resultado = cria_lista();
	int i, j;
	
	if(n1->qtd < n2->qtd){
		while(n1->qtd != n2->qtd){
			insere_inicio(n1, 0);
		}
	}else{
		while(n1->qtd != n2->qtd){
			insere_inicio(n2, 0);
		}
	}
	
	j = 0;
	for(i = n1->qtd - 1; i >= 0; i--){ // -1 devido as posicoes serem de 0 a n-1
		if(retorna_algarismo(n1, i) + j >= retorna_algarismo(n2, i)){
			insere_inicio(resultado, retorna_algarismo(n1, i) + j - retorna_algarismo(n2, i));
			j = 0;
		}else{
			insere_inicio(resultado, retorna_algarismo(n1, i) + j + 10 - retorna_algarismo(n2, i));
			j = -1;
		}
	}
	
	return resultado;
	
}

// retorna 1 se n1 maior; retorna -1 se n2 maior ou retorna 0 se forem iguais
int maior(Lista *n1, Lista *n2){
	int i;
	if(n1->inicio->algarismo > 0 && n2->inicio->algarismo < 0)
		return 1;
	if(n2->inicio->algarismo > 0 && n1->inicio->algarismo < 0)
			return -1;
	
	if(n1->inicio->algarismo > 0 && n2->inicio->algarismo > 0){
		if(n1->qtd > n2-> qtd){
			return 1;
		}
		if(n1->qtd < n2->qtd){
			return -1;
		}
		
		for(i = 1; i < n1->qtd; i++){
			if(retorna_algarismo(n1, i) < retorna_algarismo(n2, i)){
				return -1;
			}
			if(retorna_algarismo(n1, i) > retorna_algarismo(n2, i)){
				return 1;
			}
		}
		return 0;
	}else{
		if(n1->qtd > n2-> qtd){
				return -1;
			}
			if(n1->qtd < n2->qtd){
				return 1;
			}
			
			for(i = 1; i < n1->qtd; i++){
				if(retorna_algarismo(n1, i) < retorna_algarismo(n2, i)){
					return 1;
				}
				if(retorna_algarismo(n1, i) > retorna_algarismo(n2, i)){
					return -1;
				}
			}
			return 0;
	}
	
}

void operacao(Lista *n1, Lista *n2){
	Lista *resultado;
	int i;
	
	// soma
	if(n1->inicio->algarismo > 0 && n2->inicio->algarismo > 0){
		resultado = soma(n1, n2);
//		printf("fn1");
	} else if(n1->inicio->algarismo < 0 && n2->inicio->algarismo < 0){
		n1->inicio->algarismo *= -1;
		n2->inicio->algarismo *= -1;
		resultado = soma(n1, n2);
		resultado->inicio->algarismo *= -1;
		n1->inicio->algarismo *= -1;
		n2->inicio->algarismo *= -1;
//		printf("fn2");
	} else if(n1->inicio->algarismo > 0 && n2->inicio->algarismo < 0){
		n2->inicio->algarismo *= -1;
//		printf("fn3");
		if(maior(n1, n2) == -1){
			resultado = subtracao(n2, n1);
			resultado->inicio->algarismo *= -1;
		}else{
			resultado = subtracao(n1, n2);
		}
	} else {
//		printf("fn4");
		n1->inicio->algarismo *= -1;
		if(maior(n1, n2) == 1){
			resultado = subtracao(n1, n2);
			resultado->inicio->algarismo *= -1;
		}else{
			resultado = subtracao(n2, n1);
		}
	}
	imprime(resultado);
	// fim soma
}

int main() {
	Lista* n1;
	Lista* n2;
	
	n1 = cria_lista();
	n2 = cria_lista();
	
//	insere_fim(n1, 5);
//	insere_fim(n1, 1);
//	insere_fim(n1, 9);
	insere_inicio(n1, 5);
	insere_inicio(n1, 1);
	insere_inicio(n1, 9);
	insere_inicio(n2, 6);
	insere_inicio(n2, 1);
	

	imprime(n1);
	imprime(n2);
	//libera(n1);
//	n1 = subtracao(n1, n2);
	
//	imprime(n1);
	operacao(n1, n2);
	n2->inicio->algarismo *= -1;
	operacao(n1, n2);
//	retorna_algarismo(n1, 0);	
//	retorna_algarismo(n1, 1);
//	retorna_algarismo(n1, 2);

}
