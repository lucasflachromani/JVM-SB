
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "classloader.h"

#include "carregador.h"
#include "methods.h"
#include "instructions.h"
#include "mnemonics.h"

// vetor com o tamanho dos arrays
struct array *arrayLength;

// n�mero de arrays alocados
u4 numArrays;

// flags
int possuiNome = 0;
int imprimirTela = 0;
int imprimirArquivo = 0;

// Class Main
char classeMain[200];

void iniciarFlags(int argc, char **argv) {
	int i;
	for(i = 1; i < argc; i++) {
		if(!strcmp(argv[i], "-v")) {
			imprimirTela = 1;
		} else if(!strcmp(argv[i], "-f")) {
			imprimirArquivo = 1;
		}
		else if(!possuiNome) {
			memcpy(classeMain, argv[i],(strlen(argv[i]) + 1));
			possuiNome = 1;
		}
	}
}

void inicializar() {
	arrayLength = NULL;
	numArrays = 0;
}

int main(int argc, char **argv) {

	method_info *metodoMain;
	FILE *arquivo;

	if(argc > 4) {
		printf(" Erro: Argumentos demais.\n");
		exit(1);
	} else {
		inicializar();
		iniciarFlags(argc, argv);
		iniciarInstrucoes();			// Popula array de instrucoes
		populate_opcode_info();

		if(!possuiNome) {
			printf("\nDigite o nome do arquivo: ");
			scanf("%s", classeMain);
			getchar();
		}

		carregarClass(classeMain);

		if((metodoMain = getMainMethod()) == NULL) {
			printf(" Erro: Não foi possível localizar método main.");
			exit(1);
		}

		prepararMetodo(getClassByIndex(0), metodoMain);
		runMethod();
	}

	return 0;

}
