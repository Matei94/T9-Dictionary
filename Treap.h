// Autor: Matei Razvan Madalin, 313CA
// 		  UPB, Facultatea de Automatica si Calculatoare

#ifndef __TREAP_H
#define __TREAP_H

#include <iostream>
using namespace std;

struct elem {
	char *cuv;
	int nr_apar;
};

template <typename T> 
struct Treap {
	T key;
	bool nil;
	int priority;
	int nr_nodes;
	Treap<T> *left, *right;

	// Constructor
	Treap() : priority(-1), left(NULL), right(NULL), nil(true), nr_nodes(0) {}
	
	// Destructor
	~Treap() {
		delete left;
		delete right;
		left = NULL;
		right = NULL;
	}

	// Adaugam date, transformand un nod nil intr-un nod obisnuit.
	void addData(T key, int priority) {
		this->nil = false;
		
		this->key.cuv = key.cuv;
		this->key.nr_apar = key.nr_apar;
		
		this->priority = priority;
		this->nr_nodes = 1;
		this->left = new Treap();
		this->right = new Treap();
	}

 	// Stergem un nod obisnuit, transformandu-l intr-unul nil.
	void delData() {
		this->nil = true;
		this->priority = -1;
		delete this->left;
		delete this->right;
		this->left = NULL;
		this->right = NULL;
		this->nr_nodes = 0;
	}

	bool isNil() {
		return this->nil;
	}

	bool find(T key) {
		if (this->isNil()) {
			return false;
		}

		if (key == this->key) {
			return true;
		}

		if (key < this->key) {
			return this->left->find(key);
		}
		else {
			return this->right->find(key);
		}
	}
	
	T findMin(Treap<T> *&nod) {
		if (nod->isNil()) {
			return -1;
		}
		else {
			if (nod->left->isNil()) {
				return nod->key;
			}
			else {
				return findMin(nod->left);
			}
		}
	}
	
	T findMax(Treap<T> *nod) {
		if (!nod->isNil()) {
			while (!nod->right->isNil()) {
				nod = nod->right;
			}
			return nod->key;
		}
		return -1;
	}

	void rotateRight(Treap<T> *&nod) {
		Treap<T> *aux;

		aux = nod->left;
		
		// Recalculeaza numarul de noduri din subarbori.
		nod->nr_nodes = 1 + nod->right->nr_nodes + aux->right->nr_nodes;
		aux->nr_nodes = 1 + aux->left->nr_nodes + nod->nr_nodes;
		
		nod->left = aux->right;
		aux->right = nod;
		nod = aux;
	}

	void rotateLeft(Treap<T> *&nod) {
		Treap<T> *aux;
		
		aux = nod->right;
		
		// Recalculeaza numarul de noduri din subarbori.
		nod->nr_nodes = 1 + nod->left->nr_nodes + aux->left->nr_nodes;
		aux->nr_nodes = 1 + aux->right->nr_nodes + nod->nr_nodes;
		
		nod->right = aux->left;
		aux->left = nod;
		nod = aux;
	}

	void insert(Treap<T> *&fatherPointer, T key, int priority) {
		if (this->isNil()) {
			this->addData(key, priority);
			return;
		}

		if ((key.nr_apar < this->key.nr_apar) || 
		   ((key.nr_apar == this->key.nr_apar) && (strcmp(key.cuv, this->key.cuv) > 0))) {
			this->left->insert(fatherPointer->left, key, priority);
			nr_nodes++;
		} else {
			this->right->insert(fatherPointer->right, key, priority);
			nr_nodes++;
		}
		
		// balance		
		if (this->left->priority > this->priority) {
			this->rotateRight(fatherPointer);
		} 
		else if (this->right->priority > this->priority) {
			this->rotateLeft(fatherPointer);
		}
	}

	void erase(Treap<T> *&fatherPointer, T key) {
		if (this->isNil()) {
			return ;
		}

		if ( (key.nr_apar < fatherPointer->key.nr_apar) || 
		     ((key.nr_apar == fatherPointer->key.nr_apar) && (strcmp(key.cuv, fatherPointer->key.cuv) > 0)) ) {
			
			erase(fatherPointer->left,key);
			fatherPointer->nr_nodes--;
		}
    	else {
			if ((key.nr_apar > fatherPointer->key.nr_apar) || 
			   ((key.nr_apar == fatherPointer->key.nr_apar) && (strcmp(key.cuv, fatherPointer->key.cuv) < 0))) {
			
				erase(fatherPointer->right,key);
				fatherPointer->nr_nodes--;
			} else {
				if (fatherPointer->left->isNil() && fatherPointer->right->isNil()) {
					fatherPointer->delData();
				} 
				else {
					if (fatherPointer->left->priority > fatherPointer->right->priority){
						rotateRight(fatherPointer);
						erase(fatherPointer,key);
					} 
					else {
						rotateLeft(fatherPointer);
						erase(fatherPointer,key);
					}
				}
			}
		}
	}

	void inOrder() {
		if (this->isNil()) {
			cout << endl;
			return ;
		}

		if(!this->left->isNil()) {
			this->left->inOrder();
		}
		
		// (cuv, nr_apar){nr_nodes}
		cout << "(" << this->key.cuv << ", " << this->key.nr_apar << "){" << this->nr_nodes << "} ";

		if(!this->right->isNil()) {
			this->right->inOrder();
		}
	}
	
	void preOrder2() {
		if (this->isNil()) {
			return ;
		}
		
		// key(nr_nodes)
		cout << this->key << "(" << this->nr_nodes << ") ";
		if(!this->left->isNil()) {
			this->left->preOrder2();
		}
		if(!this->right->isNil()) {
			this->right->preOrder2();
		}
	}
	
	// Structura arborescenta.
	void preOrder(int level = 0) {
		if (this->isNil()) {
			return ;
		}

		for (int i = 0; i < level; i++) {
			cout << ' ';
		}
		
		// |(cuv, nr_apar){nr_nodes}
		cout << "|(" << this->key.cuv << ", " << this->key.nr_apar << "){" << this->nr_nodes << "} " << endl;
		if(!this->left->isNil()) {
			this->left->preOrder(level + 4);
		}
		if(!this->right->isNil()) {
			this->right->preOrder(level + 4);
		}
	}
	
	// Ordine crescatoare
	T findAscendio(int k) {
		int r = this->left->nr_nodes;
		if (k == r+1) {
			return this->key;
		}
		if (k < r+1) {
			return this->left->findAscendio(k);
		}
		return this->right->findAscendio(k-r-1);
	}
	
	// Ordine descrescatoare
	T findDescendio(int k) {
		return findAscendio(nr_nodes - k + 1);
	}
};

#endif //__TREAP_H

