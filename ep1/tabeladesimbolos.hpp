#ifndef _TABELADESIMBOLOS_H
#define _TABELADESIMBOLOS_H

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <algorithm>

using namespace std; 

#define ESQUERDA 2
#define DIREITA 1
#define PENDENTE cout << "ATENÇÃO! Função ainda não criada.\n";


enum cor {RUBRO, NEGRO};


string removeSimbolos (string s)
{	
	for (unsigned int i = 0; i < s.size (); i++)
		// permite letras minúsculas e números;
		if ((s[i] >= 32 && s[i] <= 64)  
			|| (s[i] >= 91 && s[i] <= 92) || (s[i] >= 123 && s[i] <= 125)) {
			// permite - e ', desde que não no início da palavra
			if (s[i] != 39 && s[i] != 45) {
				s.erase (s.begin () + i);
				i--;
			}
			else if (i == 0 || s[i+1] == s[i]) {
				s.erase (s.begin () + i);
				i--;

			}
		}
	return s;
}

template <class Chave, class Item>
class No
{
	private:
		Chave chave;
		Item valor;

	public:
		Chave getChave ()
			{return chave;}
		Item getValor ()
			{return valor;}
		void setChave (Chave ch)
			{chave = ch;}
		void setValor (Item val)
			{valor = val;}
};

template <class Chave, class Item>
class NoLista: public No <Chave, Item>
{
	NoLista <Chave, Item> *prox;

	public:
		NoLista ();
		void setProx (NoLista <Chave, Item> *prx)
			{prox = prx;}
		NoLista <Chave, Item> *getProx ()
			{return prox;}
};

template <class Chave, class Item>
NoLista <Chave, Item>::NoLista (): prox (nullptr) {};

template <class Chave, class Item>
class NoArvoreBin: public No <Chave, Item>
{
	NoArvoreBin <Chave, Item> *esq;
	NoArvoreBin <Chave, Item> *dir;

	public:
		NoArvoreBin ();

		NoArvoreBin <Chave, Item> *getEsq()
			{return esq;}
		NoArvoreBin <Chave, Item> *getDir()
			{return dir;}
		void setEsq (NoArvoreBin <Chave, Item> *e)
			{esq = e;}
		void setDir (NoArvoreBin <Chave, Item> *d)
			{dir = d;}
};

template <class Chave, class Item>
NoArvoreBin<Chave, Item>::NoArvoreBin (): esq (nullptr), dir (nullptr) {};

template <class Chave, class Item>
class NoTreap: public No <Chave, Item>
{
	int prior;

	NoTreap <Chave, Item> *esq;
	NoTreap <Chave, Item> *dir;

	public:
		NoTreap ();

		int getPrior ()
			{return prior;}
		NoTreap <Chave, Item> *getEsq()
			{return esq;}
		NoTreap <Chave, Item> *getDir()
			{return dir;}
		void setEsq (NoTreap <Chave, Item> *e)
			{esq = e;}
		void setDir (NoTreap <Chave, Item> *d)
			{dir = d;}
};

template <class Chave, class Item>
NoTreap<Chave, Item>::NoTreap (): esq (nullptr), dir (nullptr) 
{
	prior = rand () % 100;
};

template <class Chave, class Item>
class No23
{
	No <Chave, Item> *no1, *no2;
	int nChaves;

	No23 <Chave, Item> *esq, *meio, *dir, *pai;

	public:
		No23 ();


		No23 <Chave, Item> *getEsq()
			{return esq;}
		No23 <Chave, Item> *getDir()
			{return dir;}
		No23 <Chave, Item> *getMeio()
			{return meio;}
		No23 <Chave, Item> *getPai()
			{return pai;}
		int getNChaves()
			{return nChaves;}
		No <Chave, Item>* getNo (int);
		void setNo (int, No <Chave, Item>*);
		void setEsq (No23 <Chave, Item> *e)
			{esq = e;}
		void setDir (No23 <Chave, Item> *d)
			{dir = d;}
		void setMeio (No23 <Chave, Item> *m)
			{meio = m;}
		void setPai (No23 <Chave, Item> *p)
			{pai = p;}
		void setNChaves (int n)
			{nChaves = n;}
};

template <class Chave, class Item>
No23 <Chave, Item>::No23 (): esq (nullptr), meio (nullptr), dir (nullptr), pai (nullptr) 
{
	nChaves = 0;
}

template <class Chave, class Item>
No <Chave, Item>* No23 <Chave, Item>::getNo (int num)
{
	if (num == 1)
		return no1;
	else
		return no2;
}

template <class Chave, class Item>
void No23 <Chave, Item>::setNo (int num, No <Chave, Item> *no)
{
	if (num == 1) 
		no1 = no;

	else 
		no2 = no;
}

template <class Chave, class Item>
class NoRN: public No <Chave, Item>
{
	bool cor;

	NoRN <Chave, Item> *esq, *dir, *pai;

	public:
		NoRN ();

		bool getCor ()
			{return cor;}
		NoRN <Chave, Item> *getEsq()
			{return esq;}
		NoRN <Chave, Item> *getDir()
			{return dir;}
		NoRN <Chave, Item> *getPai()
			{return pai;}
		NoRN <Chave, Item> *getTio(NoRN <Chave, Item>*);
		void setEsq (NoRN <Chave, Item> *e)
			{esq = e;}
		void setPai (NoRN <Chave, Item> *dp)
			{pai = dp;}
		void setDir (NoRN <Chave, Item> *d)
			{dir = d;}
		void setCor (bool c)
			{cor = c;}
		void trocaCor ()
			{cor = (cor ? RUBRO : NEGRO);}
		bool filhoRubro ()
			{return (esq && esq->cor == RUBRO) || (dir && dir->cor == RUBRO);}
};	

template <class Chave, class Item>
NoRN <Chave, Item>::NoRN (): esq (nullptr), dir (nullptr) 
{
 cor = RUBRO;
}

template <class Chave, class Item>
NoRN <Chave, Item>* NoRN <Chave, Item>::getTio (NoRN <Chave, Item>* no) 
{
	NoRN <Chave, Item> *p;
	p = no->pai;

	if (no == p->esq)
		return p->dir;
	else
		return p->esq;
} 

/************************* Vetor Desordenado *************************/

template <class Chave, class Item>
class vetorDes
{
	No <Chave, Item> *inicio;
	int nElementos, tamMax;

	void resize (); 

	public:
		vetorDes (string arquivo)
		{
			string token;
			fstream arqTexto;
			int cont = 0;

			inicio = new No <Chave, Item> [1];
			nElementos = 0;
			tamMax = 1;

			arqTexto.open (arquivo);
			while (arqTexto >> token) {
				cont++;
				transform (token.begin(), token.end(), token.begin(), ::tolower);
				token = removeSimbolos (token);
				if (!(token.empty ()))
					insere (token, 1);
			}
			arqTexto.close();
		}
		~vetorDes ();

		void insere (Chave, Item);
		Item devolve (Chave);
		void remove (Chave);
		int rank (Chave);
		Chave seleciona (int);
};

template <class Chave, class Item>
vetorDes <Chave, Item>::~vetorDes ()
{
	delete [] inicio;
}

template <class Chave, class Item>
void vetorDes <Chave,Item>::insere (Chave chave, Item valor)
{
	if (nElementos == tamMax)
		resize ();

	int i = 0;

	for (i = 0; i < nElementos; i++)
		if (inicio [i].getChave () == chave) {
			inicio [i].setValor (inicio [i].getValor () + valor);
			return;
		}

	inicio [nElementos].setChave (chave);
	inicio [nElementos].setValor (valor);
	nElementos++;
}

template <class Chave, class Item>
Item vetorDes <Chave, Item>::devolve (Chave chave)
{
	for (int i  = 0; i < nElementos; i++){
		if (inicio [i].getChave () == chave){
			return inicio [i].getValor (); 
		}
	}

	cout << "Chave não encontrada. \n";
	return 0;
}

template <class Chave, class Item>
void vetorDes <Chave, Item>::remove (Chave chave)
{
	for (int i  = 0; i < nElementos; i++)
		if (inicio [i].getChave () == chave){
			for (int j = i; j < nElementos - 1; j++)
				inicio [j] = inicio [j+1]; 
		return;
		}
	cout << "Chave não encontrada.\n";
}

template <class Chave, class Item>
int vetorDes <Chave, Item>::rank (Chave chave)
{
	int cont = 0;
	
	for (int i = 0; i < nElementos; i++){
		if (inicio [i].getChave () < chave)
			cont++; 
	} 

	return cont; 
}

template <class Chave, class Item>
Chave vetorDes <Chave, Item>::seleciona (int k)
{
	for (int i = 0; i < nElementos; i++) {
		if (rank (inicio [i].getChave ()) == k)
			return inicio [i].getChave ();
	}
	cout << "Não existem " << k + 1 << " chaves nessa tabela de símbolos\n";
	return " ";
}

// Funções auxiliares

template <class Chave, class Item>
void vetorDes<Chave, Item>::resize () 
{
    No <Chave, Item> *novo = new No <Chave, Item> [tamMax * 2];

    memcpy (novo, inicio, tamMax * sizeof (No <Chave, Item>) );

    tamMax = tamMax * 2;
    inicio = novo;
}

/************************* Vetor Ordenado *************************/

template <class Chave, class Item>
class vetorOrd
{
	No <Chave, Item> *inicio;
	int nElementos, tamMax;

	void resize ();
	
	public:
		vetorOrd (string arquivo)
		{
			string token;
			fstream arqTexto;

			inicio = new No <Chave, Item> [1];
			nElementos = 0;
			tamMax = 1;
			
			arqTexto.open (arquivo);
			while (arqTexto >> token) {
				transform (token.begin(), token.end(), token.begin(), ::tolower);
				token = removeSimbolos (token);
				if (!(token.empty ()))
					insere (token, 1);
			}
			arqTexto.close();
		}
		~vetorOrd ();

		void insere (Chave, Item);
		Item devolve (Chave);
		void remove (Chave);
		int rank (Chave);
		Chave seleciona (int);
};

