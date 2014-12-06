
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "classloader.h"
#include "inicializador.h"
#include "instrucoes.h"
#include "metodos.h"

// vetor com o tamanho dos arrays
struct array *arrayLength;

// n�mero de arrays alocados
u4 numArrays;

// flags
int possuiNome = 0;
int imprimirTela = 0;
int imprimeArq = 0;

// Class Main
char fileSrcName[200], fileTrgtName[100];

void iniciarFlags (int argc, char **argv) {

	if (argc < 2) {
		printf ("Insira o nome do .class: ");
		scanf ("%s", fileSrcName);
		getchar();
	} else {
		strcpy (fileSrcName, argv[1]);
	}
	
	if (argc == 3) {
		strcpy (fileTrgtName, argv[2]);
		imprimeArq = 1;
	} else if (argc > 3) {
		printf ("O programa requer apenas dois argumentos alem do programa. Os demais serao desconsiderados.\n");
	}
}

void inicializar() {
	arrayLength = NULL;
	numArrays = 0;
}

int main(int argc, char **argv) {
	methodInfo *metodoMain;
	FILE *arquivo;

	inicializar();
	iniciarFlags(argc, argv);
	iniciarInstrucoes();			// Popula array de instrucoes
	carregarOpcodeInformacao();

	carregarClass(fileSrcName);

	if((metodoMain = getMainMethod()) == NULL) {
		printf(" Erro: Nao foi possivel localizar metodo main.");
		exit(1);
	}

	prepararMetodo(getClassByIndex(0), metodoMain);
	executarMetodo();
	
	//exibir bytecodes pro arquivo txt, se informado

	return 0;

}
