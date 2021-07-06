//
// Created by steve on 06.07.21.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct para_t{char *key; int value} para_t;

para_t imgPara[5] = {{"breite",0},{"hoehe",0},{"rotKomp",0},
                              {"gruenKomp",0},{"blauKomp",0}};

char *name;

FILE *openFile(char *path){
    FILE *target;
    if ((target = fopen(path,"w+")) == NULL){
        printf("Fehler: Datei \"%s\" ist nicht geoeffnet\n", path);
        exit(1);
    }
    return target;
}

void closeFile(FILE *target){
    if (fclose(target)){
        puts("Datei kann nicht gescvhlossen werden");
        exit(1);
    }
}

void initPara (char *para[]){
    for (int i = 1; i < 6; ++i) {
        for (int j = 0; *(para[i] + j) != '\0'; ++j) {
            if (*(para[i] + j)<'0'||*(para[i] + j)>'9'){
                puts("Fehler: Die Helligkeit jeder Farbe und Groesse der Bildung soll eine Ziffer sein");
                exit(1);
            }
        }
    }
    for (int i = 0; i < 5; ++i) {
        char **endptr = NULL;
        imgPara[i].value = atoi(para[i + 1]);
        if (i>=2&&(imgPara[i].value<0||imgPara[i].value>255)){
            puts("Fehler: Die Helligkeit jeder Farbe soll zwischen 0 und 255 sein");
            exit(1);
        }
    }
    name = para[6];
    int i;
    for (i = 0; *(para[6] + i) != '\0'; ++i) {}
    i -= 4;
    if (*(para[6] + i) != '.'||*(para[6] + i + 1) != 'p' || *(para[6] + i + 2) != 'p' || *(para[6] + i + 3) != 'm'){
        puts("Fehler: Die Dateinameerweitung soll \".ppm\" sein");
        exit(1);
    }
}

void writeFile(FILE *target){
    if(fprintf(target,"P3 %d %d 255 ", imgPara[0].value, imgPara[1].value) == 0){
        puts("Fehler: Datei kann nicht gespeichert werden1");
        exit(1);
    }
    for (int i = 0; i < imgPara[0].value * imgPara[1].value; ++i) {
        if(fprintf(target,"%d %d %d ", imgPara[2].value, imgPara[3].value, imgPara[4].value) == 0){
            puts("Fehler: Datei kann nicht gespeichert werden");
            exit(1);
        }
        if (9 == i % imgPara[0].value){
            if(fprintf(target,"\n") == 0){
                puts("Fehler: Datei kann nicht gespeichert werden");
                exit(1);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (1 == argc || argc > 7){
        puts("Verwendung: ./a5_b <Breite> <Höhe> <Farbkomponente rot> <Farbkomponente grün> <Farbkomponenteblau> <Dateiname>.ppm");
        return 0;
    }
    initPara(argv);
    FILE *target = openFile(name);
    writeFile(target);
    closeFile(target);
    return 0;
}