template <class Chave, class Item>
vetorOrd <Chave, Item>::~vetorOrd ()
{
	delete [] inicio;
}

template <class Chave, class Item>
void vetorOrd<Chave, Item>::insere (Chave chave, Item valor)
{
	int r = rank (chave);

	if (nElementos == tamMax)
		resize ();

	if (inicio [r].getChave () == chave){
		inicio [r].setValor (inicio[r].getValor () + valor);
		return;
	}

	for (int i = nElementos; i > r; i--)
		inicio [i] = inicio [i-1];
	
	inicio [r].setChave (chave);
	inicio [r].setValor (valor);
	nElementos++;
}

template <class Chave, class Item>
Item vetorOrd <Chave, Item>::devolve (Chave chave)
{
	int h = rank (chave);

	if (inicio [h].getChave () != chave){
		cout << "Chave não encontrada. \n";
		return 0;
	} 

	return inicio [h].getValor ();
}

template <class Chave, class Item>
void vetorOrd <Chave, Item>::remove (Chave chave)
{
	int h = rank (chave);

	if (inicio [h].getChave () != chave){
		cout << "Chave não encontrada.\n";
		return;
	}
	for (int i = h; i < nElementos - 1; i++) {
		inicio [i] = inicio [i+1];
	}
	nElementos--;	
}

template <class Chave, class Item>
int vetorOrd <Chave, Item>::rank (Chave chave)
{
	int ini = 0, fim = nElementos -1;

	while (ini <= fim){		
		int meio = (ini + fim) / 2;
		
		if (inicio [meio].getChave () == chave)
			return (meio);
		
		else if (inicio [meio].getChave () > chave)
			fim = meio - 1;
		else
			ini = meio + 1;
	}
	return ini;
}

template <class Chave, class Item>
Chave vetorOrd <Chave, Item>::seleciona (int k)
{
	if (!inicio[k].getChave ().empty () )
		return inicio[k].getChave ();
	else
		cout << "Não existem " << k + 1 << " chaves nessa tabela de símbolos\n";
	return "";
}

// Funções auxiliares

template <class Chave, class Item>
void vetorOrd<Chave, Item>::resize () 
{
    No <Chave, Item> *novo = new No <Chave, Item> [tamMax * 2];
    memcpy (novo, inicio, tamMax * sizeof (No <Chave, Item>) );

    inicio = novo;
    tamMax = tamMax * 2;
}

/************************* Lista Ligada Desordenada *************************/

template <class Chave, class Item>
class listaDes
{
	NoLista <Chave, Item> *inicio;

	public:
		listaDes (string arquivo)
		{
			string token;
			fstream arqTexto;

			inicio = NULL;
			arqTexto.open (arquivo);
			
			while (arqTexto >> token) {
				transform (token.begin(), token.end(), token.begin(), ::tolower);
				token = removeSimbolos (token);
				if (!(token.empty ()))
					insere (token, 1);
			}
			arqTexto.close();
		}
		~listaDes ();

		void insere (Chave, Item);
		Item devolve (Chave);
		void remove (Chave);
		int rank (Chave);
		Chave seleciona (int);
};

template <class Chave, class Item>
listaDes <Chave, Item>::~listaDes ()
{
	delete inicio;
}

template <class Chave, class Item>
void listaDes <Chave,Item>::insere (Chave chave, Item valor)
{
	NoLista <Chave, Item> *p = inicio;
	while (p != NULL)
	{
		if (p->getChave () == chave){
			p->setValor (p->getValor () + valor);
			return;
		}
		p = p->getProx ();
	}

	NoLista <Chave, Item> *novo = new NoLista <Chave, Item>;
	novo->setChave (chave);
	novo->setValor (valor);
	novo->setProx (inicio);
	inicio = novo;
}

template <class Chave, class Item>
Item listaDes <Chave,Item>::devolve (Chave chave)
{
	NoLista <Chave, Item> *p = inicio;

	while (p != NULL) {
		if (p->getChave () == chave)
			return p->getValor ();
		p = p->getProx ();
	}
	cout << "Chave não encontrada. \n";
	return 0;
}

template <class Chave, class Item>
void listaDes <Chave,Item>::remove (Chave chave)
{
	NoLista <Chave, Item> *p, *aux;
	p = inicio;
	aux = NULL;

	while (p) {
		if (p->getChave () == chave) {
			if (aux && p->getProx())
				aux->setProx (p->getProx ());
			else if (aux == NULL)
				inicio = p->getProx ();
			delete p;
			return;
		}
		aux = p;
		p = p->getProx ();
	}
	cout << "Chave não encontrada.\n";
}

template <class Chave, class Item>
int listaDes <Chave, Item>::rank (Chave chave)
{
	NoLista <Chave, Item> *p = inicio;
	int cont = 0;

	while (p) {
		if (p->getChave () < chave)
			cont++;
		p = p->getProx ();
	}
	return cont; 
}

template <class Chave, class Item>
Chave listaDes <Chave, Item>::seleciona (int k)
{
	NoLista <Chave, Item> *p = inicio;

	while (p) {
		if (rank (p->getChave ()) == k)
			return p->getChave ();
		p = p->getProx ();
	}
	cout << "Não existem " << k + 1 << " chaves nessa tabela de símbolos\n";
	return "";
}

/************************* Lista Ligada Ordenada *************************/

template <class Chave, class Item>
class listaOrd
{
	NoLista <Chave, Item> *inicio;

	public:
		listaOrd (string arquivo)
		{
			string token;
			fstream arqTexto;

			inicio = NULL;
			arqTexto.open (arquivo);
			
			while (arqTexto >> token) {
				transform (token.begin(), token.end(), token.begin(), ::tolower);
				token = removeSimbolos (token);
				if (!(token.empty ()))
					insere (token, 1);
			}

			 arqTexto.close ();
		}
		~listaOrd ();

		void insere (Chave, Item);
		Item devolve (Chave);
		void remove (Chave);
		int rank (Chave);
		Chave seleciona (int);
};

template <class Chave, class Item>
listaOrd <Chave, Item>::~listaOrd ()
{
	delete inicio;
}

template <class Chave, class Item>
void listaOrd <Chave,Item>::insere (Chave chave, Item valor)
{
	NoLista <Chave, Item> *p;
	p = inicio;
	int h = rank (chave);

	for (int i = 1; i < h; i++)
		p = p->getProx ();

	if ((h > 0 && p->getProx ()) && (p->getProx ()->getChave () == chave)){
		p->getProx ()->setValor (p->getProx ()->getValor () + valor);
		return;
	}
	else if (h == 0 && p && p->getChave () == chave){
		p->setValor (p->getValor () + valor);
		return;
	}

	else {
		NoLista <Chave, Item> *novo = new NoLista <Chave, Item>;
		novo->setChave (chave);
		novo->setValor (valor);
		
		if (p) {
			if (p->getChave () > chave) {
				novo->setProx (p);
				inicio = novo;
				return;
			} 
			else {
				novo->setProx (p->getProx ());
				p->setProx (novo);
				return;
			}
		} 
		else {
			novo->setProx (NULL);
			inicio = novo;
			return;
		}
	}

}

template <class Chave, class Item>
Item listaOrd <Chave,Item>::devolve (Chave chave)
{
	NoLista <Chave, Item> *p = inicio;
	int h = rank (chave);

	for (int i = 0; i < h; i++) 
		p = p->getProx ();
	if (p->getChave () != chave) {
		cout << "Chave não encontrada. \n";
		return 0;
	}
	return p->getValor ();
}

template <class Chave, class Item>
void listaOrd <Chave,Item>::remove (Chave chave)
{
	NoLista <Chave, Item> *p, *aux;
	p = inicio;
	aux = NULL;

	while (p) {
		if (p->getChave () == chave) {
			if (aux && p->getProx () )
				aux->setProx (p->getProx ());
			else if (aux == NULL)
				inicio = p->getProx ();
			delete p;
			return;
		}
		if (p->getProx () == NULL || p->getChave () > chave) {
			cout << "Chave não encontrada.\n";
			return;
		}
		else {
			aux = p;
			p = p->getProx ();
		}
	}
}

template <class Chave, class Item>
int listaOrd <Chave, Item>::rank (Chave chave)
{
	NoLista <Chave, Item> *p = inicio;
	int cont = 0;

	while (p){
		if (p->getChave () < chave)
			cont++;
		p = p->getProx ();
	}

	return cont;
}

template <class Chave, class Item>
Chave listaOrd <Chave, Item>::seleciona (int k)
{
	NoLista <Chave, Item> *p = inicio;

	for (int i = 0; i < k; i++){
		if (!(p->getProx ())) {
			cout << "Não existem " << k + 1 << " chave nessa TS. \n"; 
			return "";
		}
		p = p->getProx ();
	}
	return p->getChave ();
}

/************************* Árvore Binária *************************/

template <class Chave, class Item>
class arvoreBin
{
	NoArvoreBin <Chave, Item> *raiz;

	NoArvoreBin <Chave, Item>* insereR (Chave, Item, NoArvoreBin <Chave, Item>*);
	NoArvoreBin <Chave, Item>* removeR (NoArvoreBin <Chave, Item>*, Chave);
	int rankR (NoArvoreBin <Chave, Item>*, Chave);
	NoArvoreBin <Chave, Item>* max (NoArvoreBin<Chave, Item>*);
	void printAB (string, NoArvoreBin <Chave, Item>*, bool);

	public:
		arvoreBin (string arquivo)
		{
			string token;
			fstream arqTexto;

			raiz = NULL;
			arqTexto.open (arquivo);
			
			while (arqTexto >> token) {
				transform (token.begin(), token.end(), token.begin(), ::tolower);
				token = removeSimbolos (token);
				if (!(token.empty ()))
					insere (token, 1);
			}
			arqTexto.close ();
		}
		~arvoreBin ();

		void insere (Chave, Item);
		Item devolve (Chave);
		void remove (Chave);
		int rank (Chave);
		Chave seleciona (int);
};

