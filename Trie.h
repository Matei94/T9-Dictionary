// Autor: Matei Razvan Madalin, 313CA
// 		  UPB, Facultatea de Automatica si Calculatoare

#include "Treap.h"
#include <iostream>
using namespace std;
			
// Get coresponding position.  
int POZ(char *s) {
	char poz = *s - 'a'; 
	if ( 0 <= poz && poz <= 2)   return 0; 
	if ( 3 <= poz && poz <= 5)   return 1; 
	if ( 6 <= poz && poz <= 8)   return 2; 
	if ( 9 <= poz && poz <= 11)  return 3; 
	if (12 <= poz && poz <= 14)  return 4; 
	if (15 <= poz && poz <= 18)  return 5; 
	if (19 <= poz && poz <= 21)  return 6; 
	if (22 <= poz && poz <= 25)  return 7;
}

struct Trie {
    char are_treap;
    Treap<struct elem> *treap;
    Trie *fiu[8];
 
 	// Constructor
    Trie() {
    	treap = NULL;
        are_treap = 0;
        memset( fiu, 0, sizeof( fiu ) );
    }
    
    // Destructor
    ~Trie() {
    	int i;
    	
    	for(i=0; i<8; i++) {
    		delete fiu[i];
    		fiu[i] = NULL;
    	}
    	delete treap;
    	treap = NULL;
    }
};

Trie *T = new Trie;
Trie *aux;

// Insert element in trie.
void ins( Trie *&nod, char *s, elem e ) {
	if( *s == '\0' ) {
		// The treap in the trie structure is 
		// allocated only at end of words.
		// are_treap keeps track of that.
		if(nod->are_treap == 0) {
			nod->treap = new Treap<elem>;
			nod->are_treap = 1;
		}
		
		// Insert element in coresponding treap.
		nod->treap->insert(nod->treap, e, rand() % 1000);
		return;
	}
	
	if( nod->fiu[ POZ(s) ] == 0 ) {
	    nod->fiu[ POZ(s) ] = new Trie;
	}

	ins(nod->fiu[ POZ(s) ], s+1, e);
}
