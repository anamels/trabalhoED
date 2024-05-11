#include <stdio.h>
#include <stdlib.h>
#include "../bib/libgeral.h"
#define SEED 239
#define SIZE 10007
//n primo prox ao dobro de qtdElementos

int hashf_1(int chave, int seed, int tamanho_hash) {
    return (chave * seed) % tamanho_hash;
}
int hashf_2(int chave, int tamanho_hash) {
    return 1 + (chave % (--tamanho_hash));
}

int construirHash(thash *hash) {
    hash->vetor = (tmunicipio *) calloc(SIZE, sizeof(tmunicipio));
    if(hash->vetor == NULL) {
        return EXIT_FAILURE;
    }

    hash->qtdElementos = 0;
    hash->tamanho_max = SIZE;

    return EXIT_SUCCESS;
}

int inserirHash(thash *hash, tmunicipio bucket) {
    int posicao;
    int i = 0;

    while(hash->vetor[posicao].codigo_ibge != 0){
        int resultadoHash1 = hashf_1(bucket.codigo_ibge, SEED, hash->tamanho_max);
        int resultadoHash2 = hashf_2(bucket.codigo_ibge, hash->tamanho_max);
        posicao = (resultadoHash1 + i * resultadoHash2) % hash->tamanho_max;

        i++;
    }

    hash->vetor[posicao] = bucket;
    hash->qtdElementos += 1;

    return EXIT_SUCCESS;
}

tmunicipio *buscarHash(thash hash, int chave) {
    int posicao;
    int i = 0;

    while(hash.vetor[posicao].codigo_ibge != 0){
        int resultadoHash1 = hashf_1(chave, SEED, hash.tamanho_max);
        int resultadoHash2 = hashf_2(chave, hash.tamanho_max);
        posicao = (resultadoHash1 + i * resultadoHash2) % hash.tamanho_max;
    
        if(chave == hash.vetor[posicao].codigo_ibge)
            return &hash.vetor[posicao];

        i++;
    }

    return NULL;
}

void deletarHash(thash *hash) {
    free(hash->vetor);
}