template <class Chave, class Item>
arvoreBin <Chave, Item>::~arvoreBin ()
{
	delete raiz;
}

template <class Chave, class Item>
void arvoreBin <Chave, Item>::insere (Chave chave, Item valor)
{
	raiz = insereR (chave, valor, raiz);
}

template <class Chave, class Item>
Item arvoreBin <Chave, Item>::devolve (Chave chave)
{
	NoArvoreBin <Chave, Item> *p;

	p = raiz;

	while (p) {
		if (p->getChave () == chave)
			return p->getValor ();
		else if (p->getEsq () || p->getDir ()) {
			if (p->getChave () > chave)
					p = p->getEsq ();
			else if (p->getChave () < chave)
					p = p->getDir ();
		}
	}

	cout << "Chave não encontrada.\n";
	return 0;
}

template <class Chave, class Item>
void arvoreBin <Chave, Item>::remove (Chave chave)
{
	raiz = removeR (raiz, chave);
}


template <class Chave, class Item>
int arvoreBin <Chave, Item>::rank (Chave chave)
{
	return rankR (raiz, chave);
}

template <class Chave, class Item>
Chave arvoreBin <Chave, Item>::seleciona (int k)
{
	int rankNo = 0;
	NoArvoreBin <Chave, Item> *p;
	p = raiz;

	while (p) {
		if ((rankNo = rank (p->getChave ())) == k)
			return p->getChave ();
		else if (rankNo < k) 
			p = p->getDir ();
		else
			p = p->getEsq ();
	}

	cout << "Não existem " << k + 1 << " chaves nessa tabela de símbolos.\n";
	return "";
}

// Funções auxiliares

template <class Chave, class Item>
int arvoreBin <Chave, Item>::rankR (NoArvoreBin <Chave, Item> *no, Chave chave)
{
	int cont = 0;

	if (no) {
		if (no-> getChave () < chave) {
			cont++;
			cont += rankR (no->getEsq (), chave);
			cont += rankR (no->getDir (), chave);
		}
		else if (no->getChave () >= chave)
			cont += rankR (no->getEsq (), chave);
	}
	return cont; 
}

template <class Chave, class Item>
void arvoreBin <Chave, Item>::printAB (string prefix, NoArvoreBin <Chave, Item> *no, bool esq)
{
    if (no != nullptr)
    {
        cout << prefix;

        cout << (esq ? "├──" : "└──" );

        cout << no->getChave () << ": " << no->getValor () << "\n";

        printAB (prefix + (esq ? "│   " : "    "), no->getEsq (), true);
        printAB (prefix + (esq ? "│   " : "    "), no->getDir (), false);
    }
}

template <class Chave, class Item>
NoArvoreBin <Chave, Item>* arvoreBin <Chave, Item>::insereR (Chave chave, Item valor, NoArvoreBin <Chave, Item> *no)
{
	if (no == NULL) {
		NoArvoreBin <Chave, Item> *novo = new NoArvoreBin <Chave, Item>;
		novo->setChave (chave);
		novo->setValor (valor);
		novo->setEsq (NULL);
		novo->setDir (NULL);
		no = novo;
	}
	else if (no->getChave () > chave)
		no->setEsq (insereR (chave, valor, no->getEsq ()));
	else if (no->getChave () < chave)
		no->setDir (insereR (chave, valor, no->getDir ()));
	else 
		no->setValor (no->getValor () + valor);

	return no;
}

template <class Chave, class Item>
NoArvoreBin <Chave, Item>* arvoreBin <Chave, Item>::max (NoArvoreBin <Chave, Item> *raiz)
{
	if (raiz == nullptr || raiz->getDir () == nullptr)
		return raiz;
	return max (raiz->getDir ());
}

template <class Chave, class Item>
NoArvoreBin <Chave, Item>* arvoreBin <Chave, Item>::removeR (NoArvoreBin <Chave, Item> * raiz, Chave chave)
{
	NoArvoreBin <Chave, Item> * aux;
	if (raiz == NULL) 
		return raiz;
	if (raiz->getChave () > chave)
		raiz->setEsq (removeR (raiz->getEsq (), chave));
	else if (raiz->getChave () < chave)
		raiz->setDir (removeR (raiz->getDir (), chave));
	else { 
	// achei o cara a ser removido 
		if (raiz->getDir () == NULL) {
			aux = raiz->getEsq ();
			delete raiz;
			return aux;
		}
		else if (raiz->getEsq () == NULL) {
			aux = raiz->getDir ();
			delete raiz;
			return aux;
		}
		else {
		// o nó tem os dois filhos
			aux = max (raiz->getEsq ());
			raiz->setChave (aux->getChave ());
			raiz->setValor (aux->getValor ());
			raiz->setEsq (removeR (raiz->getEsq (), aux->getChave ()));
		}
	}
	return raiz;
}

/************************* Treap *************************/

template <class Chave, class Item>
class treap
{
	NoTreap <Chave, Item> *raiz;

	NoTreap <Chave, Item>* rotEsq (NoTreap <Chave, Item> *raiz);
	NoTreap <Chave, Item>* rotDir (NoTreap <Chave, Item> *raiz);
	NoTreap <Chave, Item>* removeR (NoTreap <Chave, Item>*, Chave);
	NoTreap <Chave, Item>* insereR (NoTreap <Chave, Item>*, Chave, Item);
	int rankR (NoTreap <Chave, Item>*, Chave);
	void printTR (string, NoTreap <Chave, Item>*, bool);

	public:
		treap (string arquivo)
		{
			string token;
			fstream arqTexto;

			raiz = NULL;
			arqTexto.open (arquivo);

			while (arqTexto >> token) {
				transform (token.begin(), token.end(), token.begin(), ::tolower);
				token = removeSimbolos (token);
				if (!(token.empty ()))
					insere (token, 1);
			}
			arqTexto.close (); 
		}
		~treap ();

		void insere (Chave, Item);
		Item devolve (Chave);
		void remove (Chave);
		int rank (Chave);
		Chave seleciona (int);
};

template <class Chave, class Item>
treap <Chave, Item>::~treap ()
{
	delete raiz;
}

template <class Chave, class Item>
void treap <Chave, Item>::insere (Chave chave, Item valor)
{
	raiz = insereR (raiz, chave, valor);
} 

template <class Chave, class Item>
Item treap <Chave,Item>::devolve (Chave chave)
{
	NoTreap <Chave, Item> *p;

	p = raiz;

	while (p) {
		if (p->getChave () == chave)
			return p->getValor ();
		else if (p->getEsq () || p->getDir ()) {
			if (p->getChave () > chave) 
					p = p->getEsq ();
			else if (p->getChave () < chave) 
					p = p->getDir ();
		}
	}
	
	return 0;
}

template <class Chave, class Item>
void treap <Chave,Item>::remove (Chave chave)
{
	raiz = removeR (raiz, chave);
}

template <class Chave, class Item>
int treap <Chave, Item>::rank (Chave chave)
{
	return rankR (raiz, chave);
}

template <class Chave, class Item>
Chave treap <Chave, Item>::seleciona (int k)
{
	int rankNo = 0;
	NoTreap <Chave, Item> *p;
	p = raiz;

	while (p) {
		rankNo = rank (p->getChave ());
		if (rankNo == k)
			return p->getChave ();
		else if (rankNo < k) 
			p = p->getDir ();
		else
			p = p->getEsq ();
	}

	cout << "Chave não encontrada. \n";
	return "";
}

// Funções auxiliares

template <class Chave, class Item>
int treap <Chave, Item>::rankR (NoTreap <Chave, Item> *no, Chave chave)
{
	int cont = 0;

	if (no) {
		if (no-> getChave () < chave) {
			cont++;
			cont += rankR (no->getEsq (), chave);
			cont += rankR (no->getDir (), chave);
		}
		else if (no->getChave () >= chave)
			cont += rankR (no->getEsq (), chave);
	}
	return cont; 
}

template <class Chave, class Item>
NoTreap <Chave, Item>* treap <Chave, Item>::rotEsq (NoTreap <Chave, Item> *no)
{
	NoTreap <Chave, Item> *d, *de;
	d = no->getDir ();
	de = no->getDir ()->getEsq ();

	d->setEsq (no);
	no->setDir (de);

	return d;
}

template <class Chave, class Item>
NoTreap <Chave, Item>* treap <Chave, Item>::rotDir (NoTreap <Chave, Item> *no)
{
	NoTreap <Chave, Item> *e, *ed;
	e = no->getEsq ();
	ed = no->getEsq ()->getDir ();
	e->setDir (no);
	no->setEsq (ed);

	return e;
}

template <class Chave, class Item>
NoTreap <Chave, Item>* treap <Chave,Item>::removeR (NoTreap <Chave, Item> *no, Chave chave)
{
	if (no == NULL){
		cout << "Chave não encontrada.\n";
		return NULL;
	}

	if (chave < no->getChave ())
		no->setEsq (removeR (no->getEsq (), chave));
	else if (chave > no->getChave ())
		no->setDir (removeR (no->getDir (), chave));
	// encontrou a chave
	else {
		// é folha
		if (no->getEsq () == NULL && no->getDir () == NULL) {
			delete no;
			no = NULL;

			return no;
		}
		// tem dois filhos
		else if (no->getEsq () && no->getDir ()) {
			if (no->getEsq ()->getPrior () < no->getDir ()->getPrior ()) {
				no = rotEsq (no);
				no->setEsq (removeR (no->getEsq (), chave));
			}
			else {
				no = rotDir (no);
				no->setDir (removeR (no->getDir (), chave));
			}
		}
		// tem filho esquerdo
		else if (no->getEsq ()) {
			delete no;
			no = no->getEsq ();
		}
		// tem filho direito
		else {
			delete no;
			no = no->getDir ();

		} 
	}
	return no;
}

