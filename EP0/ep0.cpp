/****************************************************************
    Nome: Fernanda Itoda
    NUSP: 10740825

    Fonte e comentários: 

****************************************************************/

#include <iostream>
#include <stdlib.h>  
#include <string> 
// #include <time.h> 
using namespace std;

#define T 50
#define K 4
#define C 20
#define V 20
#define EMERGENCIAS 30

#define POUSO 0
#define DECOLAGEM 1
#define IMEDIATO 4
#define COMBUSTIVEL 2
#define ESPERA 3
#define TRUE 1
#define FALSE 0


static int t, t1, t2, t3;
static float nPouso, nDecolag, somaPouso, somaDec;
static float combDisp, nPousaram, nDecolaram;
static int PDEmerg;

class Aviao
  {
  private:
    int emerg;
    bool PD; // P = 1; D = 0;
    int tempo;
    int espera;
    string aeroporto;
    string numero;

  public:
    Aviao *prox;

    Aviao () {};
    ~Aviao () {};
    // construtor da próxima unidade
    void alocaProx () {prox = new Aviao;} 
            
    void setEmerg (int e) {emerg = e;}
    void setPD (bool pd) {PD = pd;}
    void setTempo (int x) {tempo = x;}
    void setEspera (int esp) {espera = esp;}
    void setAeroporto (string aer) {aeroporto = aer;}
    void setNumero (string num) {numero = num;}
    void addPCombustivel () {combDisp += tempo - (t - espera);} 
    void addTPousaram () {somaPouso += t - espera;} 
    void addTDecolaram () {somaDec += t - espera;} 
    int tipoEmerg () {return emerg;}
    int tipoPD () {return PD;}

    void mostrarAviao ();
    int verificaAviao ();
    float somaEspera ();
  };

class Pista
  {
  private:
    int nEspera;
    int nEmerg;
    bool nImediato;
    string nome;

    Pista* comparaComb (Pista&, Pista&, Pista&);
    Pista* comparaEmerg (Pista&, Pista&, Pista&);
    Pista* comparaNormal (Pista&, Pista&, Pista&);

  public:
    Aviao *cabLista;
    Pista () {};
    ~Pista () {};

    void setNEspera (int n) {nEspera = n;}
    void setNEmerg (int em) {nEmerg = em;}
    void setNImed (bool im) {nImediato = im;}
    void setNome (string pista) {nome = pista;}

    Pista* comparaPistas (Pista&, Pista&, Pista&);
    void verificaPista (Pista&, Pista&, Pista&);
    void adicionar (Aviao*, int);
    void avioesContato ();
    void mostrarEspera ();
    bool remove1 ();
  };

void setValues (Aviao &avi, bool pd, int e, int x, int esp, string aer, string num);
void setPista (Pista &pista, int n, int em, bool im, string nome);

int Aviao::verificaAviao ()
{
  int maxEspera, tPassado;

  tPassado = t - espera;

  if (PD == DECOLAGEM) { 
    maxEspera = 0.1 * tempo; 
    if (tPassado >= maxEspera - 3) { // espera está no LIMIAR
      emerg = ESPERA;
      return ESPERA;
    }
  }
  else { // POUSO
    if (tempo - tPassado <= 3) {
      if (tempo - tPassado < 1) {
        emerg = IMEDIATO;
        return IMEDIATO;
      }
      else {
        emerg = COMBUSTIVEL;
        return COMBUSTIVEL;
      }
    }
  }
  return FALSE;
}

bool Pista::remove1 ()
{
  Aviao *plista, *paux;

  plista = cabLista;
  while (plista->prox != NULL)
    plista = plista->prox;
  plista = cabLista;

  if (plista->prox != NULL) {
    plista = plista->prox;

    if (plista->prox != NULL)
      paux = plista->prox;
    else
      paux = NULL;

    nEspera--;
    if (plista->tipoPD () == POUSO){
      nPouso--;
      plista->addPCombustivel ();
      plista->addTPousaram ();
      nPousaram++;
    }
    else{
      nDecolag--;
      nDecolaram++;
      plista->addTDecolaram () ;
    }

    if (nEmerg != 0){
      nEmerg--;
      if (plista->tipoEmerg () != FALSE || plista->tipoEmerg () != COMBUSTIVEL)
        PDEmerg++;
      if (nImediato == TRUE)
        nImediato == FALSE;
    }

    plista->mostrarAviao();
    delete plista;
    cabLista->prox = paux;
   
    return TRUE;
  }
  return FALSE;
}

