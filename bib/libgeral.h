#ifndef __LIBGERAL__
#define __LIBGERAL__

typedef struct {
    int codigo_ibge, capital, codigo_uf, siafi_id, ddd;
    double latitude, longitude; 
    char nome[50], fuso_horario[20];
} tmunicipio;

typedef struct {
    tmunicipio *vetor;
    int qtdElementos;
    int tamanho_max;
} thash;

int hash1(int chave, int seed, int tamanho_hash);
int hash2(int chave, int tamanho_hash);
int inserirHash(thash *hash, tmunicipio bucket);
int construirHash(thash *hash);
tmunicipio *buscarHash(thash hash, int chave);
void deletarHash(thash *hash);


typedef struct {
    int codigo_ibge;
    double latitude, longitude;
} telementoNo;

typedef struct _no {
    telementoNo elemento;
    struct _no *esq;
    struct _no *dir;
} tnode;

typedef struct {
    tnode *raiz;
} ttree;

typedef struct {
    int codigo_ibge;
    double distancia;
} tvizinho;

typedef struct {
    tvizinho *vizinhos;
    int tamanho_max;
    int qtdElementos;
} theap;

int inserirArvore(ttree *arvore, tnode **atual, telementoNo node, int nivel);
tvizinho vizinhosProximos(tnode **atual, tmunicipio *municipio, int nivel, theap *heap);
void construirArvore(ttree *arvore);


int inicializaHeap(theap *heap, int n);
tvizinho acessa_max(tvizinho vetor[]);
void altera_prioridade(tvizinho vetor[], theap heap, int n, tvizinho novoVizinho);
int insere_elemento(tvizinho vetor[], theap *heap, tvizinho novoVizinho);
void heap_sort(tvizinho vetor[], theap heap);

int lerArquivo(const char *caminhoArquivo, thash *hash, ttree *arvore);

#endif
