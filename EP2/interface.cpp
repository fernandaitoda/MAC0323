/***********************************
EP2: GRAFOS DE TEXTOS
MAC0323

Fernanda Itoda
10740825
************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <sstream>
#include <string.h>
#include <queue>
#include <list>
#include <math.h>

using namespace std;

#define PROMPT      cout << ">>> ";
#define ERROR(msg)   fprintf(stderr,"ERROR: %s\n", #msg)
#define WARNING(msg) fprintf(stdout,"WARNING: %s\n", #msg)

static void mostreUso (char *nomePrograma);
string removeSimbolos (string s);

class AdjNode
{
    int ind;
    AdjNode *prox;

    public:
        AdjNode (): prox (nullptr) {}; 
        AdjNode (int i): ind (i), prox (nullptr) {}; 

        void setInd (int indice)
            { ind = indice; }
        void setProx (AdjNode *px)
            { prox = px; }
        int getInd ()
            { return ind; }
        AdjNode* getProx ()
            { return prox; }
};

class Vertex 
{
    string palavra;
    int grau;
    AdjNode *list;

    public:
        Vertex (): list (nullptr) {}; 
        Vertex (string pal): palavra (pal), grau (0), list (nullptr) {};

        void setPal (string pal)
            { palavra = pal; }
        void setGrau (int g)
            { grau = g; }
        void setList (AdjNode* cab)
            { list = cab; }
        string getPal ()
            { return palavra; }
        int getGrau ()
            { return grau; }
        AdjNode* getList ()
            { return list; }

};

//k definido como no enunciado será passado como argumento de linha de comando
class Grafo
{
    Vertex **graph;
    int *comp;
    int V, E, C;
    int min, tamMax;

    int nComponentes ();
    void componentesR (int, int); 
    int setEdges (Vertex*, int);
    int buscaDFS (Vertex*, bool);
    int DFSr (int, Vertex*, bool*, bool);
    bool emCicloR (int, int*, int, int);
    bool ifPath (int, int);

    void resize();
    
    void printG();

    public:

    Grafo (int k, string arquivo) {
        /* Inicializa um grafo com parâmetro k */
        
        string token;
        fstream arqTexto;

        graph = new Vertex* [1];
        graph[0] = nullptr;


        V = E = C = 0;
        tamMax = 1;
        min = k;

        arqTexto.open (arquivo);
		while (arqTexto >> token) {
			transform (token.begin(), token.end(), token.begin(), ::tolower);
			token = removeSimbolos (token);
			if (!(token.empty ()))
				insere (token);
		}
        arqTexto.close();

        comp = new int [V];
        for (int i = 0; i < V; i++)
            comp[i] = -1;
        C = nComponentes();
    }

    int insere (string);
    /* Insere a palavra e retorna o número de arestas adicionados ao grafo,
        retorna -1 se a palavra já está no grafo ou tem tamanho menor que k */

    int vertices() 
    /* Retorna o número de vértices do grafo */
        { return V; }

    int arestas() 
    /* Retorna o número de arestas do grafo */
        { return E; }

    int componentes()
    /* Retorna o número de componentes do grafo */
        { return C; }

    bool conexo(); 
    /* Retorna se o grafo é ou não conexo */

    int tamComp (string);
    /* Retorna o tamanho da componente conexa onde está a palavra
        ou -1 caso ela não se encontre no grafo */

    int dist (string, string); 
    /* Retorna a menor distância entre as palavras a e b ou -1
        caso elas estejam desconexas ou não estejam no grafo */
    

    bool emCiclo (string a);
    /* Retorna verdadeiro casa a palavra esteja em algum ciclo,
        falso caso contrário */
    
    bool emCiclo (string a, string b); 
    /* Retorna verdadeiro casa exista um ciclo que contenha ambas as palavras,
        falso caso contrário */
    
    int mediaGraus();
    /* Retorna a média dos graus de todos os vértices */

    int analiseComp (char);
    /* Retorna o tamanho médio das componentes, a maior componente ou a menor componente */

    int mediaDist();
    /* Retorna a distância média entre duas palavras no grafo */
};

int Grafo::insere (string palavra)
{
    /* Insere a palavra e retorna o número de arestas adicionados ao grafo,
    retorna -1 se a palavra já está no grafo ou tem tamanho menor que k*/

    if (V == tamMax)
        resize();

    int newEdges = 0;

    if (palavra.length() < (unsigned int) min) 
        return -1;

    Vertex *novo = new Vertex (palavra);
    if (buscaDFS (novo, false) != (-1)) {
        delete novo;
        return -1;
    }
    
    graph[V] = novo;
    V++;
    newEdges = buscaDFS (novo, true);

    return newEdges;
}

