//
// Created by steve on 06.07.21.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct para_t{char *key; int value} para_t;

para_t imgPara[11] = {{"breite",0},{"hoehe",0},{"rotStart",0},
                     {"gruenStart",0},{"blauStart",0},{"rotZiel",0},
                     {"gruenZiel",0},{"blauZiel",0},{"rotStufe",0},
                      {"gruenStufe",0},{"blauStufe",0}};

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
    for (int i = 1; i < 9; ++i) {
        for (int j = 0; *(para[i] + j) != '\0'; ++j) {
            if (*(para[i] + j)<'0'||*(para[i] + j)>'9'){
                puts("Fehler: Die Helligkeit jeder Farbe und Groesse der Bildung soll eine Ziffer sein");
                exit(1);
            }
        }
    }
    for (int i = 0; i < 8; ++i) {
        char **endptr = NULL;
        imgPara[i].value = atoi(para[i + 1]);
        if (i>=2&&(imgPara[i].value<0||imgPara[i].value>255)){
            puts("Fehler: Die Helligkeit jeder Farbe soll zwischen 0 und 255 sein");
            exit(1);
        }
    }
    for (int i = 2; i < 5; ++i) {
        imgPara[i + 6].value = (imgPara[i + 3].value - imgPara[i].value) / imgPara[0].value;
    }
    name = para[9];
    int i;
    for (i = 0; *(name + i) != '\0'; ++i) {}
    i -= 4;
    if (*(name + i) != '.'||*(name + i + 1) != 'p' || *(name + i + 2) != 'p' || *(name + i + 3) != 'm'){
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
        int posion = i % imgPara[0].value;
        int rot = imgPara[2].value + posion * imgPara[8].value;
        int gruen = imgPara[3].value + posion * imgPara[9].value;
        int blau = imgPara[4].value + posion * imgPara[10].value;
        if(fprintf(target,"%d %d %d ", rot, gruen, blau) == 0){
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
    if (1 == argc || argc > 10){
        puts("Verwendung: ./a5_c <Breite> <Höhe> <Rotanteil Startfarbe> <Grünanteil Startfarbe> <Blauanteil Startfar-be> <Rotanteil Zielfarbe> <Grünanteil Zielfarbe> <Blauanteil Zielfarbe> <Dateiname>.ppm");
        return 0;
    }
    initPara(argv);
    FILE *target = openFile(name);
    writeFile(target);
    closeFile(target);
    return 0;
}
