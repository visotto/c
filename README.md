Trabalho ED 1
=============

##Enunciado
Implemente a soma, subtração e multiplicação de dois números grandes ( n > 10^100 ) com a possibilidade de entrada de números negativos. Utilize listas encadeadas. Você pode usar lista encadeada com ou sem nó cabeça, duplamente encadeada e/ou circular.

O seu programa deve ler os dígitos separados por um espaço, de 2 números n1 e n2 e imprimir o resultado de n1 + n2, n1 - n2, n1 * n2, nessa ordem com um "\n" entre os resultados. Note que o número de dígitos de n1 e n2 não necessariamente é igual.

Por exemplo, para a entrada (para simplificar, neste exemplo, o número não é grande como requerido):  
5  
5 4 3 2 1  
4  
2 3 4 5  

Saída:  
56666  
51976  
127382745  

Você deve desenvolver a biblioteca com as operações da lista escolhida. A implementação das operações da aplicação (leitura dos números, soma, multiplicação e subtração, apresentação do resultado) deve ser implementado em um outro arquivo .c.

Você deve entregar o .c e .h da biblioteca de lista, .c com a implementação da aplicação e o Makefile. Formato do arquivo de entrega: trab1-Nome.zip (ou .tgz).



##Versões

######1.0.2
Indentação refeita, chamadas de funções que estavam comentadas no main apagadas.

Função soma(Lista *n1, Lista *n2) foi corrigida adicionando o caso especial em que ocorre overflow no bit mais significativo: 99+1 = 100, Lista *resultado possui 3 dígitos.


##OBS
Arquivo verificar possui casos de testes já realizados.