template <class Chave, class Item>
NoTreap <Chave, Item>* treap <Chave, Item>::insereR (NoTreap <Chave, Item> *no, Chave chave, Item valor)
{
	if (no == NULL) {
		NoTreap <Chave, Item> *novo = new NoTreap <Chave, Item>;
		novo->setChave (chave);
		novo->setValor (valor);
		no = novo;
	}
	else if (no->getChave () > chave) {
		no->setEsq (insereR (no->getEsq (), chave, valor));
		if (no->getEsq () && no->getEsq ()-> getPrior () > no->getPrior ())
			no = rotDir (no);
	}
	else if (no->getChave () < chave) {
		no->setDir (insereR (no->getDir (), chave, valor));
		if (no->getDir () && no->getDir ()->getPrior () > no->getPrior ())
			no = rotEsq (no);
	}
	else 
		no->setValor (no->getValor () + valor);

	return no;
}

template <class Chave, class Item>
void treap <Chave, Item>::printTR (string prefix, NoTreap <Chave, Item> *no, bool esq)
{
    if (no)
    {
        cout << prefix;

        cout << (esq ? "├──" : "└──" );

        cout << no->getChave () << ": " << no->getValor ();
        cout << " (" << no->getPrior () << ")\n";

        printTR (prefix + (esq ? "│   " : "    "), no->getEsq (), true);
        printTR (prefix + (esq ? "│   " : "    "), no->getDir (), false);
    }
}

/************************* Árvore 2-3 *************************/

template <class Chave, class Item>
struct out
{
	No <Chave, Item> *interm;
	No23 <Chave, Item> *orfao;

	out ()
	{
		interm = orfao = NULL;
	}
	out (No <Chave, Item> *i, No23 <Chave, Item> *o) 
	{
		interm = i;
		orfao = o;
	}
};

template <class Chave, class Item>
class arvore23
{
	No23 <Chave, Item> *raiz;

	No <Chave, Item>* busca (No23 <Chave, Item>*, Chave);
	int rankR (No23 <Chave, Item> *no, Chave chave);
	out <Chave, Item>* insereR (No23 <Chave, Item>*, No <Chave, Item>*);
	No23 <Chave, Item>* removeR (No23 <Chave, Item>*, Chave chave);
	out <Chave, Item>* split (No23 <Chave, Item>*, No <Chave, Item>*, No23 <Chave, Item>*);
	No23 <Chave, Item>* merge (No23 <Chave, Item>*, No23 <Chave, Item>*);
	void rotEsq (No23 <Chave, Item>*, No <Chave, Item>*, No23 <Chave, Item>*);
	void rotDir (No23 <Chave, Item>*, No <Chave, Item>*, No23 <Chave, Item>*);
	int ifRotaciona (No23 <Chave, Item>*);

	void printA23 (string, No23 <Chave, Item>*, bool);

	public:
		arvore23 (string arquivo)
		{
			string token;
			fstream arqTexto;

			raiz = NULL;
			arqTexto.open (arquivo);

			while (arqTexto >> token) {
				transform (token.begin(), token.end(), token.begin(), ::tolower);
				token = removeSimbolos (token);
				if (!(token.empty ()))
					insere (token, 1);
			}

			arqTexto.close ();
		}
		~arvore23 ();

		void insere (Chave, Item);
		Item devolve (Chave);
		void remove (Chave);
		int rank (Chave);
		Chave seleciona (int);
};

template <class Chave, class Item>
arvore23 <Chave, Item>::~arvore23 ()
{
	delete raiz;
}

template <class Chave, class Item>
void arvore23 <Chave, Item>::insere (Chave chave, Item valor)
{
	No <Chave, Item> *no = busca (raiz, chave);

	if (no == NULL) {
		No <Chave, Item> *novo = new No <Chave, Item>;
		novo->setChave (chave);
		novo->setValor (valor);
		out <Chave, Item> *OUT = insereR (raiz, novo);
	
		if (OUT) {
			No23 <Chave, Item> *celula = new No23 <Chave, Item>;

			celula->setNo (1, OUT->interm);
			celula->setNChaves (1);

			celula->setEsq (raiz);
			raiz->setPai (celula);

			celula->setMeio (OUT->orfao);
			OUT->orfao ->setPai (celula);

			celula->setDir (NULL);
			raiz = celula;
		}
	}

	else 
		no->setValor (no->getValor () + valor);
}

template <class Chave, class Item>
Item arvore23 <Chave,Item>::devolve (Chave chave)
{
	No <Chave, Item> *end = busca (raiz, chave);

	if (end)
		return end->getValor ();

	cout << "Chave não encontrada.\n";
	return 0;

}

template <class Chave, class Item>
void arvore23 <Chave,Item>::remove (Chave chave)
{
	No23 <Chave, Item> *aux;

	aux = removeR (raiz, chave);
	if (aux)
		cout << "erro, nó não alocado.\n";
}

template <class Chave, class Item>
int arvore23 <Chave, Item>::rank (Chave chave)
{
	return rankR (raiz, chave);
}

template <class Chave, class Item>
Chave arvore23 <Chave, Item>::seleciona (int k)
{
	int rankNo1, rankNo2;
	rankNo1 = rankNo2 = 0;
	No23 <Chave, Item> *p;
	p = raiz;

	while (p) {
		if (p->getNChaves () == 1) {
			if ((rankNo1 = rank (p->getNo (1)->getChave ())) == k)
				return p->getNo (1)->getChave ();
			else if (rankNo1 < k) 
				p = p->getMeio ();
			else
				p = p->getEsq ();
		}
		else {
			if ((rankNo1 = rank (p->getNo (1)->getChave ())) == k)
				return p->getNo (1)->getChave ();
			else if (rankNo1 < k) {
				if ((rankNo2 = rank (p->getNo (2)->getChave ())) == k)
					return p->getNo (2)->getChave ();
				else if (rankNo2 < k )
					p = p->getDir ();
				else
					p = p->getMeio ();
			}
			else
				p = p->getEsq ();
		}
	}
	cout << "Chave não encontrada. \n";
	return "";
}

// Funções auxiliares
template <class Chave, class Item>
int arvore23 <Chave, Item>::ifRotaciona (No23 <Chave, Item> *no)
{
	No23 <Chave, Item> *pai = no->getPai ();

	if (pai) {
		// pai de nó único
		if (pai->getNChaves () == 1) {
			// overflow em "no"
			if (no->getNChaves () != 0) {
				if (!((pai->getEsq ()->getNChaves () == 2) && (pai->getMeio ()->getNChaves () == 2))) {
					if (pai->getEsq () == no)
						return DIREITA;
					else 
						return ESQUERDA;
				}
			}
			// underflow em "no"
			else {
				if ((pai->getEsq () == no) && (pai->getMeio ()->getNChaves () == 2))
					return ESQUERDA;
				else if ((pai->getMeio () == no) && (pai->getEsq ()->getNChaves () == 2))
					return DIREITA;
			}
		}
		// pai de nó duplo
		else {
			// overflow em "no"
			if (no->getNChaves () != 0) {
				if ((pai->getEsq () == no) && (pai->getMeio ()->getNChaves () == 1))
					return DIREITA;
				else if (pai->getMeio () == no) {
					if (pai->getEsq ()->getNChaves () == 1)
						return ESQUERDA;
					else if (pai->getDir ()->getNChaves () == 1)
						return DIREITA;
				}
				else 
					if (pai->getMeio ()->getNChaves () == 1)
						return ESQUERDA;
			}
			// underflow em "no"
			else {
				if ((pai->getEsq () == no) && (pai->getMeio ()->getNChaves () == 2))
					return ESQUERDA;
				else if (pai->getMeio () == no) {
					if (pai->getEsq ()->getNChaves () == 2)
						return DIREITA;
					else if (pai->getDir ()->getNChaves () == 2)
						return ESQUERDA;
				}
				else 
					if (pai->getMeio ()->getNChaves () == 2)
						return DIREITA;
			}
		}
	}

	return 0;
}