bool Grafo::conexo()
{
    for (int i = 0; i < V; i++) 
        for (int j = 0; j < V; j++) 
            if (comp[i] != comp[j])
                return false;
    return true;
}

int Grafo::tamComp (string palavra)
{
    Vertex *aux = new Vertex (palavra);
    
    int indice = buscaDFS (aux, false);
    delete aux;

    if (indice == -1)
        return -1;
    
    // tamanho = V + E
    return (2 * graph[indice]->getGrau() + 1) ; 
}

int Grafo::dist (string a, string b)
{
    bool *visited = new bool[V];
    int *distance = new int[V];
    queue<int> Q;

    Vertex Va (a), Vb (b);
    int ind1 = buscaDFS (&Va, false);
    int ind2 = buscaDFS (&Vb, false);

    if (ind1 == -1 || ind2 == -1 || graph[ind1]->getGrau() == 0) 
        return -1;

    for (int v = 0; v < V; v++) {
        visited[v] = false;
        distance[v] = 0;
    }

    distance[ind1] = 0;
    visited[ind1] = true;
    Q.push (ind1);

    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();

        for (AdjNode *p = graph[v]->getList(); p; p = p->getProx())
            if (visited[p->getInd()] == false) {
                distance[p->getInd()] = distance[v] + 1;
                visited[p->getInd()] = true;
                Q.push (p->getInd());
            }
    }
    return distance[ind2];
}

bool Grafo::emCiclo (string a)
{
    int *visited = new int[V];
    
    for (int v = 0; v < V; v++)  
        visited[v] = -1;

    for (int i = 0; i < V; i++)
        if (graph[i]->getPal() == a) {
            if (graph[i]->getGrau() > 0)
                return true;
            return (emCicloR (i, visited, -1, i));
        }
    
    return false;
}

bool Grafo::emCiclo (string a, string b)
{
    int *visited = new int[V];
    int A = -1, B = -1;

    for (int v = 0; v < V; v++)  
        visited[v] = -1;

    for (int i = 0; i < V; i++) {
        if (graph[i]->getPal() == a)
            A = i;
        else if (graph[i]->getPal() == b)
            B = i; 
        
        if (A != (-1) && B != (-1)) {
            if (graph[A]->getGrau() > 0 && graph[B]->getGrau() > 0) {
                for (AdjNode *p = graph[A]->getList(); p; p = p->getProx())
                    if (p->getInd() == B)
                        return true;
            }
            else if (ifPath (A, B)) 
                return (emCicloR (B, visited, -1, A));
        
            else
                return false;
        }
    }
    
    return false;   
}

int Grafo::mediaGraus()
{
    int soma = 0;

    for (int v = 0; v < V; v++)
        soma += graph[v]->getGrau ();
    
    return (soma / V);
}

int Grafo::analiseComp (char indicador)
{
    int *tam = new int[C];

    for (int i = 0; i < C; i++)
        tam[i] = -1;

    for (int v = 0; v < V; v++) 
        if (tam[comp[v]] == (-1))
            tam[comp[v]] = tamComp (graph[v]->getPal());

    if (indicador == '+') {
        int soma = 0;
        
        for (int i = 0; i < C; i++)
            soma += tam[i];

        return (soma / C);    
    }

    else if (indicador == '>') {
        int maior = -1;

        for (int i = 0; i < C; i++)
            if (tam[i] > maior)
                maior = tam[i];

        return maior;
    }

    else {
        int menor = 999999;

        for (int i = 0; i < C; i++)
            if (tam[i] < menor)
                menor = tam[i];

        return menor;
    }
}

int Grafo::mediaDist()
{
    int soma = 0;
    int nCombinacoes = 0;

    for (int v = 0; v < V; v++)
        for (int vv = v + 1; vv < V; vv++) {
            soma += dist (graph[v]->getPal(), graph[vv]->getPal());
            nCombinacoes++;
        }

    return (soma / nCombinacoes);
}

// Funções auxiliares
int Grafo::nComponentes()
{
    int cont = 0;

    for (int v = 0; v < V; v++) {
        if (comp[v] == (-1))
            componentesR (v, cont++);
    }
    return cont;
}

