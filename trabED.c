/*
 Lista Duplamente Encadeada com No Descritor
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
  if (li != NULL) {
    li->inicio = NULL;
    li->final = NULL;
    li->qtd = 0;
  }

  return li;
}

int insere_inicio(Lista* li, int alg) {
  if (li == NULL)
    return 0;

  Elem *no = (Elem*) malloc(sizeof(Elem));

  if (no == NULL)
    return 0;

  no->algarismo = alg;
  no->ant = NULL;
  no->prox = li->inicio;
  li->inicio = no; // primeiro elemento da lista passa a ser o elemento no
  if (li->qtd == 0) { // lista vazia: insere inicio
    li->final = no;
  }
  li->qtd = li->qtd + 1;
  return 1;
}

int insere_fim(Lista* li, int alg) {
  if (li == NULL)
    return 0;

  Elem *no = (Elem*) malloc(sizeof(Elem));

  if (no == NULL)
    return 0;

  no->algarismo = alg;
  no->prox = NULL;

  if (li->qtd == 0) { // lista vazia: insere inicio
    no->ant = NULL;
    li->inicio = no; // primeiro elemento da lista passa a ser o elemento no
  } else {
    Elem *aux = li->inicio; // aux (ponteiro auxiliar) recebe inicio da lista

    while (aux->prox != NULL) // busca onde inserir
      aux = aux->prox;
    aux->prox = no; // insere depois de aux
    no->ant = aux;
  }
  li->final = no;
  li->qtd = li->qtd + 1;
  return 1;
}

int lista_vazia(Lista *li) {
  if (li->qtd == 0)
    return 1;

  return 0;
}

int remove_inicio(Lista* li) {
  if (li == NULL || lista_vazia(li))
    return 0;

  Elem *no;

  no = li->inicio;
  li->inicio = no->prox;

  if (no->prox != NULL)
    no->prox->ant = NULL;

  li->qtd = li->qtd - 1;

  free(no);

  return 1;
}

void imprime(Lista *li) {
  Elem *aux = li->inicio;
  int i;
  if (lista_vazia(li)) {
    printf("lista vazia\n");
    return;
  }

  for (i = 0; i < li->qtd; i++) {
    printf("%d", aux->algarismo);
    aux = aux->prox;
  }
  printf("\n");
}

void inverte_sinal(Lista *aux) {
  aux->inicio->algarismo *= -1;
}

// remove os zeros a esquerda excedentes
void remove_zeros(Lista* li) {
  while (li->inicio->algarismo == 0 && li->qtd > 1) {
    remove_inicio(li);
  }
}

void libera(Lista *li) {
  Elem *aux;
  int i;
  if (lista_vazia(li))
    return;

  for (i = 0; i < li->qtd; i++) {
    aux = li->inicio;
    li->inicio = aux->prox;

    free(aux);
  }

  li->qtd = 0;
}

// retorna o algarismo presente do no desejado
int retorna_algarismo(Lista *li, int posicao) {
  Elem *aux = li->inicio;
  int i;
  for (i = 0; i < posicao; i++) {
    aux = aux->prox;
  }

  return aux->algarismo;
}

// soma listas que iniciam com o mesmo sinal
Lista* soma(Lista *n1, Lista *n2) {
  Lista* resultado = cria_lista();
  int i;
  int j; // carry
  if (n1->qtd < n2->qtd) {
    while (n1->qtd != n2->qtd) {
      insere_inicio(n1, 0);
    }
  } else {
    while (n1->qtd != n2->qtd) {
      insere_inicio(n2, 0);
    }
  }

  j = 0;
  for (i = n1->qtd - 1; i >= 0; i--) { // -1 devido as posicoes serem de 0 a n-1
    if (retorna_algarismo(n1, i) + retorna_algarismo(n2, i) + j <= 9) {
      insere_inicio(resultado,
          retorna_algarismo(n1, i) + retorna_algarismo(n2, i) + j);
      j = 0;
    } else {
      // pega 10 emprestado
      insere_inicio(resultado,
          retorna_algarismo(n1, i) + retorna_algarismo(n2, i) + j
              - 10);
      j = 1;
      if (i == 0)
        insere_inicio(resultado, 1); // se resultado tiver carry no algarismo mais significativo
    }
  }
  remove_zeros(n1);
  remove_zeros(n2);
  remove_zeros(resultado);

  return resultado;
}

// subtrai duas listas
Lista *subtracao(Lista *n1, Lista *n2) {
  Lista *resultado = cria_lista();
  int i;
  int j; // carry

  if (n1->qtd < n2->qtd) {
    while (n1->qtd != n2->qtd)
      insere_inicio(n1, 0);

  } else {
    while (n1->qtd != n2->qtd)
      insere_inicio(n2, 0);
  }

  j = 0;
  for (i = n1->qtd - 1; i >= 0; i--) { // -1 devido as posicoes serem de 0 a n-1
    if (retorna_algarismo(n1, i) + j >= retorna_algarismo(n2, i)) {
      insere_inicio(resultado,
          retorna_algarismo(n1, i) + j - retorna_algarismo(n2, i));
      j = 0;
    } else {
      // pega 10 emprestado
      insere_inicio(resultado,
          retorna_algarismo(n1, i) + j + 10
              - retorna_algarismo(n2, i));
      j = -1;
    }
  }

  remove_zeros(resultado);
  remove_zeros(n1);
  remove_zeros(n2);

  return resultado;
}

// multiplica duas listas
Lista *multiplicacao(Lista *n1, Lista *n2) {
  Lista *resultado = cria_lista();
  Lista *apenas1 = cria_lista();
  insere_fim(apenas1, 1);
  do {
    resultado = soma(resultado, n1);
    n2 = subtracao(n2, apenas1);

    if (n2->inicio->algarismo == 0)
      remove_zeros(n2);

  } while (n2->inicio->algarismo > 0);

  return resultado;
}

// compara as listas n1 e n2 e retorna a maior
// retorna 1 se n1 maior ou retorna -1 se n2 maior ou retorna 0 se forem iguais
int maior(Lista *n1, Lista *n2) {
  int i;
  if (n1->inicio->algarismo >= 0 && n2->inicio->algarismo < 0)
    return 1;
  if (n2->inicio->algarismo >= 0 && n1->inicio->algarismo < 0)
    return -1;

  if (n1->inicio->algarismo > 0 && n2->inicio->algarismo > 0) {
    if (n1->qtd > n2->qtd)
      return 1;

    if (n1->qtd < n2->qtd)
      return -1;

    for (i = 0; i < n1->qtd; i++) {
      if (retorna_algarismo(n1, i) < retorna_algarismo(n2, i)) {
        return -1;
      }

      if (retorna_algarismo(n1, i) > retorna_algarismo(n2, i)) {
        return 1;
      }
    }
    return 0;
  } else {
    if (n1->qtd > n2->qtd) {
      return -1;
    }

    if (n1->qtd < n2->qtd) {
      return 1;
    }

    for (i = 0; i < n1->qtd; i++) {
      if (retorna_algarismo(n1, i) < retorna_algarismo(n2, i))
        return 1;

      if (retorna_algarismo(n1, i) > retorna_algarismo(n2, i))
        return -1;

    }

    return 0;
  }
}

void soma_subtracao(Lista *n1, Lista *n2) {
  Lista *resultado;

  if (n1->inicio->algarismo >= 0 && n2->inicio->algarismo >= 0) { // n1 e n2 positivo
    resultado = soma(n1, n2);

  } else if (n1->inicio->algarismo < 0 && n2->inicio->algarismo < 0) { // n1 e n2 negativo
    inverte_sinal(n1);
    inverte_sinal(n2);
    resultado = soma(n1, n2);
    inverte_sinal(resultado);
    inverte_sinal(n1);
    inverte_sinal(n2);

  } else if (n1->inicio->algarismo >= 0 && n2->inicio->algarismo < 0) { // n1 positivo e n2 negativo
    inverte_sinal(n2);

    if (maior(n1, n2) == -1) {
      resultado = subtracao(n2, n1);
      inverte_sinal(resultado);
    } else {
      resultado = subtracao(n1, n2);
    }

    inverte_sinal(n2);
  } else { // n1 negativo e n2 positivo
    inverte_sinal(n1);
    if (maior(n1, n2) == 1) {
      resultado = subtracao(n1, n2);
      inverte_sinal(resultado);

    } else {
      resultado = subtracao(n2, n1);
    }
    inverte_sinal(n1);
  }

  remove_zeros(n1);
  remove_zeros(n2);
  imprime(resultado);
  libera(resultado);
}

void operacao(Lista *n1, Lista *n2) {
  Lista *resultado = cria_lista();

  int i;

  // soma
  soma_subtracao(n1, n2);
  inverte_sinal(n2);
  // fim soma

  // subtracao
  soma_subtracao(n1, n2);
  inverte_sinal(n2);
  // fim subtracao

  // multiplicacao
  if (n1->inicio->algarismo < 0 && n2->inicio->algarismo < 0) { // n1 e n2 negativo
    inverte_sinal(n1);
    inverte_sinal(n2);

    resultado = multiplicacao(n1, n2);

    inverte_sinal(n1);
    inverte_sinal(n2);

  } else if (n1->inicio->algarismo >= 0 && n2->inicio->algarismo < 0) { // n1 positivo e n2 negativo
    inverte_sinal(n2);

    resultado = multiplicacao(n1, n2);

    inverte_sinal(resultado);
    inverte_sinal(n2);

  } else if (n1->inicio->algarismo < 0 && n2->inicio->algarismo >= 0) { // n1 negativo e n2 positivo
    inverte_sinal(n1);

    resultado = multiplicacao(n1, n2);
    inverte_sinal(n1);

    inverte_sinal(resultado);

  } else { // n1 e n2 positivo
    resultado = multiplicacao(n1, n2);
  }

  imprime(resultado);
  libera(resultado);
  // fim multiplicacao
}

int main() {
  Lista* n1;
  Lista* n2;
  int algarismo, qtd;

  n1 = cria_lista();
  n2 = cria_lista();

  scanf("%d", &qtd);

  for (; qtd > 0; qtd--) {
    scanf("%d", &algarismo);
    insere_fim(n1, algarismo);
  }

  scanf("%d", &qtd);

  for (; qtd > 0; qtd--) {
    scanf("%d", &algarismo);
    insere_fim(n2, algarismo);
  }

  operacao(n1, n2);

  libera(n1);
  libera(n2);

  return 0;
}