template <class Chave, class Item>
void arvore23 <Chave, Item>::rotDir (No23 <Chave, Item> *no, No <Chave, Item> *novo, No23 <Chave, Item> *orfao)
{
	No23 <Chave, Item> *pai = no->getPai ();
	No23 <Chave, Item> *dirPai, *esqPai, *meioPai;
	dirPai = pai->getDir ();
	esqPai = pai->getEsq ();
	meioPai = pai->getMeio ();

	// CASO 1: overflow em "no"
	if (no->getNChaves () != 0) {
    	if (pai->getNChaves () == 2 && meioPai == no) {
			No23 <Chave, Item> *auxMaior = NULL;
			
			// atualiza valores
    		dirPai->setNo (2, dirPai->getNo (1));    
    		dirPai->setNo (1, pai->getNo (2));
    		dirPai->setNChaves (2);

    		// novo < 1º "no" < 2º "no"
    		if (no->getNo (1)->getChave () > novo->getChave ()) {
    			pai->setNo (2, no->getNo (2));
    			no->setNo (2, no->getNo (1));
    			no->setNo (1, novo);

    			// ponteiros: esq < orfao < meio < dir
    			if (orfao) {
    				auxMaior = no->getDir ();
    				no->setDir (no->getMeio ());
    				no->setMeio (orfao);
    				orfao->setPai (no);
    			}
    		}
    		// 1º "no" < "novo" < 2º "no"
    		else if (no->getNo (2)->getChave () > novo->getChave ()) {
    			pai->setNo (2, no->getNo (2));
    			no->setNo (2, novo);

    			// ponteiros: esq < meio < orfao < dir
    			if (orfao) {
    				auxMaior = no->getDir ();
    				no->setDir (orfao);
    				orfao->setPai (no);
    			}
    		}
    		// 1º "no" < 2º "no < novo"
    		else {
    			pai->setNo (2, novo);
				
				// ponteiros: esq < meio < dir < orfao    			
	    		if (orfao) 
    				auxMaior = orfao;
	    	}

	    	if (orfao) { 
					dirPai->setDir (dirPai->getMeio ());
					dirPai->setMeio (dirPai->getEsq ());
					dirPai->setEsq (auxMaior);
	    			auxMaior->setPai (dirPai);
    		}
		}
		else {
			No23 <Chave, Item> *auxMaior = NULL;
			// atualiza valoress
			meioPai->setNo (2, meioPai->getNo (1));
			meioPai->setNo (1, pai->getNo (1));
			meioPai->setNChaves (2);
			
    		// novo < 1º "no" < 2º "no"
			if (no->getNo (1)->getChave () > novo->getChave ()) {
				pai->setNo (1, no->getNo (2));
				no->setNo (2, no->getNo (1));
				no->setNo (1, novo);

    			// ponteiros: esq < orfao < meio < dir
				if (orfao) {
					auxMaior = no->getDir ();
					no->setDir (no->getMeio ());
					no->setMeio (orfao);
					orfao->setPai (no);
				}
			}
    		// 1º "no" < "novo" < 2º "no"
			else if (no->getNo (2)->getChave () >novo->getChave ()) {
				pai->setNo (1, no->getNo (2));
				no->setNo (2, novo);

    			// ponteiros: esq < meio < orfao < dir
				if (orfao) {
					auxMaior = no->getDir ();
					no->setDir (orfao);
					orfao->setPai (no);
				}

			}
    		// 1º "no" < 2º "no" < novo
			else {
				pai->setNo (1, novo);
				
				// ponteiros: esq < meio < dir < orfao    			
				if (orfao)
					auxMaior = orfao;
			}
		
			if (orfao) {
				meioPai->setDir (meioPai->getMeio ());
				meioPai->setMeio (meioPai->getEsq ());
				meioPai->setEsq (auxMaior);
				auxMaior->setPai (meioPai);
			}
		}
	}
	// CASO 2: underflow em "no"
    else {
    	if (pai->getNChaves () == 2 && dirPai == no) {
			
			// atualiza valores
			no->setNo (1, pai->getNo (2));         
			no->setNChaves (1);

			pai->setNo (2, meioPai-> getNo (2));
			meioPai->setNChaves (1);
			meioPai->setNo (2, NULL);

			//atualiza ponteiros
			dirPai->setEsq (meioPai->getDir ());
			if (meioPai->getDir ())
				meioPai->getDir ()->setPai (dirPai);
		}

		else {
			// atualiza valores
			no->setNo (1, pai->getNo (1));             
			no->setNChaves (1);                    

			pai->setNo (1, esqPai->getNo (2));
			esqPai->setNChaves (1);
			esqPai->setNo (2, NULL);

			// atualiza ponteiros
			meioPai->setEsq (esqPai->getDir ());
			if (esqPai->getDir ())
				esqPai->getDir ()->setPai (meioPai);
		}
		no->setNo (2, NULL);
	} 
}

template <class Chave, class Item>
void arvore23 <Chave, Item>::rotEsq (No23 <Chave, Item> *no, No <Chave, Item> *novo, No23 <Chave, Item> *orfao)
{
	No23 <Chave, Item> *pai = no->getPai ();
	No23 <Chave, Item> *dirPai, *esqPai, *meioPai;
	dirPai = pai->getDir ();
	esqPai = pai->getEsq ();
	meioPai = pai->getMeio ();

	// CASO 1: overflow em "no"
	if (no->getNChaves () != 0) {
		if (pai->getNChaves () == 2 && dirPai == no) {
			// atualiza valores
			meioPai->setNo (2, pai->getNo (2));
			meioPai->setNChaves (2);

			meioPai->setDir (dirPai->getEsq ());
			if (no->getEsq ())
				dirPai->getEsq ()->setPai (meioPai);
			
			// novo < 1º "no" < 2º "no"
			if (no->getNo (1)->getChave () > novo->getChave ()) {
				pai->setNo (2, novo);

				//ponteiros: esq < orfao < meio < dir
				if (orfao) {
					dirPai->setEsq (orfao);
					orfao->setPai (dirPai);
				}
			}
			// 1º "no" < novo < 2º "no"
			else if (no->getNo (2)->getChave () > novo->getChave ()) {
				pai->setNo (2, no->getNo (1));
				no->setNo (1, novo);

				//ponteiros: esq < meio < orfao < dir
				if (orfao) {
					dirPai->setEsq (dirPai->getMeio ());
					dirPai->setMeio (orfao);
					orfao->setPai (dirPai);
				}
			}
			// 1º "no" < 2º "no" < novo
			else {
				pai->setNo (2, no->getNo (1));
				no->setNo (1, no->getNo (2));
				no->setNo (2, novo);

				//ponteiros: esq < meio < dir < orfao
				if (orfao) {
					dirPai->setEsq (dirPai->getMeio ());
					dirPai->setMeio (dirPai->getDir ());
					dirPai->setDir (orfao);
					orfao->setPai (dirPai);
				}
			} 
		}
		else {
			// atualiza valores
			esqPai->setNo (2, pai->getNo (1));
			esqPai->setNChaves (2);

			esqPai->setDir (meioPai->getEsq ());
			if (no->getEsq ())
				meioPai->getEsq ()->setPai (esqPai);

			// novo < 1º "no" < 2º "no"
			if (no->getNo (1)->getChave () > novo->getChave ()) {
				pai->setNo (1, novo);

				// ponteiros: esq < orfao < meio < dir
				if (orfao) {
					meioPai->setEsq (orfao);
					orfao->setPai (meioPai);
				}
			}
			// 1º "no" < novo < 2º "no"
			else if (no->getNo (2)->getChave () > novo->getChave ()) {
				pai->setNo (1, no->getNo (1));
				no->setNo (1, novo);

				// ponteiros: esq < meio < orfao < dir
				if (orfao) {
					meioPai->setEsq (meioPai->getMeio ());
					meioPai->setMeio (orfao);
					orfao->setPai (meioPai);
				}
			}
			// 1º "no" < 2º "no" < novo
			else {
				pai->setNo (1, no->getNo (1));
				no->setNo (1, no->getNo (2));
				no->setNo (2, novo);
			
				// ponteiros: esq < meio < dir < orfao
				if (orfao) {
					meioPai->setEsq (meioPai->getMeio ());
					meioPai->setMeio (meioPai->getDir());
					meioPai->setDir (orfao);
					orfao->setPai (meioPai);
				}
			}
		}
	}
	// CASO 2: underflow em "no"
	else {
		if (pai->getNChaves () == 2 && meioPai == no) {
			
			// atualiza valores
			no->setNo (1, pai->getNo (2));
			no->setNChaves (1); 

			pai->setNo (2, dirPai->getNo (1));
			dirPai->setNChaves (1);
			dirPai->setNo (1, dirPai->getNo (2));
			dirPai->setNo (2, NULL);

			// atualiza ponteiros
			meioPai->setMeio (dirPai->getEsq ());
			if (dirPai->getEsq ())
				dirPai->getEsq ()->setPai (meioPai);

			dirPai->setEsq (dirPai->getMeio ()) ;
			dirPai->setMeio (dirPai->getDir ());
			dirPai->setDir (NULL);
		}
		else {
			// atualiza valores
			no->setNo (1, pai->getNo (1));
			no->setNChaves (1);

			pai->setNo (1, meioPai->getNo (1));
			meioPai->setNChaves (1);
			meioPai->setNo (2, NULL);

			// atualiza ponteiros
			esqPai->setMeio (meioPai->getEsq ());
			if (meioPai->getEsq ())
				meioPai->getEsq ()->setPai (esqPai);

			meioPai->setEsq (meioPai->getMeio ());
			meioPai->setMeio (meioPai->getDir ());
			meioPai->setDir (NULL);
		}
		no->setNo (2, NULL);
	}
}

template <class Chave, class Item>
No <Chave, Item>* arvore23 <Chave, Item>::busca (No23 <Chave, Item>* no, Chave chave)
{
	if (no) {
		// nú único
		if (no->getNChaves () == 1) {
			if (no->getNo (1)->getChave () > chave)  
				return busca (no->getEsq (), chave);
			else if (no->getNo (1)->getChave () < chave) 
				return busca (no->getMeio (), chave);
			else
				return no->getNo (1);
		}
		// nó duplo
		else {
			if (no->getNo (1)->getChave () == chave)
				return no->getNo (1);
			else if (no->getNo (2)->getChave () == chave)  
				return no->getNo (2);	
			
			else if (no->getNo (1)->getChave () > chave) 
				return busca (no->getEsq (), chave);
			else if (no->getNo (2)->getChave () > chave) 
				return busca (no->getMeio (), chave);
			else
				return busca (no->getDir (), chave);
		}
	}
	return NULL;
}

template <class Chave, class Item>
out <Chave, Item>* arvore23 <Chave, Item>::split (No23 <Chave, Item> *no, No <Chave, Item> *add, No23 <Chave, Item> *orfao)
{	
	No23 <Chave, Item> *maior = new No23 <Chave, Item>;
	No <Chave, Item> *interm;
	maior->setNChaves (1);
	maior->setNo (2, NULL);
	
	// CASO 1: add/orfao < 1º "no" < 2º "no"
	if (no->getNo (1)->getChave () > add->getChave ()) {
		// atualiza valores
		interm = no->getNo (1);
		maior->setNo (1, no->getNo (2));
		no->setNo (1, add);

		// atualiza ponteiros: esq < orfao < meio < dir
		if (no->getEsq ()) {
			maior->setEsq (no->getMeio ());
			no->getMeio ()->setPai (maior);

			maior->setMeio (no->getDir ());
			no->getDir ()->setPai (maior);

			no->setMeio (orfao);
			if (orfao)
				orfao->setPai (no);
		}
	}
	// CASO 2: 1º "no" < add/orfao < 2º "no"
	else if (no->getNo (2)->getChave () > add->getChave ()) {

		// atualiza valores
		interm = add;
		maior->setNo (1, no->getNo (2));

		// atualiza ponteiros: esq < meio < orfao < dir
		if (no->getEsq ()) {
			maior->setEsq (orfao);
			if (orfao)
				orfao->setPai (maior);

			maior->setMeio (no->getDir ());
			no->getDir ()->setPai (maior);
		}
	}
	// CASO 3: 1º "no" < 2º "no" < add/orfao
	else {

		// atualiza valores
		interm = no->getNo (2);
		maior->setNo (1, add);

		// atualiza ponteiros: esq < meio < dir < orfao
		if (no->getEsq ()) {
			maior->setEsq (no->getDir ());
			no->getDir ()->setPai (maior);

			maior->setMeio (orfao);
			if (orfao)
				orfao->setPai (maior);
		}
	}

	no->setDir (NULL);
	no->setNChaves (1);
	no->setNo (2, NULL);

	out <Chave, Item> *OUT = new out <Chave, Item> (interm, maior);
	return OUT; 
}

