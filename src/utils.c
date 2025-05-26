#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <Windows.h>
#include <time.h>
#include "utils.h"

bool in_array(int numero, int array[], int size) {
	for(int i = 0; i < size; i++) {
		if(numero == array[i]) {
			return true;
		}
	}

	return false;
}

void scriviFile(char * nameScrivi) {
	FILE *fileCred = fopen("credentials.bin", "ab");

	if (!fileCred) {
		perror("Errore nell'aprire il file per la scrittura");
		return;
	}

	User utenteTemp;
	strncpy(utenteTemp.username, nameScrivi, 100);
	utenteTemp.username[100] = '\0'; // assicurati che sia terminato
	utenteTemp.bilancio = 5000;

	fwrite(&utenteTemp, sizeof(User), 1, fileCred); // 👈 scrivi l'intera struct

	fclose(fileCred);
}

bool checkCredentials(User *utente, char * nameCheck) {
	FILE * fileCred = fopen("credentials.bin", "rb");

	if(!fileCred) {
		perror("Errore file credenziali: ");
		return false;
	}
	
	User temp;
	while(fread(&temp, sizeof(User), 1, fileCred) == 1) {

		if(strncmp(temp.username, nameCheck, 100) == 0) {
			strcpy(utente->username, nameCheck);
			utente->bilancio = temp.bilancio;
			fclose(fileCred);
			return true;
		}
	}

	fclose(fileCred);
	return false;
}

void aggiornaBilancio(User *utente) {
	FILE *file = fopen("credentials.bin", "rb+");
	if (!file) {
		perror("Errore apertura file per aggiornare bilancio");
		return;
	}

	User temp;
	while (fread(&temp, sizeof(User), 1, file) == 1) {
		if (strncmp(temp.username, utente->username, 100) == 0) {
			// Torna indietro per riscrivere il bilancio
			fseek(file, -(long)sizeof(User), SEEK_CUR);
			// Aggiorna solo il bilancio, ma per sicurezza riscrivi l'intera struct
			temp.bilancio = utente->bilancio;
			fwrite(&temp, sizeof(User), 1, file);
			break;
		}
	}

	fclose(file);
}


int sommaArray(int array[], size_t size) {
	int somma = 0;
	for(size_t i = 0; i < size; i++) {
		somma += array[i];
	}

	return somma;
}