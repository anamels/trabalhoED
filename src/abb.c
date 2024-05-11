#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "../bib/libgeral.h"

void construirArvore(ttree *arvore) {
    arvore->raiz = NULL;
}

int inserirArvore(ttree *arvore, tnode **atual, telementoNo no, int nivel) {
    if(*atual == NULL) {
        *atual = malloc(sizeof(tnode));
        (*atual)->elemento = no;
        (*atual)->esq = NULL;
        (*atual)->dir = NULL;

        return EXIT_SUCCESS;
    } else {
        int cmp;
        
        /*A KD-tree divide recursivamente o espaço de busca em regiões 
        menores, representadas por hiper-retângulos em dimensões maiores
        que 1. */

        if(nivel % 2) 
            cmp = (*atual)->elemento.longitude - no.longitude;
        else 
            cmp = (*atual)->elemento.latitude - no.latitude;

        // se a long/lat do no for maior do que o elemento, va para dir
        // else va para esq
        if(cmp < 0) {
            inserirArvore(arvore, &(*atual)->dir, no, ++nivel);
        } else {
            inserirArvore(arvore, &(*atual)->esq, no, ++nivel);
        }
    }

    return EXIT_FAILURE;
}

tvizinho comparaMinDistancia(tvizinho vizinho1, tvizinho vizinho2) {
    if(vizinho1.distancia < vizinho2.distancia)
        return vizinho1;

    return vizinho2;
}

tvizinho vizinhosProximos(tnode **atual, tmunicipio *municipio, int nivel, theap *heap) {
    float distancia; 
    tvizinho maisProximo;
    maisProximo.distancia = 999999999;

    if(*atual != NULL) {
        int cmp;
        
        //calcula dist euc entre o no atual e a cidade da busca
        distancia = sqrt(pow((*atual)->elemento.latitude - municipio->latitude, 2) + pow((*atual)->elemento.longitude - municipio->longitude, 2));

        //joga no maisProx se a distancia for menor (exceto ele mesmo)
        if(distancia < maisProximo.distancia && distancia > 0) {
            maisProximo.distancia = distancia;
            maisProximo.codigo_ibge = (*atual)->elemento.codigo_ibge;      

            // se a heap tiver espaço, insere maisProx
            // se nao, compara com o max: maisProx é menor? altera prioridade
            if(heap->qtdElementos < heap->tamanho_max) {
                insere_elemento(heap->vizinhos, heap, maisProximo);
            } else if(maisProximo.distancia < acessa_max(heap->vizinhos).distancia) {
                altera_prioridade(heap->vizinhos, *heap, 0, maisProximo);
            }  
        }
   
        // kdtree
        if(nivel % 2)
            cmp = (*atual)->elemento.longitude - municipio->longitude;
        else 
            cmp = (*atual)->elemento.latitude - municipio->latitude;
        
        // se o da cidade for maior que meu atual, puxa rec
        // com o filho da a direita e compara com o maisProx

        // se nao, puxa rec com o filho da esquerda
        if(cmp < 0) {
            maisProximo = comparaMinDistancia(maisProximo, vizinhosProximos(&(*atual)->dir, municipio, ++nivel, heap));
            
            //puxa outro caminho para nao seguir smp o mesmo
            if(maisProximo.distancia > cmp || heap->qtdElementos < heap->tamanho_max)
                maisProximo = comparaMinDistancia(maisProximo, vizinhosProximos(&(*atual)->esq, municipio, ++nivel, heap));
            
        } else {
            maisProximo = comparaMinDistancia(maisProximo, vizinhosProximos(&(*atual)->esq, municipio, ++nivel, heap));

            if(maisProximo.distancia > cmp || heap->qtdElementos < heap->tamanho_max)
                maisProximo = comparaMinDistancia(maisProximo, vizinhosProximos(&(*atual)->dir, municipio, ++nivel, heap));
        }
    }

    return maisProximo;
}