template <class Chave, class Item>
out <Chave, Item>* arvore23 <Chave, Item>::insereR (No23 <Chave, Item> *no, No <Chave, Item> *novo) 
{
	out <Chave, Item> *OUT;

	// CASO 1: árvore vazia
	if (!no) {
		no = new No23 <Chave, Item>;
		no->setNo (1, novo);
		no->setNChaves (1);
		raiz = no;
		return NULL;
	}
	else {
		// folhas
		if (!no->getEsq ()) {
			// CASO 2:caso simples 
			if (no->getNChaves () == 1) {
				if (no->getNo (1)->getChave ().compare (novo->getChave ()) > 0) {
					no->setNo (2, no->getNo (1));
					no->setNo (1, novo);
				}
				else 
					no->setNo (2, novo);
				
				no->setNChaves (2);
				return NULL;
			}
			// CASO 3: overflow
			else {
				OUT = NULL;
				int rot = ifRotaciona (no);
				if (rot == ESQUERDA)
					rotEsq (no, novo, NULL);
				else if (rot == DIREITA)
					rotDir (no, novo, NULL);
				else 
					OUT = split (no, novo, NULL);

				return OUT;
			}
		}
		// não-folha
		else {
			// CASO 4: recursão simples: nó único
			if (no->getNChaves () == 1) {
				if (no->getNo (1)->getChave () > novo->getChave ()) {
					OUT = NULL;
					OUT = insereR (no->getEsq (), novo);

					if (OUT && OUT->orfao) {
						// atualiza valores
						no->setNo (2, no->getNo (1));
						no->setNo (1, OUT->interm);
						no->setNChaves (2);

						//atualiza ponteiros
						no->setDir (no->getMeio ());
						no->setMeio (OUT->orfao);
						OUT->orfao->setPai (no);

					}
				}

				else if (no->getNo (1)->getChave () < novo->getChave ()) { 
					OUT = NULL;
					OUT = insereR (no->getMeio (), novo);

					if (OUT && OUT->orfao) {
						// atualiza valores
						no->setNo (2, OUT->interm);
						no->setNChaves (2);
						
						//atualiza ponteiros
						no->setDir (OUT->orfao);
						OUT->orfao->setPai (no);
						
					}
				}

				return NULL;
			}

			// CASO 5: recursão composta: nó duplo
			else {
				OUT = NULL;
				if (no->getNo (1)->getChave () > novo->getChave ())
					OUT = insereR (no->getEsq (), novo);
				else if (no->getNo (2)->getChave () > novo->getChave ())
					OUT = insereR (no->getMeio (), novo);
				else
					OUT = insereR (no->getDir (), novo);
			

				if (OUT && OUT->orfao) {
					int rot = ifRotaciona (no);
					if (rot == ESQUERDA) {
						rotEsq (no, OUT->interm, OUT->orfao);
						OUT->orfao = NULL;
					}
					else if (rot == DIREITA) {
						rotDir (no, OUT->interm, OUT->orfao);
						OUT->orfao = NULL;
					}
					else
						OUT = split (no, OUT->interm, OUT->orfao);

					return OUT;
				}

				return NULL;
			}
		}		
	}
}

template <class Chave, class Item>
No23 <Chave, Item>* arvore23 <Chave, Item>::merge (No23 <Chave, Item> *no, No23 <Chave, Item> *orfao)
{
	No23 <Chave, Item> *pai = no->getPai ();

	if (pai->getNChaves () == 2 && pai->getDir () == no) {
		pai->getMeio ()->setNo (2, pai->getNo (2));
		pai->getMeio ()->setNChaves (2);

		if (orfao) {
			pai->getMeio ()->setDir (orfao);
			orfao->setPai (pai->getMeio ());
		}
	}

	else {
		if (pai->getEsq () == no) {
			pai->getMeio ()->setNo (2, pai->getMeio ()->getNo (1));
			pai->getMeio ()->setNo (1, pai->getNo (1));
			pai->setNo (1, pai->getNo (2));
			pai->getMeio ()->setNChaves (2);

			if (orfao) {
				pai->getMeio ()->setDir (pai->getMeio ()->getMeio ());
				pai->getMeio ()->setEsq (orfao);
				pai->getMeio ()->setMeio (pai->getMeio ()->getEsq ());
				orfao->setPai (pai->getMeio ());
				
				orfao = pai->getMeio ();
			}

			pai->setEsq (pai->getMeio ());
			pai->setMeio (pai->getDir ());
		}

		else {
			pai->getEsq ()->setNo (2, pai->getNo (1));
			pai->setNo (1, pai->getNo (2));
			pai->getEsq ()->setNChaves (2);
			
			if (orfao) {
				pai->getEsq ()->setDir (orfao);
				orfao->setPai (pai->getEsq ());
				
				orfao = pai->getEsq ();
			}
			pai->setMeio (pai->getDir ());

		}
	}
	pai->setDir (NULL);
	pai->setNChaves (1);
	pai->setNo (2, NULL);

	delete no;
	no = NULL;

	return orfao;
}

template <class Chave, class Item>
No23 <Chave, Item>* arvore23 <Chave, Item>::removeR (No23 <Chave, Item> *no, Chave chave)
{
	No23 <Chave, Item> *orfao = NULL;

	if (no) {
		if (no->getEsq ()) {
			// recursão nó único
			if (no->getNChaves () == 1 && no->getNo (1)->getChave () != chave) {
				if (no->getNo (1)->getChave () > chave) 
					orfao = removeR (no->getEsq (), chave);
				else 
					orfao = removeR (no->getMeio (), chave);

				if (!orfao)
					return NULL;
			}
			// recursão nó duplo
			else if (no->getNo (1)->getChave () != chave && no->getNo (2)->getChave () != chave) {
				if (no->getNo (1)->getChave () > chave)
					orfao = removeR (no->getEsq (), chave);
				else if (no->getNo (2)->getChave () > chave)
					orfao = removeR (no->getMeio (), chave);
				else
					orfao = removeR (no->getDir (), chave);

				if (!orfao)
					return NULL;
			}

			// após recursão 
			if (raiz->getNChaves () == 0) {
				delete raiz;
				raiz = orfao;		
				no = raiz;

				return NULL;
			}

			if (orfao) {
				int rot = ifRotaciona (no);

				if (rot == ESQUERDA)
					rotEsq (no, NULL, orfao);

				else if (rot == DIREITA)
					rotDir (no, NULL, orfao);
				else
					orfao = merge (no, orfao);

				return orfao;
			}

			No23 <Chave, Item> *ptr;
			No <Chave, Item> *aux;

			// CASO 1: nó deletado não-folha
			// no 2º
			if (no->getNChaves () == 2 && no->getNo (2)->getChave () == chave) {
				ptr = no->getMeio ();
				aux = no->getNo (2);
			}
			// no 1º
			else {
				ptr = no->getEsq ();
				aux = no->getNo (1);
			}

			while (ptr->getEsq ()) {
				if (ptr->getNChaves () == 1)
					ptr = ptr->getMeio ();
				else
					ptr = ptr->getDir ();
			}
			if (ptr->getNChaves () == 1) {
				no->setNo (1, ptr->getNo (1));
				ptr->setNo (1, aux);
				
				ptr->setNChaves (0);
				delete ptr->getNo (1);
				ptr->setNo (1, NULL);
				no = ptr;
			}
			else if (ptr->getNChaves () == 2) {
				if (no->getNo (1)->getChave () == chave)
					no->setNo (1, ptr->getNo (2));
				else
					no->setNo (2, ptr->getNo (2));

				ptr->setNo (2, aux);
				ptr->setNChaves (1);
				
				delete ptr->getNo (2);
				ptr->setNo (2, NULL);
				no = ptr;
			}
		}

		// CASO 2: nó deletado folha
		else if (!no->getEsq () && 
			(no->getNo (1)->getChave () == chave || (no->getNo(2) && no->getNo (2)->getChave () == chave))) {

			if (no->getNChaves () == 2) {
				if (no->getNo (1)->getChave () == chave) {
					delete no->getNo (1);
					no->setNo (1, no->getNo (2));
				}
				else 
					delete no->getNo (2);
				
				no->setNChaves (1);
				no->setNo (2, NULL);
			}
			else {
				delete no->getNo (1);
				no->setNChaves (0);
				no->setNo (1, NULL);
			}
		}

		// rebalanceamento
		if (no->getNChaves () == 0 && no == raiz) {
			delete no;
			raiz = NULL;
		} 

		else if (no->getNChaves () == 0) {
			int rot = ifRotaciona (no);

			if (rot == ESQUERDA)
				rotEsq (no, NULL, NULL);
			else if (rot == DIREITA)
				rotDir (no, NULL, NULL);
			else
				orfao = merge (no, NULL);

			return orfao;
		}
	}	
	return NULL;
}

template <class Chave, class Item>
int arvore23 <Chave, Item>::rankR (No23 <Chave, Item> *no, Chave chave)
{
	int cont = 0;

	if (no) {
		// nó único
		if (no->getNChaves () == 1) {
			// menor: contabiliza checa 2 filhos
			if (no->getNo (1)->getChave () < chave) {
				cont ++;
				cont += rankR (no->getMeio (), chave);
				cont += rankR (no->getEsq (), chave);
			}
			// maior ou igual: checa filho esquerdo
			else 
				cont += rankR (no->getEsq (), chave);
		}
		// nó duplo
		else {
			// chave menor ou igual 1º nó: checa filho esquerdo
			if (no->getNo (1)->getChave () >= chave)
				cont += rankR (no->getEsq (), chave);
			// chave igual ou menor que 2º nó (e maior que 1º): contabiliza (1º) e checa esquerda e meio
			else if (no->getNo (2)->getChave () >= chave) {
				cont++;
				cont += rankR (no->getEsq (), chave);
				cont += rankR (no->getMeio (), chave);
			}
			// chave maior que 2º nó: contabiliza (1º e 2º) e checa 3 filhos
			else if (no->getNo (2)->getChave () < chave) {
				cont += 2;
				cont += rankR (no->getEsq (), chave);
				cont += rankR (no->getMeio (), chave);
				cont += rankR (no->getDir (), chave);
			}
		}
	}
	return cont;
}

