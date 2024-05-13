#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "./bib/libgeral.h"

void menu()
{
    printf("Opções:\n1 - Buscar cidade\n2 - Buscar os N vizinhos mais próximos\n3 - Sair\n");
    printf("Insira a opção desejada: ");
}

void infoMuni(tmunicipio municipio) {
    printf("\nCódigo da cidade: %d\n", municipio.codigo_ibge);
    printf("Nome da cidade: %s\n", municipio.nome);
    printf("Latitude: %f\n", municipio.latitude);
    printf("Longitude: %f\n", municipio.longitude);

    if(municipio.capital == 0) {
        printf("Não é capital\n");
    } else {
        printf("É capital\n");
    }

    printf("Código UF: %d\n", municipio.codigo_uf);
    printf("ID SIAFI: %d\n", municipio.siafi_id);
    printf("DDD: %d\n", municipio.ddd);
    printf("Fuso horário: %s\n\n", municipio.fuso_horario);
}

int main() {
    int n, op = 0;
    int learq;
    int codigoIbge;

    thash hash;
    ttree arvore;
    theap heap;

    construirHash(&hash);
    construirArvore(&arvore);

    learq = lerArquivo("./data/municipios.json", &hash, &arvore);

    if (learq == EXIT_SUCCESS) {
        do {
            menu();
            scanf("%d", &op);

            switch (op) {
            case 1:

                do {
                    printf("Informe o código IBGE da cidade que deseja buscar: ");
                    scanf("%d", &codigoIbge);

                    if (codigoIbge <= 0) {
                        printf("Código inválido! Tente novamente.\n\n");
                    } else {
                        tmunicipio *municipio = buscarHash(hash, codigoIbge);

                        if(municipio == NULL) {
                            printf("Cidade não encontrada.\n\n");
                        } else {
                            infoMuni(*municipio);
                        }
                    }
                } while (codigoIbge <= 0);
                
                break;
            case 2:                
                do {
                    printf("Informe o código IBGE da cidade: ");
                    scanf("%d", &codigoIbge);

                    if (codigoIbge <= 0) {
                        printf("Código inválido! Tente novamente.\n\n");
                    } else {
                        tmunicipio *municipio = buscarHash(hash, codigoIbge);
                        
                        if(municipio == NULL) {
                            printf("Cidade não encontrada.\n\n");
                            codigoIbge = -1;
                        } else {
                            printf("Informe a quantidade de vizinhos que deseja buscar: ");
                            scanf("%d", &n);

                            if(n <= 0) {
                                printf("Quantidade inválida! Tente novamente.\n\n");
                                codigoIbge = -1;
                            } else {
                                inicializaHeap(&heap, n);
                            }

                            tvizinho vizinhoMaisProximo = vizinhosProximos(&arvore.raiz, municipio, 0, &heap);
                            heap_sort(heap.vizinhos, heap);
                            //ordena vizinhos mais prox

                            for(int i = 0; i < heap.qtdElementos; i++) {
                                tmunicipio *municipio = buscarHash(hash, heap.vizinhos[i].codigo_ibge);
                                infoMuni(*municipio);
                            }
                        }
                    }
                } while (codigoIbge <= 0);

                break;
            case 3:
                printf("Obrigada!\n");
                break;
            default:
                printf("Opção inválida!\n\n");
                break;
            }
        } while (op != 3);

        deletarHash(&hash);
        return EXIT_SUCCESS;
    } else {
        deletarHash(&hash);
        return EXIT_FAILURE;
    }
}