void Pista::adicionar (Aviao *aviao, int emerg)
{
  Aviao *plista, *paux;

  plista = cabLista;
  paux = NULL;
  
  if (emerg == FALSE) {
    while (plista->prox != NULL)
      plista = plista->prox;

    plista->prox = aviao;
    aviao->prox = NULL;
    plista = plista->prox;

    nEspera++; 
    if (aviao->tipoPD () == POUSO)
      nPouso++;
    else
      nDecolag++;
  }
  else if (emerg == IMEDIATO) {
    if (plista->prox != NULL)
      paux = plista->prox;
    aviao->prox = paux;
    plista->prox = aviao;
    nImediato = TRUE;
    nEspera++;
    nEmerg++;
    if (aviao->tipoPD () == POUSO)
      nPouso++;
    else
      nDecolag++;
  }
  else { 
    for (int i = 0; i < nEmerg; i++) 
      plista = plista->prox;

    if (plista->prox != NULL)
      paux = plista->prox;

    aviao->prox = paux;
    plista->prox = aviao;
    plista = plista->prox;

    nEmerg++;
    nEspera++; 
    if (aviao->tipoPD () == POUSO)
      nPouso++;
    else
      nDecolag++;
  }
}

Pista* Pista::comparaComb (Pista &p1, Pista &p2, Pista &p3)
// função compara na ordem dada
{
  if (p1.nEmerg == 0)
    return &p1;
  else if (p2.nEmerg == 0)
    return &p2;
  else if (p3.nEmerg == 0)
    return &p3;
  else 
    return NULL;
}

Pista* Pista::comparaEmerg (Pista &p1, Pista &p2, Pista &p3)
// função compara na ordem dada
{
  Pista paux;
  paux.nEspera = 100;
  // o valor 100 é auxiliar para usar a função comparaNormal; basta um valor alto

  if (p1.nEmerg <= p2.nEmerg && p1.nEmerg <= p3.nEmerg){
    if (p1.nEmerg == p2.nEmerg)
      return comparaNormal (p1, paux, p2);
    else if (p1.nEmerg == p3.nEmerg)
      return comparaNormal (p1, paux, p3);
    else
      return &p1;
  }
  else if (p2.nEmerg <= p1.nEmerg && p2.nEmerg <= p3.nEmerg){
    if (p2.nEmerg == p1.nEmerg)
      return comparaNormal (p2, paux, p1);
    else if (p2.nEmerg == p3.nEmerg)
      return comparaNormal (p2, paux, p3);
    else 
      return &p2;
  }
  else if (p3.nEmerg <= p1.nEmerg && p3.nEmerg <= p2.nEmerg){
    if (p3.nEmerg == p1.nEmerg)
      return comparaNormal (p3, paux, p1);
    else if (p3.nEmerg == p2.nEmerg)
      return comparaNormal (p3, paux, p2);
    else 
      return &p3;
  }
  else
    return NULL;
}

Pista* Pista::comparaNormal (Pista &p1, Pista &p2, Pista &p3)
{
  if (p1.nEspera <= p2.nEspera && p1.nEspera <= p3.nEspera)
    return &p1;
  else if (p2.nEspera <= p1.nEspera && p2.nEspera <= p3.nEspera)
    return &p2;
  else if (p3.nEspera <= p1.nEspera && p3.nEspera <= p2.nEspera)
    return &p3;
  else
    cout << "Erro.\n";
}

Pista* Pista::comparaPistas (Pista &p1, Pista &p2, Pista &p3)
// pressupões que a lista de contato (Pista) não está vazia
{
  Aviao *plista;
  int criterio, PD;

  plista = cabLista->prox;
  criterio = plista->tipoEmerg ();
  PD = plista->tipoPD ();

  if (PD == DECOLAGEM) {
    if (criterio == COMBUSTIVEL) 
      return comparaComb (p3, p1, p2);
    else if (criterio != FALSE)
      return comparaEmerg (p3, p1, p2);
    else
      return comparaNormal (p3, p1, p2);
  }
  else { // PD == POUSO
    if (criterio == COMBUSTIVEL) 
      return comparaComb (p1, p2, p3);
    else if (criterio != FALSE)
      return comparaEmerg (p1, p2, p3);
    else
      return comparaNormal (p1, p2, p3);
  }
}

