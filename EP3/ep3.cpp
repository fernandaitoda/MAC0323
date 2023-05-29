/***********************************
EP2: RECONHECIMENDO DE EXPRESSÕES REGULARES
MAC0323

Fernanda Itoda
10740825
************************************/

#include <iostream>
#include <string>
#include <regex>
#include "ep3.hpp"

using namespace std;


static void mostreUso (char *nomePrograma);


int main (int argc, char *argv[]) 
{
    if (argc < 3) mostreUso (argv[0]);

    string expr = argv[1];
    string word = argv[2];

    NFA G (expr);
    G.readRE (expr, 0);
    cout << "Para a expressão: " << expr << "\n";
    if (G.checkWord (word, 0, 0) == true)
        cout << "A palavra \"" << word << "\" foi reconhecida \n";
    else
        cout << "A palavra \"" << word << "\" não foi reconhecida \n";
    return EXIT_SUCCESS;
}

static void 
mostreUso (char *nomePrograma)
{
    cout << "Uso \n"
	     << "prompt> " << nomePrograma << " \"ER\" palavra\n"
	     << "    \"ER\" = expressão regular entre aspas\n"
         << "    palavra = palavra a ser reconhecida pela ER\n";
    exit(EXIT_FAILURE);
}   