template <class Chave, class Item>
void arvore23 <Chave, Item>::printA23 (string prefix, No23 <Chave, Item> *no, bool esq)
// Nós únicos são azuis; nós duplos possuem o nó 1 verde e o nó dois rosa; número de nós pe vermelho
{
	const string green ("\033[0;92m");
	const string red ("\033[0;91m");
	const string pink ("\033[0;95m");
	const string blue ("\033[0;94m");
	const string reset ("\033[0m");
    
    if (no)
    {
        cout << prefix;

        cout << (esq ? "├──" : "└──" );
        cout << red << no->getNChaves () << " " << reset;

        if (no->getNChaves () == 2) {
        	cout << green << no->getNo (1)->getChave () << ": " << no->getNo (1)->getValor () << reset << " ";
        	cout << pink << no->getNo (2)->getChave () << ": " << no->getNo (2)->getValor () << reset << "\n";
        }
        
        else if (no->getNChaves () == 1) {
        	cout << blue << no->getNo (1)->getChave () << ": " << no->getNo (1)->getValor () << reset << "\n";
        }

        printA23 (prefix + (esq ? "│   " : "    "), no->getEsq (), true);
        printA23 (prefix + (esq ? "│   " : "    "), no->getMeio (), false);
        printA23 (prefix + (esq ? "│   " : "    "), no->getDir (), false);
    }
}

/************************* Árvore Rubro-Negra *************************/

template <class Chave, class Item>
class arvoreRN
// Os casos numerados são explicados no relatório
{
	NoRN <Chave, Item> *raiz;

	NoRN <Chave, Item>* rotEsq (NoRN <Chave, Item>*);
	NoRN <Chave, Item>* rotDir (NoRN <Chave, Item>*);
	int rankR (NoRN <Chave, Item>*, Chave);

	void fixInsere (NoRN <Chave, Item>*);
	NoRN <Chave, Item>* insereR (NoRN <Chave, Item>*, Chave, Item, NoRN <Chave, Item>*);
	
	NoRN <Chave, Item>* substituto (NoRN <Chave, Item>*);
	void fixRemove (NoRN <Chave, Item>*);
	NoRN <Chave, Item>* removeR (NoRN <Chave, Item>*, Chave);	

	void printRN (string, NoRN <Chave, Item>*, bool);
	
	public:
		arvoreRN (string arquivo)
		{
			string token;
			fstream arqTexto;

			raiz = NULL;
			arqTexto.open (arquivo);

			while (arqTexto >> token) {
				transform (token.begin(), token.end(), token.begin(), ::tolower);
				token = removeSimbolos (token);
				insere (token, 1);
			}
			arqTexto.close ();
		}
		~arvoreRN ();

		void insere (Chave, Item);
		Item devolve (Chave);
		void remove (Chave);
		int rank (Chave);
		Chave seleciona (int);
};

template <class Chave, class Item>
arvoreRN <Chave, Item>::~arvoreRN ()
{
	delete raiz;
}

template <class Chave, class Item>
void arvoreRN <Chave, Item>::insere (Chave chave, Item valor)
{
	NoRN <Chave, Item> *novo = new NoRN <Chave, Item>;
	novo->setChave (chave);
	novo->setValor (valor);
	if (!(raiz))
		novo->setCor (NEGRO);

	raiz = insereR (raiz, chave, valor, novo);

	if (devolve (chave) == 1)
		fixInsere (novo);
}

template <class Chave, class Item>
Item arvoreRN <Chave,Item>::devolve (Chave chave)
{
	NoRN <Chave, Item> *p;

	p = raiz;

	while (p) {
		if (p->getChave () == chave)
			return p->getValor ();
		else if (p->getEsq () || p->getDir ()) {
			if (p->getChave () > chave)
					p = p->getEsq ();
			else if (p->getChave () < chave)
					p = p->getDir ();
		}
	}

	cout << "Chave não encontrada.\n";
	return 0;
}

template <class Chave, class Item>
void arvoreRN <Chave,Item>::remove (Chave chave)
{
	raiz = removeR (raiz, chave);
}

template <class Chave, class Item>
int arvoreRN <Chave, Item>::rank (Chave chave)
{
	return rankR (raiz, chave);
}

template <class Chave, class Item>
Chave arvoreRN <Chave, Item>::seleciona (int k)
{
	int rankNo = 0;
	NoRN <Chave, Item> *p;
	p = raiz;

	while (p) {
		if ((rankNo = rank (p->getChave ())) == k)
			return p->getChave ();
		else if (rankNo < k) 
			p = p->getDir ();
		else
			p = p->getEsq ();
	}

	cout << "Não existem " << k + 1 << " chaves nessa tabela de símbolos.\n";
	return "";
}

// Funções auxiliares

template <class Chave, class Item>
void arvoreRN <Chave, Item>::fixInsere (NoRN <Chave, Item> *x)
{
	NoRN <Chave, Item> *pai = NULL;	
	NoRN <Chave, Item> *vo = NULL;	

	while (x != raiz && x->getCor () != NEGRO && x->getPai ()->getCor () == RUBRO) {
		pai = x->getPai ();
		vo = x->getPai ()->getPai ();

		// pai é filho esquerdo E_
		if (pai == vo->getEsq ()) {
			
			// CASO 1: TIO RUBRO
			if (x->getTio(x) && x->getTio (x)->getCor () == RUBRO) {
				vo->setCor (RUBRO);
				pai->setCor (NEGRO);
				x->getTio (x)->setCor (NEGRO);
				x = vo; 
			}

			// CASO 2: ED
			else {
				if (x == pai->getDir()) {
					pai = rotEsq (pai);
					x = pai;
					pai = x->getPai ();
				}

				// CASO 3: EE
				vo = rotDir (vo);
				pai->trocaCor ();
				vo->trocaCor ();
				x = pai;
			}
		}

		// pai é filho direito D_
		else {

			// CASO 1: TIO RUBRO
			if (x->getTio(x) && x->getTio (x)->getCor () == RUBRO) {
				vo->setCor (RUBRO);
				pai->setCor (NEGRO);
				x->getTio (x)->setCor (NEGRO);
				x = vo; 
			}

			// CASO 4: DE
			else {
				if (x == pai->getEsq ()) {
					pai = rotDir (pai);
					x = pai;
					pai = x->getPai ();
				}

				// CASO 5: DD
				vo = rotEsq (vo);
				pai->trocaCor ();
				vo->trocaCor ();
				x = pai;

			}
		}
	}

	raiz->setCor (NEGRO);
}

template <class Chave, class Item>
NoRN <Chave, Item>* arvoreRN <Chave, Item>::insereR (NoRN <Chave, Item>* no, Chave chave, Item valor, NoRN <Chave, Item> *novo)
{
	if (no == NULL) 
		return novo;

	if (no->getChave () > chave) {
		no->setEsq (insereR (no->getEsq (), chave, valor, novo));
		no->getEsq ()->setPai (no);
	}
	else if (no->getChave () < chave) {
		no->setDir (insereR (no->getDir (), chave, valor, novo));
		no->getDir ()->setPai (no);
	}
	else {
		delete novo;
		no->setValor (no->getValor () + valor);
	}

	return no;
}

template <class Chave, class Item>
NoRN <Chave, Item>* arvoreRN <Chave, Item>::substituto (NoRN <Chave, Item> *no)
{
	if (no->getEsq () && no->getDir ()) {
		NoRN <Chave, Item> *p = no;
		while (p->getEsq ())
			p = p->getEsq ();
		return p; 
	}

	if (!(no->getEsq ()) && !(no->getDir ()))
		return NULL;
	if (no->getEsq ())
		return no->getEsq ();
	else
		return no->getDir ();
}

template <class Chave, class Item>
void arvoreRN <Chave, Item>::fixRemove (NoRN <Chave, Item> *no)
{
	if (no == raiz) 
		return;

	NoRN <Chave, Item> *pai, *irmao;
	pai = no->getPai ();

	if (pai->getEsq () == no)
		irmao = pai->getDir ();
	else
		irmao = pai->getEsq (); 

	if (!irmao)
		fixRemove (pai);
	else {
		// CASOS 1 e 2: irmão rubro
		if (irmao->getCor () == RUBRO) {
			pai->setCor (RUBRO);
			irmao->setCor (NEGRO);

			// CASO 1: E (irmão)
			if (pai->getEsq () == irmao) 
				pai = rotDir (pai);

			// CASO 2: D (irmão)
			else
				pai = rotEsq (pai);
			
			fixRemove (no);
		}
		else {
			// CASOS 3, 4, 5 e 6: irmão negro com filho(s) rubro(s) 
			if (irmao->filhoRubro ()) {
				if (irmao->getEsq () && irmao->getEsq ()->getCor () == RUBRO) {
					// CASO 3: EE (irmão)(sobrinho)
					if (pai->getEsq () == irmao) {
						irmao->getEsq ()->setCor (irmao->getCor ());
						irmao->setCor (pai->getCor ());
						pai = rotDir (pai);
					}
					// CASO 4: DE (irmão)(sobrinho)
					else {
						irmao->getEsq ()->setCor (pai->getCor ());
						irmao = rotDir (irmao);
						pai = rotEsq (pai);
					}
				}
				else {
					// CASO 5: ED (irmão)(sobrinho)
					if (pai->getEsq () == irmao) {
						irmao->getDir ()->setCor (pai->getCor ());
						irmao = rotEsq (irmao);
						pai = rotDir (pai);
					}
					// CASO 6: DD (irmão)(sobrinho)
					else {
						irmao->getDir ()->setCor (irmao->getCor ());
						irmao->setCor (pai->getCor ());
						pai = rotEsq (pai);
					}
				}
				pai->setCor (NEGRO);
			}
			// CASO 7: irmão negro com filhos negros
			else {
				irmao->setCor (RUBRO);
				if (pai->getCor () == NEGRO)
					fixRemove (pai);
				else
					pai->setCor (NEGRO);
			}
		}
	}
}