void Pista::verificaPista (Pista &p1, Pista &p2, Pista &p3)
{
  if (nEspera == 0)
    return;

  Aviao *plista, *avAux, cabAux;
  Pista *p, paux;
  int emerg = 0;

  plista = cabLista;
  paux.cabLista = &cabAux;

  for (int i = 0; i < nEmerg; i++) {
    avAux = plista;
    plista = plista->prox; 
    if (plista->tipoEmerg () == COMBUSTIVEL || (plista->tipoEmerg () == TRUE && plista->tipoPD () == POUSO) )
      if (plista->verificaAviao () == IMEDIATO) {
        plista->mostrarAviao();
        if (p1.nImediato == FALSE && t1 == 0) {
          nEmerg--;;
          nEspera--;
          avAux->prox = plista->prox;
          plista->prox = NULL;
          p1.adicionar (plista, IMEDIATO);
          plista = avAux;
        }
        else if (p2.nImediato == FALSE && t2 == 0) {
          nEmerg--;
          nEspera--;
          avAux->prox = plista->prox;
          plista->prox = NULL;
          p2.adicionar (plista, IMEDIATO);
          plista = avAux;
        }
        else if (p3.nImediato == FALSE && t3 == 0) {
          nEmerg--;
          nEspera--;
          avAux->prox = plista->prox;
          plista->prox = NULL;
          p3.adicionar (plista, IMEDIATO);
          plista = avAux;
        }
        else {
          //enviado para aeroporto vizinho
          nEspera--;
          nImediato == FALSE;
          nEmerg--;
          nPouso--;
          nPousaram++;
          avAux->prox = plista->prox;
          avAux = avAux->prox;
          delete plista;
          plista = avAux;
        }
      }
  }
  avAux = NULL;

  while (plista != NULL && plista->prox != NULL) {
    emerg = plista->prox->verificaAviao ();
    if (emerg != FALSE) {
      avAux = plista;
      plista = plista->prox;
      avAux->prox = plista->prox;
      if (plista->prox != NULL)
      avAux = avAux->prox;
      cabAux.prox = plista;
      p = paux.comparaPistas (p1, p2, p3);
      nEspera--;

      if (plista->tipoPD() == POUSO)
        nPouso--;
      else
        nDecolag--;

      if (p == NULL){
        // enviado para aeroporto vizinho
        delete plista;
        nPousaram++;
        plista = avAux;
      }
      else {
        p->adicionar (plista, emerg);
        plista = avAux;
      }
    }
    if ( plista == NULL || plista->prox == NULL)
      break;
    plista = plista->prox;
  }
}

void Pista::avioesContato ()
{
  Aviao *plista;
  bool pd;
  int e;
  float x;

  plista = new Aviao;
  cabLista = plista;

  string aeroportos [30] = {"BCN", "AMS", "BIO", "BLQ", "BOD", "BRU", 
                        "BSL", "CDG", "DUB", "FCO", "FRA", "GRX", 
                        "JFK", "LGW", "LPL", "LYS", "MAD", "MAH", 
                        "MLA", "MUC", "NTE", "ORY", "PMI", "RAK",
                        "SDR", "STN", "STR", "SXF", "VCE", "ZRH"};

  string nVoo [31] = {"VLG8990", "IBK5502", "VLG2973", "EZY8581", "IBE1745",
                  "RYR6986", "VLG2915", "NAX7025", "TAP1042", "VLG7333",
                  "VLG8240", "RYR9146", "DLH1133", "RYR0147", "VLG6523", 
                  "RYR1527", "VLG3910", "DLH1815", "VLG8025", "VLG8306",
                  "EZY4420", "VLG6248", "EZY1082", "VLG1867", "EZY4535",
                  "VLG3709", "VLG1591", "VLG1427", "VLG1315", "VLG8721",
                  "VLG6402"};

  //srand (time(NULL));
  nEspera = rand () % K;

  for (int i = 0; i < nEspera; i++) {
    plista->alocaProx ();
    plista = plista->prox;

    e = rand () % 100;
    if (e > EMERGENCIAS)
      e = 0;
    else
      e = 1;
    pd = rand () % 2;
    if (pd == 0) {
      x = rand () % C + 1;
      if (x == 1)
        e = COMBUSTIVEL;
      else if (x < 1)
        e = IMEDIATO;
    }
    else {
      x = rand () % V + 1;
      if (x < 10)
        e = ESPERA;
    }
    setValues (*plista, pd, e, x, t, aeroportos[rand () % 30], nVoo[rand () % 31]);
    // se f or P(0), aeroporto é referente à origem
    // se for P(1), aeroporto é referente ao destino

    if (e != FALSE)
      nEmerg++;
  }
  plista->prox = NULL; 
}

void Aviao::mostrarAviao ()
{
  cout << "\n  - Identificação do avião: " << numero << "\n";
  if (PD == POUSO)
    cout << "   Aeroporto de origem: " << aeroporto << "\n";
  else
    cout << "   Aeroporto de destino: " << aeroporto << "\n";

}

void Pista::mostrarEspera ()
{
  Aviao *plista;
  plista = cabLista;

  if (nEspera != 0){
    cout << "-------------------------------------------\n";
    cout << "            " << nome << "\n";
    for (int i = 0; i < nEspera; i++){
      plista = plista->prox;
      plista->mostrarAviao ();
    }
  }
}