void Grafo::componentesR (int v, int cont) 
{
    comp[v] = cont;

    for (AdjNode *p = graph[v]->getList(); p; p = p->getProx()) {
        if (comp[p->getInd()] == -1)
            componentesR (p->getInd(), cont);
    }
}

int Grafo::DFSr (int v, Vertex* novo, bool visited[], bool ifSetEdges)
{
    AdjNode *p = nullptr;
    int indAtual = 0;
    int found;

    ifSetEdges ? found = 0 : found = -1;

    if (graph[v]->getPal() == novo->getPal()) {
        if (ifSetEdges)
            return 0;
        else
            return v;
    }
        
    visited[v] = true;
    
    if (ifSetEdges == true)
        found += setEdges (novo, v);

    for (p = graph[v]->getList(); p; p = p->getProx()) {
        indAtual = p->getInd();
        if (visited[indAtual] == false)
            (ifSetEdges ? found += DFSr (indAtual, novo, visited, true) 
            : found = DFSr (indAtual, novo, visited, false));
        
        if (!(ifSetEdges) && found) 
            return found;

    }    
    return found;
}

int Grafo::buscaDFS (Vertex* novo, bool ifSetEdges)
{
    bool *visited = new bool[V];
    int found;

    ifSetEdges ? found = 0 : found = -1;
    
    for (int i = 0; i < V; i++)
        visited[i] = false;

    for (int v = 0; v < V; v++) {
        if (visited[v] == false)
            (ifSetEdges ? found += DFSr (v, novo, visited, true) 
            : found = DFSr (v, novo, visited, false));

        if (!(ifSetEdges) && found != (-1))
            return found;
    }
    return found;
}

int Grafo::setEdges (Vertex *novo, int i)
{
    int nEdges = 0; 

    if (novo->getPal().size() == graph[i]->getPal().size()) {
        int difChar = 0;

        int prim = 0, seg = 0;
        for (unsigned int k = 0; k < novo->getPal().size() && difChar < 3; ++k) 
            if (novo->getPal()[k] != graph[i]->getPal()[k]) {
                difChar++;
                if (difChar == 1) 
                    prim = k;

                else if (novo->getPal()[prim] != graph[i]->getPal()[k]
                    || novo->getPal()[k] != graph[i]->getPal()[prim])
                    break;
                
                else
                    seg = k;
            }  
        
        // CASO 1: permutação de 2 letras || CASO 2: substituição de 1 letra
        if ((difChar == 2 && seg > prim) || difChar == 1) {

            AdjNode *no = new AdjNode (i);
            if (!novo->getList()) {
                novo->setList (no);
            }
            else {
                AdjNode *ptr = novo->getList();
                while (ptr->getProx())
                    ptr = ptr->getProx();
                ptr->setProx (no);
            }

            AdjNode *no2 = new AdjNode (V-1); 
            if (!graph[i]->getList()) {
                graph[i]->setList (no2);
            }
            else {
                AdjNode *ptr2 = graph[i]->getList();
                while (ptr2->getProx())
                    ptr2 = ptr2->getProx();
                ptr2->setProx (no2);
            }
            novo->setGrau (novo->getGrau() + 1);
            graph[i]->setGrau (graph[i]->getGrau() + 1);
            nEdges += 2;
        } 
    }
    
    else {
        Vertex *maior, *menor;
        if (max (novo->getPal().size(), graph[i]->getPal().size()) == novo->getPal().size()) {
            maior = novo;
            menor = graph[i];
        }
        else {
            maior = graph[i];
            menor = novo;
        }

        // CASO 3: remoção/inserção de 1 letra
        if ( maior - menor == 1) {

            int difChar = 0;
            for (unsigned int Ia = 0, Ie = 0; Ie < menor->getPal().size() && difChar < 2; Ia++, Ie++) 
                if (maior->getPal()[Ia] != menor->getPal()[Ie]) {
                    Ia++;
                    difChar++;
                }
            
            // É vizinha
            if (difChar < 2) {
                if (!novo->getList()) {
                    AdjNode *no = new AdjNode (i);
                    novo->setList (no);
                }

                else {
                    AdjNode *ptr = novo->getList();
                    
                    while (ptr->getProx())
                        ptr = ptr->getProx();
                    
                    AdjNode *no = new AdjNode (i);
                    ptr->setProx (no);
                }

                AdjNode *no2 = new AdjNode (V-1); 
                if (!graph[i]->getList())
                    graph[i]->setList (no2);
                else {
                    AdjNode *ptr2 = graph[i]->getList();
                    while (ptr2->getProx())
                        ptr2 = ptr2->getProx();
                    ptr2->setProx (no2);
                }
                novo->setGrau (novo->getGrau() + 1);
                graph[i]->setGrau (graph[i]->getGrau() + 1);
                nEdges += 2;
            }
        }
    }
    E += nEdges;
    return nEdges;
}

