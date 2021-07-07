// Das Ergebnis von ./bs5 beispiel1.ppm "Dateigroesse: 35 bytes" sonder 34 bytes, da EOF auch ein byte besitzt.
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int breite;
int hoehe;
long dateigroesse;

FILE *openFile(char *path){
    FILE *target;
    if ((target = fopen(path,"r")) == NULL){
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

long calculateFileSize(FILE *target){
    FILE *savePos = target;
    long sizeOfFile;
    if (fseek(target, 0L, SEEK_END)){
        exit(errno);
    }
    sizeOfFile = ftell(target);
    target = savePos;
    return sizeOfFile;
}

void getFileInfo(FILE *target){
    if (fscanf(target, "P3%d%d", &breite, &hoehe) == 0){
        puts("Fehler: Das Format dieser Datei ist falsch");
        exit(1);
    }
    dateigroesse = calculateFileSize(target);
}

int main(int argc, char *argv[])
{
    if (1 == argc || argc > 2){
        puts("Verwendung: a5_a <Dateipfad>");
        return 0;
    }
    FILE *target = openFile(argv[1]);
    getFileInfo(target);
    closeFile(target);
	printf("Breite: %d \nHoehe: %d \nDateigroesse: %ld bytes\n",
		breite, hoehe, dateigroesse);
	return 0;
}