float Aviao::somaEspera ()
{
  int combEspera = 0;
  Aviao *plista;

  if (prox != NULL){
    plista = prox;
    if (plista->PD == POUSO)
      combEspera += plista->tempo - (t - plista->espera);
    while (plista->prox != NULL){
      plista = plista->prox;
      if (plista->PD == POUSO)
        combEspera += plista->tempo - (t - plista->espera);
    }
  }
  return combEspera;
}

int main()
{
  Aviao *plista;
  Pista p1, p2, p3, pcontato;
  Pista* pEnvio;

  t1 = 0; t2 = 0; t3 = 0;
  nPouso = 0; nDecolag = 0;
  nPousaram = 0; nDecolaram = 0;
  somaPouso = 0; somaDec = 0;
  combDisp = 0; 

  setPista (p1, 0, 0, FALSE, "PISTA 1"); 
  setPista (p2, 0, 0, FALSE, "PISTA 2");
  setPista (p3, 0, 0, FALSE, "PISTA 3");
  setPista (pcontato, 0, 0, FALSE, "CONTATO");

  cout << "Bem Vindo à central do Aeroporto de Barcelona (PT)\n";
  
  for (t = 0; t < T; t++){

    cout << "\n\n> contagem do tempo <-> " << t << "\n ";

    //checagem dos aviões que já estão na fila
    p1.verificaPista (p1, p2, p3);
    p2.verificaPista (p1, p2, p3);
    p3.verificaPista (p1, p2, p3);

  
    // análise de aviões em contato
    pcontato.avioesContato();
    plista = pcontato.cabLista;

    while (plista->prox != NULL){
      pEnvio = pcontato.comparaPistas(p1, p2, p3);
      plista = plista->prox;
      pcontato.cabLista->prox = plista->prox;
      plista->prox = NULL;
      if (pEnvio == NULL){
        // enviado para aeroporto vizinho
        delete plista;
        nPousaram++;
      }
      else
        pEnvio->adicionar (plista, plista->tipoEmerg ());
      plista = pcontato.cabLista;
    }

    // liberação de aviões para pouso ou decolagem
    PDEmerg = 0;
    if (t1 == 0){
      if (p1.remove1 () == TRUE)
        t1 = 2;
    }
    else if (t1 > 0)
      t1--;
    if (t2 == 0){
      if (p2.remove1 () == TRUE)
        t2 = 2;
    }
    else if (t2 > 0)
      t2--;
    if (t3 == 0){
      if (p3.remove1 () == TRUE)
        t3 = 2;
    }
    else if (t3 > 0)
      t3--;

    // lista de aviões em espera
    cout << "- Aviões aguardando para pouso ou decolagem: \n";
    p1.mostrarEspera ();
    p2.mostrarEspera ();
    p3.mostrarEspera ();
    cout << "------------------------------------------- \n";


    // tempo médio de espera
    int tempoPouso = 0, tempoDecolag = 0;

    if (nPousaram == 0)
      cout << "- Nenhum avião pousou ainda. \n";
    else 
      cout << "- Tempo médio de espera para pouso: " 
          << somaPouso / nPousaram << "\n";

    if (nDecolaram == 0)
      cout << "- Nenhum avião decolou ainda. \n";
    else 
      cout << "- Tempo médio de espera para decolagem: " 
          << somaDec / nDecolaram << "\n";


    // quantidade média de combustível
    int combEspera = 0;
    if (nPouso == 0)
      cout << "- Nenhum avião esperando para pousar. \n";
    else {
      combEspera += p1.cabLista->somaEspera ();
      combEspera += p2.cabLista->somaEspera ();
      combEspera += p3.cabLista->somaEspera ();
      cout << "- Quantidade média de combustível dos aviões em espera para pousar: "
        << combEspera / nPouso << "\n";
    }
    if (nPousaram != 0)
      cout << "- Quantidade média de combustível dos aviões que já pousaram: "
        << combDisp / nPousaram << "\n";

    // quantidade de aviões pousando/decolando em emergência
    if (PDEmerg == 0)
      cout << "- Nenhum avião pousando ou decolando em emergência no momento. \n";
    else
      cout << "- Número de aviões pousando ou decolando em emergência: "
        << PDEmerg << "\n";
  }
  return 0;
}


void setValues (Aviao &avi, bool pd, int e, int x, int esp, string aer, string num)
{
  avi.setPD (pd); 
  avi.setEmerg (e);
  avi.setTempo (x);
  avi.setEspera (esp);
  avi.setAeroporto (aer);
  avi.setNumero (num);
}

void setPista (Pista &pista, int n, int em, bool im, string nome)
{
  Aviao *cab = new Aviao;
  pista.setNEspera (n);
  pista.setNome (nome);
  pista.setNImed (im);
  pista.setNEmerg (em);
  cab->prox = NULL;
  pista.cabLista = cab;

}