template <class Chave, class Item>
NoRN <Chave, Item>* arvoreRN <Chave, Item>::removeR (NoRN <Chave, Item> * no, Chave chave)
{
	int pos = 0;
	NoRN <Chave, Item> *irmao, *sub;
	Item aux; 
	sub = substituto (no);

	if (no != raiz) {
		if (no->getPai ()->getEsq () && no->getPai ()->getEsq () == no) {
			pos = ESQUERDA;
			irmao = no->getPai ()->getDir ();
		}
		else {
			pos = DIREITA;
			irmao = no->getPai ()->getEsq (); 
		}
	}

	if (!no) {
		cout << "Chave não encontrada.\n";
		return no;
	}
	if (no->getChave () > chave) 
		no->setEsq (removeR (no->getEsq (), chave));

	else if (no->getChave () < chave) 
		no->setDir (removeR (no->getDir (), chave));

	else {
		// achei o cara a ser removido
		if (!sub) {
			if (no == raiz) {
				raiz = NULL;
				return NULL;
			}

			if (no->getCor () == NEGRO) 
				fixRemove (no);

			// CASO SIMPLES
			else
				if (irmao)
					irmao->setCor (RUBRO);
			if (pos == ESQUERDA)
				no->getPai ()->setEsq (NULL);
			else
				no->getPai ()->setDir (NULL);
			
			delete no;
			return sub;
		}
		else if (no->getEsq () && no->getDir ()) {
			aux = sub->getValor ();
			sub->setValor (no->getValor ());
			no->setValor (aux);
			removeR (sub, sub->getChave());
		}
		else {
			if (no == raiz) 
				delete no;
			
			else {
				if (pos == ESQUERDA)
					no->getPai ()->setEsq (sub);
				else
					no->getPai ()->setDir (sub);

				sub->setPai (no->getPai ());
				delete no;

				if ((!sub || sub->getCor () == NEGRO) && (no->getCor () == NEGRO))
					fixRemove (sub);

				// CASO SIMPLES
				else 
					sub->setCor (NEGRO);
			}
			return sub;
		}
	}
	return no;
}

template <class Chave, class Item>
int arvoreRN <Chave, Item>::rankR (NoRN <Chave, Item> *no, Chave chave)
{
	int cont = 0;

	if (no) {
		if (no-> getChave () < chave) {
			cont++;
			cont += rankR (no->getEsq (), chave);
			cont += rankR (no->getDir (), chave);
		}
		else if (no->getChave () >= chave)
			cont += rankR (no->getEsq (), chave);
	}
	return cont; 
}

template <class Chave, class Item>
NoRN <Chave, Item>* arvoreRN <Chave, Item>::rotEsq (NoRN <Chave, Item> *ptr)
{
	NoRN <Chave, Item> *ptrD;
	ptrD = ptr->getDir ();
	ptr->setDir (ptrD->getEsq ());

	if (ptr->getDir ())
		ptr->getDir ()->setPai (ptr);

	ptrD->setPai (ptr->getPai ());

	if (!(ptr->getPai ()))
		raiz = ptrD;

	// se ptr for filho esquerdo
	else if (ptr == ptr->getPai ()->getEsq ())
		ptr->getPai ()->setEsq (ptrD);

	// se ptr for filho direito
	else
		ptr->getPai ()->setDir (ptrD);

	ptrD->setEsq (ptr);
	ptr->setPai (ptrD);

	return ptrD;
}

template <class Chave, class Item>
NoRN <Chave, Item>* arvoreRN <Chave, Item>::rotDir (NoRN <Chave, Item> *ptr)
{
	NoRN <Chave, Item> *ptrE;
	ptrE = ptr->getEsq ();
	ptr->setEsq (ptrE->getDir ());

	if (ptr->getEsq ())
		ptr->getEsq ()->setPai (ptr);

	ptrE->setPai (ptr->getPai ());

	if (!(ptr->getPai ()))
		raiz = ptrE;

	// se ptr for filho esquerdo
	else if (ptr == ptr->getPai ()->getEsq ())
		ptr->getPai ()->setEsq (ptrE);

	// se ptr for filho direito
	else
		ptr->getPai ()->setDir (ptrE);

	ptrE->setDir (ptr);
	ptr->setPai (ptrE);

	return ptrE;
}

template <class Chave, class Item>
void arvoreRN <Chave, Item>::printRN (string prefix, NoRN <Chave, Item> *no, bool esq)
{
	const string red ("\033[0;31m");
	const string reset ("\033[0m");

    if (no != nullptr)
    {
        cout << prefix;


        if (no->getCor () == RUBRO) {
        	cout << red << (esq ? "├──" : "└──" );
        	cout << no->getChave () << ": " << no->getValor () << reset << "\n";
        }
        else {
        	cout << (esq ? "├──" : "└──" );
        	cout << no->getChave () << ": " << no->getValor () << "\n";
        }

        printRN (prefix + (esq ? "│   " : "    "), no->getEsq (), true);
        printRN (prefix + (esq ? "│   " : "    "), no->getDir (), false);
    }
}

/************************* Hashing Table *************************/
template <class Chave, class Item>
class hashTable
{
 	NoLista <Chave, Item> **hashHead;
 	int tamMax;
 	
 	int hash (Chave chave);
 	void printHS ();

 	public:
 		hashTable (string arquivo)
 		{
			string token;
			fstream arqTexto;

			tamMax = 5000;
			hashHead = new NoLista <Chave, Item>* [tamMax];

			for (int i = 0; i < tamMax; i++)
				hashHead [i] = nullptr;

			arqTexto.open (arquivo);
			while (arqTexto >> token) {
				transform (token.begin(), token.end(), token.begin(), ::tolower);
				token = removeSimbolos (token);
				insere (token, 1);
			}
			arqTexto.close ();
 		}

 		~hashTable ();

		void insere (Chave, Item);
		Item devolve (Chave);
		void remove (Chave);
		int rank (Chave);
		Chave seleciona (int);
};

template <class Chave, class Item>
hashTable <Chave, Item>::~hashTable ()
{
	for (int i = 0; i < tamMax; i++) 
		delete [] hashHead [i];
	delete [] hashHead;
}

template <class Chave, class Item>
void hashTable <Chave, Item>::insere (Chave chave, Item valor)
{
	int h = hash (chave);
	NoLista <Chave, Item> *p;
	if (hashHead [h]) {
		p = hashHead [h];		
		while (p) {
			if (p->getChave () == chave) {
				p->setValor (p->getValor () + valor);
				return;
			}
			p = p->getProx ();
		}
		
	}

	NoLista <Chave, Item> *novo = new NoLista <Chave, Item>;
	novo = new NoLista <Chave, Item>;
	novo->setChave (chave);
	novo->setValor (valor);
	novo->setProx (hashHead [h]);
	hashHead [h] = novo;
}

template <class Chave, class Item>
Item hashTable <Chave,Item>::devolve (Chave chave)
{
	int h = hash (chave);
	NoLista <Chave, Item> *p = hashHead [h]; 

	while (p) {
		if (p->getChave () == chave)
			return p->getValor ();
		p = p->getProx ();
	}

	cout << "Chave não encontrada.\n";
	return 0;
}

template <class Chave, class Item>
void hashTable <Chave, Item>::remove (Chave chave)
{
	int h = hash (chave);
	NoLista <Chave, Item> *aux, *p; 
	aux = p = NULL;
	if (hashHead [h])
		p = hashHead [h];

	while (p) {
		if (p->getChave () == chave){
			if (aux != NULL)
				aux->setProx (p->getProx ());
			else
				hashHead [h] = p->getProx ();
			delete p;
			p = NULL;
			return;
		}
		else 
			aux = p;
		p = p->getProx ();
	}

	cout << "Chave não encontrada.\n";
}

template <class Chave, class Item>
int hashTable <Chave, Item>::rank (Chave chave)
{
	NoLista <Chave, Item> *p;	
	int cont = 0;

	for (int i = 0; i < tamMax; i++)
		if (hashHead [i] && !(hashHead [i]->getChave ().empty ())) {
			p = hashHead [i];
			while (p && !(p->getChave ().empty ())) {
				if (p->getChave () < chave) 
					cont ++;
				p = p->getProx ();
			}
		}

	return cont; 
}

template <class Chave, class Item>
Chave hashTable <Chave, Item>::seleciona (int k)
{
	NoLista <Chave, Item> *p;

	for (int i = 0; i <tamMax; i++)
		if (hashHead [i])
			for (p = hashHead [i]; p != NULL; p = p->getProx ())
				if (rank (p->getChave ()) == k)
					return p->getChave ();

	cout << "Chave não encontrada.\n";
	return "";
}

// Funções auxiliares

template <class Chave, class Item>
int hashTable <Chave, Item>::hash (Chave chave)
{
  int h = chave [0];
  
  for (int i = 1; chave[i] != '\0'; i++)
    h = (h * 251 + chave [i]) % tamMax;
  
  return h;
}

template <class Chave, class Item>
void hashTable <Chave, Item>::printHS ()
{
	NoLista <Chave, Item> *p;

	cout << ". . . . . . . . . . . . . . . . . . . . . . .\n";
	cout << "Tabela de símbolos: { código: lista de chaves }\n";

	for (int h = 0; h < tamMax; h++)
		if (hashHead [h] && !(hashHead [h]->getChave ().empty ())) {
			p = hashHead [h];
			while (p) {
				cout << "{ " << h << ": " << p->getChave () << " - " << p->getValor () << " }\n"; 
				p = p->getProx ();
			}
		}
}

#endif