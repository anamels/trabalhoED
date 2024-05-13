#include <stdlib.h>
#include <stdio.h>
#include "../bib/libgeral.h"

void troca(tvizinho *a, tvizinho *b) {
    tvizinho aux = *a;
    *a = *b;
    *b = aux;
}

int pai(int no) {
    if(no == 0){
        return 0;
    } else {
        return (int) (no - 1) / 2;
    }
}

int esquerdo(int no) {
    return no * 2 + 1;
}

int direito(int no) {
    return no * 2 + 2;
}

int inicializaHeap(theap *heap, int no) {
    heap->vizinhos = (tvizinho *) malloc(sizeof(tvizinho) * no);

    if(heap->vizinhos == NULL) {
        return EXIT_FAILURE;
    }

    heap->qtdElementos = 0;
    heap->tamanho_max = no;
}

void desce(tvizinho vetor[], int no, theap heap) {
    int e = esquerdo(no);
    int d = direito(no);
    int maior = no;

    if(e < heap.qtdElementos && vetor[e].distancia > vetor[maior].distancia) {
        maior = e;
    }
    
    if(d < heap.qtdElementos && vetor[d].distancia > vetor[maior].distancia) {
        maior = d;
    }

    if(maior != no) {
        troca(&vetor[maior], &vetor[no]);
        desce(vetor, maior, heap);
    }
}

void constroi_heap(tvizinho vetor[], theap heap) {
    int p = pai(heap.qtdElementos - 1);

    while(p >= 0) {
        desce(vetor, p, heap);
        p--;
    }
}

void sobe(tvizinho vetor[], int no) {
    int p = pai(no);

    if(vetor[no].distancia > vetor[p].distancia) {
        troca(&vetor[p], &vetor[no]);
        sobe(vetor, p);
    }
}

tvizinho acessa_max(tvizinho vetor[]) {
    return vetor[0];
}

tvizinho extrai_max(tvizinho vetor[], theap *heap) {
    tvizinho max = vetor[0];
    heap->qtdElementos--;
    vetor[0] = vetor[heap->qtdElementos];

    desce(vetor, 0, *heap);
    return max;
}


void altera_prioridade(tvizinho vetor[], theap heap, int no, tvizinho novoVizinho) {
    if(vetor[no].distancia < novoVizinho.distancia) {
        vetor[no] = novoVizinho;
        sobe(vetor, no);
    } else {
        vetor[no] = novoVizinho;
        desce(vetor, no, heap);
    }
}

int insere_elemento(tvizinho vetor[], theap *heap, tvizinho novoVizinho) {
    if(heap->qtdElementos == heap->tamanho_max) {
        return EXIT_FAILURE;
    } else {
        vetor[heap->qtdElementos] = novoVizinho;
        heap->qtdElementos += 1;

        sobe(vetor, heap->qtdElementos - 1);
        return EXIT_SUCCESS;
    }
}

void heap_sort(tvizinho vetor[], theap heap) {
    constroi_heap(vetor, heap);

    while(heap.qtdElementos > 0) {
        heap.qtdElementos--;
        troca(&vetor[0], &vetor[heap.qtdElementos]);
        desce(vetor, 0, heap);
    }
}
