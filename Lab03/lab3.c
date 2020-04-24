/*  SCC0503 - Algoritmos e Estruturas de Dados II - Pratica 3 - Índices Secundários */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define TAM 16
#define DEL "*"

typedef int tipoChave;

typedef struct {
	/* aqui devem ser definidos os elementos necessários para compor o índice primário */
	/* voce pode utilizar variáveis estáticas ou dinâmicas */
} index_p;

typedef struct {
	/* aqui devem ser definidos os elementos necessários para compor o índice secundário */
	/* voce pode utilizar variáveis estáticas ou dinâmicas */
} index_s;

typedef struct {
	tipoChave numUSP;
	char nome[TAM];
	char sobrenome[TAM];
	char curso[TAM];
	float nota;
} tipoAluno;

void criaArquivo(FILE *);
//void carregaIndex();
//void insereIndex();
//void ordenaIndex();
//void criaIndexSec();
//void insereIndexSec();
//void removeIndexSec();
void insereRegistro();
//void pesquisaIndex();
//void pesquisaChaveSecundaria();
void pesquisaRegistro();
void imprimeRegistro();
void removeRegistro();
//void removeIndex();
//void salvaIndex();
void finalizaExecucao(FILE *);

int main(void) {
	FILE *df, *index_prim, index_sec;
	int comando= 0;

	do {
	    df= fopen("alunos.dad", "r+");
	    if (df== NULL) criaArquivo(df);

	    /* abrir/criar demais arquivos */

	} while(df== NULL);


	do {
		printf("Operacoes:\n- Gravar\n- Pesquisar chave primaria\n- Pesquisar sobrenome\n- Finalizar\n\n");


		/* Programa deve proceder de acordo com a operacao desejada */


	} while(comando> 0);


	finalizaExecucao(df);

return 0;

}

void criaArquivo(FILE *df) {

    if (df== NULL) {
        df= fopen("alunos.dad", "w");        /* Se nao existir, cria o arquivo de dados */
        fclose(df);
        df= NULL;
    }
    /* Não se esqueça de criar os demais arquivos */
    /* Caso os arquivos existam, abra os arquivos. Os índices devem ser carregados em RAM */
}

void carregaIndex() {
	/* Neste méetodo devem ser implementadas as operações de carregamento de índice */
	/* Voce pode subdividir em métodos específicos para cada índice */
	/* Lembre-se: no primeiro run do programa, todos os arquivos estão vazios. Nos proximos runs, deve ser feita a leitura e o carregamento do estado anterior */
	/* Os índices devem se manter consistentes ao longo das execuções */ 
}

void insereIndex() {
	/* Método para manipulação do index primário */
	/* Neste método devem sem implementadas as operações de inserção de um RRN no índice, que deve ser mantido ordenado */
	/* Neste caso, apenas as operações em tempo de execução (RAM) */
}

void ordenaIndex() {
	/* Método para manipulação do index primário */
	/* A cada operação de inserção ou remoção de um registro, o índice deve ser atualizado para se manter ordenado */
	/* Neste caso, apenas as operações em tempo de execução (RAM) */
}

void criaIndexSec() {
	/* Método para manipulação do index secundário */
	/* Cria uma estrutura semelhante a uma pilha */

}

void insereIndexSec() {
	/* Método para manipulação do index secundário */
	/* Este método pode ser chamado repetidamente durante o carregamento de uma índice pré-carregado ou a cada inserção durante a execução do programa */

}

void removeIndexSec() {
	/* Método para manipulação do index secundário */

}

void insereRegistro() {
	/* Neste método devem sem implementadas as operações de inserção registro no arquivo, lembrando que o índice deve se manter consistente com o arquivo */

}

void pesquisaIndex() {
	/* Aqui a pesquisa deve ser feita pela chave primária no índice por meio de uma busca binária para, então, encontrado o RRN, dar um seek no arquivo para recuperar o registro*/

}

void pesquisaChaveSecundaria() {
	/* Dado um sobrenome (ou parte dele), este método deverá verificar o índice secundário e retornar referências aos registros que contém este sobrenome */

}

void removeIndex() {
	/* Neste método devem sem implementadas as operações de remoção de um RRN no índice, que deve ser mantido ordenado */
	/* Neste caso, apenas as operações em tempo de execução (RAM) */
}


/* demais metodos a serem implementados */

void removeRegistro() {
	/* Pode ser implementada apenas uma remoção lógica */

}

void salvaIndex() {
	/* Antes do programa ser finalizar, o estado final dos índices deve ser gravado em arquivo */

}

void finalizaExecucao(FILE *df) {
    /* Arquivo de dados deve ser fechado com a finalizacao do programa */

}
