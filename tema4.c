// Autor: Matei Razvan Madalin, 313CA
// 		  UPB, Facultatea de Automatica si Calculatoare

#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include "Trie.h"
#include <iostream>
using namespace std;

int main() {
	int n, n_aux;
	int i, j, ind;
	int look_for;
	
	char c;
	char *word;
	char **words;
	
	elem e;
	
	// Buffer for word reading.
	word = (char *)malloc(100 * sizeof(char));

	FILE *fin, *fout;
	fin  = fopen("date.in", "r");
	fout = fopen("date.out", "w");
	
	/* === First Part === */
	fscanf(fin, "%d", &n);
	
	// n_aux is used for dezallocation.
	n_aux = n;
	
	// Matrix of all words encountered.
	words = (char**)malloc(n * sizeof(char*));
	
	ind = 0;
	for(i=0; i<n; i++) {
		fscanf(fin, "%s", word);
		words[ind] = strdup(word);
		e.cuv = words[ind];
		ind++;
		fscanf(fin, "%d", &e.nr_apar);
	
		ins(T, e.cuv, e);
	}
	
	/* === Second Part === */
	fscanf(fin, "%d", &n);
	for(i=0; i<n; i++) {
		fscanf(fin, "%s", word);
		
		// If '*' not encountered we look for the first apparition.
		// Else we calculate look_for.
		look_for = 1;
		if (strpbrk (word, "*") != NULL) {
			word = strtok(word, "*");
			look_for = atoi(strtok(NULL, "\n"));
			look_for++;
		}
		
		// Go to the coresponding node.
		aux = T;
		for(j=0; j<strlen(word); j++) {
			c = *(word+j);
			aux = aux->fiu[ c - '0' - 2 ];
		}
		
		// The result of the '%' operation could be 0.
		// If so, we look for the last possible word.
		look_for = look_for % aux->treap->nr_nodes;
		if(look_for == 0) look_for = aux->treap->nr_nodes;

		// Search the corresponding word.
		e = aux->treap->findDescendio(look_for);
		fprintf(fout, "%s\n", e.cuv);
		
		// After finding the word, the nr of aparritions must be increased.
		// In order to do that, the entry is erased, modified and inserted again.
		aux->treap->erase(aux->treap, e);
		e.nr_apar++;
		aux->treap->insert(aux->treap, e, rand() % 1000);
	}
		
	// Dezallocation
	free(word);
	for(i=0; i<n_aux; i++) {	
		free(words[i]);
	}
	free(words);
	
	delete T;
	
	fclose(fin);
	fclose(fout);
			
	return 0;
}

