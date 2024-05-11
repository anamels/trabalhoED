#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bib/libgeral.h"

int lerArquivo(const char *caminhoArquivo, thash *hash, ttree *arvore) {
    FILE* arquivo;
    arquivo = fopen(caminhoArquivo, "r");
    char linha[50];
    char atributos[][30] = {"codigo_ibge", "nome", "latitude",
                             "longitude", "capital", "codigo_uf",
                             "siafi_id", "ddd", "fuso_horario"};
    if(arquivo == NULL) {
        printf("Não foi possível abrir o arquivo\n");
        return EXIT_FAILURE;
    } else {
        tmunicipio municipio;
        telementoNo elemento;
        char fuso[30];

        while(fgets(linha, 50, arquivo) != NULL) {
            //le cada elemento da linha e guarda na minha cidade
            // (e no elemento no os necessarios)
            if(strstr(linha, atributos[0]) != NULL) {
                sscanf(linha, "%*s %d", &municipio.codigo_ibge);
                elemento.codigo_ibge = municipio.codigo_ibge;

            } else if(strstr(linha, atributos[1]) != NULL) {
                sscanf(linha, "%*s \"%[^\"]", municipio.nome);

            } else if(strstr(linha, atributos[2]) != NULL) {
                sscanf(linha, "%*s %lf", &municipio.latitude);
                elemento.latitude = municipio.latitude;

            } else if(strstr(linha, atributos[3]) != NULL) {
                sscanf(linha, "%*s %lf", &municipio.longitude);
                elemento.longitude = municipio.longitude;

            } else if(strstr(linha, atributos[4]) != NULL) {
                sscanf(linha, "%*s %d", &municipio.capital);

            } else if(strstr(linha, atributos[5]) != NULL) {
                sscanf(linha, "%*s %d", &municipio.codigo_uf);
                
            } else if(strstr(linha, atributos[6]) != NULL) {
                sscanf(linha, "%*s %d", &municipio.siafi_id);

            } else if(strstr(linha, atributos[7]) != NULL) {
                sscanf(linha, "%*s %d", &municipio.ddd);

            } else if(strstr(linha, atributos[8]) != NULL) {
                sscanf(linha, "%*s \"America\\%[^\"]", fuso);
                strcpy(municipio.fuso_horario, "America");
                strcat(municipio.fuso_horario, fuso);
                inserirHash(hash, municipio);
                inserirArvore(arvore, &arvore->raiz, elemento, 0);
            }
        }
    }

    fclose(arquivo);
    return EXIT_SUCCESS;
}