bool Grafo::emCicloR (int v, int visited [], int parent, int a)
{
    if (parent != (-1))
        visited[v] = visited[parent] + 1;
    else
        visited[v] = 0;

    for (AdjNode *p = graph[v]->getList(); p; p = p->getProx()) {
        if ((visited[p->getInd()]) == (-1)) {
            if (emCicloR (p->getInd(), visited, v, a))
                return true;
        }
        else if (p->getInd() == a && visited[v] > 1) 
            return true;
    }
    return false;
}

bool Grafo::ifPath (int a, int b)
{
    if (a == b)
        return true;
    
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    list<int> path;

    visited[a] = true;
    path.push_back(a);
    
    while (!path.empty()) {
        a = path.front();
        path.pop_front();

        for (AdjNode *p = graph[a]->getList(); p; p = p->getProx()) {
            if (p->getInd() == b)
                return true;
            
            else if (!visited[p->getInd()]) {
                visited[p->getInd()] = true;
                path.push_back(p->getInd());
            }
        }
    }
    return false;
}

void Grafo::resize() 
{
    Vertex **novo = new Vertex* [tamMax * 2];
    memcpy (novo, graph, tamMax * sizeof (Vertex*) );

    graph = novo;
    tamMax = tamMax * 2;
}

void Grafo::printG()
{ 
    const string green ("\033[0;92m");
	const string red ("\033[0;91m");
	const string pink ("\033[0;95m");
	const string blue ("\033[0;94m");
	const string reset ("\033[0m");
    
    AdjNode *p;

    cout << "\n";
    for (int v = 0; v < V; ++v) 
    { 
        cout << red << "V" << v << ": ";
        cout << pink << "G" << graph[v]->getGrau() << " ";
        cout << green << graph[v]->getPal() << reset;
        p = graph [v]->getList();
        while (p) {
           cout << blue << " -> " << graph[p->getInd()]->getPal() << reset;
           p = p->getProx ();
        }
        printf("\n"); 
    } 
}

void doTest (Grafo *G)
{
    string operacao;

     /* mostre uso */
    cout << "Possiveis operacoes do teste interativo:\n";
    cout << "medidas, conexidade, distMedia, tamConexa <string>, distancia <string string>,"
            " emCiclo1 <string>, emCiclo2 <string string>\n";
    cout << "CRTL-D para encerrar.\n";
    PROMPT;

    while (cin >> operacao) {
        /* pegue operacao a ser testada */
        if (operacao == "") {
             ERROR (operacao esperada);
        }

        else if (operacao.compare ("medidas") == 0) {
            int key = 0;
            
            /* VÉRTICES */
            key = G->vertices();
            if (key == 0) 
                cout << "0 vértices.\n";
            else 
                cout << " Número de vértice(s): " << key << "\n";
            
            /* ARESTAS */
            key = 0;
            key = G->arestas();
            if (key == 0) 
                cout << "0 arestas.\n";
            else 
                cout << " Número de aresta(s): " << key << "\n";
            
            /* GRAU MÉDIO */
            key = 0;
            key = G->mediaGraus();
            cout << " Grau médio: " << key << "\n";
        
            /* DENSO */
            bool key2 = false;
            int a, b;
            a = G->arestas();
            b = pow (G->vertices(), 2);
            
            while (a != 0 && b != 0) {
                a = a / 10;
                b = b / 10;
            }
            if (a == 0 && b == 0) 
                key2 = true;

            if (key2 == true)
                cout << " O grafo é denso.\n";
            else 
                cout << " O grafo não é denso.\n";
        }

        else if (operacao.compare ("conexidade") == 0) {
            bool key = false;
            key = G->conexo();
            
            if (key == false) 
                cout << " O grafo não é conexo.\n";
            else 
                cout << " O grafo é conexo.\n";
        
            /* COMPONENTES */
            int key2 = 0;
            key2 = G->componentes();
            
            if (key2 == 0) 
                cout << " 0 componentes.\n";
            else 
                cout << " Número de componente(s): " << key2 << "\n";
            
            if (key2 != 0) {
                /* TAMANHO MÉDIO DAS COMPONENTES */
                key2 = 0;
                key2 = G->analiseComp ('+');
                cout << " Tamanho médio da(s) componente(s): " << key2 << "\n";

                /* MAIOR COMPONENTE */
                key2 = 0;
                key2 = G->analiseComp ('>');

                if (key2 == (-1))
                    cout << " O grafo não possui componentes.\n";
                else 
                    cout << " Tamanho da maior componente: " << key2 << "\n";

                /* MENOR COMPONENTE */
                key2 = 0;
                key2 = G->analiseComp ('<');
                
                if (key2 == 999999)
                    cout << " O grafo não possui componentes.\n";
                else
                    cout << " Tamanho da menor componente: " << key2 << "\n";
            }
        }

        /* DISTÂNCIA MÉDIA ENTRE 2 PALAVRAS */
        else if (operacao.compare ("distMedia") == 0) {
            int key = 0;
            key = G->mediaDist();
            cout << " Distância média entre 2 palavras: " << key << "\n";
            
        }

        else {
            /* operação necessita de argumento(s) key */
            string key = "";
            cin >> key;
            if (key == " ") 
                ERROR (operacao necessita uma palavra);
            else {
                /*---------------------------------*/
                if (operacao.compare ("tamConexa") == 0) {
                    int tamanho = 0;
                    tamanho = G->tamComp (key); /* consulte o Grafo */
                    /* mostre o resultado da consulta */
                    if (tamanho == -1) 
                        cout << " Palavra não encontrada.\n";
                    else 
                        cout << " " << key << ": " << tamanho << "\n";
                }

                else if (operacao.compare ("distancia") == 0) {
                    string key2 = "";
                    cin >> key2;
                    
                    if (key2 == " ")
                        ERROR (operacao necessita de 2 palavras);
                    
                    int distancia = 0;
                    distancia = G->dist (key, key2); /* consulte o Grafo */
                    /* mostre o resultado da consulta */
                    if (distancia == 0) 
                        cout << " As palavras são iguais ou não estão conectadas.\n";
                    else 
                        cout << " 'Distância de '" << key << "' à '" << key2 << "': " << distancia << "\n";
                }

                else if (operacao.compare ("emCiclo1") == 0) {
                    bool ciclo = false;

                    ciclo = G->emCiclo (key); /* consulte o Grafo */
                    
                    /* mostre o resultado da consulta */
                    if (ciclo == false)
                        cout << " '" << key << "' não está em um ciclo\n";
                    else
                        cout << " '" << key << "' está em um ciclo\n";
                }

                else if (operacao.compare ("emCiclo2") == 0) {
                    string key2 = "";
                    cin >> key2;

                    bool ciclo = false;
                    
                    if (key2 == " ") 
                        ERROR (operacao necessita duas palavra);

                    ciclo = G->emCiclo (key, key2); /* consulte o Grafo */
                    
                    /* mostre o resultado da consulta */
                    if (ciclo == false)
                        cout << " '" << key << "' e '" << key2 << "' não estão em um ciclo\n";
                    else
                        cout << " '" << key << "' e '" << key2 << "' estão em um ciclo\n";
                }

                else 
                    ERROR(operacao nao reconhecida);
            }
        }
        if (operacao != "");
        PROMPT;
    }
    cout << "\n";
}

int main (int argc, char *argv[])
{
    fstream arqTexto;

    if (argc < 3) mostreUso (argv[0]);

    /* abra arquivo com texto */
    arqTexto.open (argv[1]);

    if (arqTexto.fail()) {
        cout << "ERRO: arquivo" << argv[1] << "nao pode ser aberto.\n";
        exit (EXIT_FAILURE);
    }

    arqTexto.close ();

    cout << "Criando grafo...\n";

    string arqEntrada = argv[1];
    string k = argv [2];
    stringstream aux (k);
    int min = 0;
    aux >> min;

    Grafo *G = new Grafo (min, arqEntrada);

    doTest (G);

    return EXIT_SUCCESS;
}

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

static void 
mostreUso (char *nomePrograma)
{
    cout << "Uso \n"
	     << "prompt> " << nomePrograma << " nome-arquivo k\n"
	     << "    nome-arquivo = nome do arquivo com o texto\n"
         << "    k = nº min de caracteres em uma palavra\n";
    exit(EXIT_FAILURE);
}   