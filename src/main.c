#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <Windows.h>
#include <time.h>
#include "giochi.h"
#include "utils.h"


#define NOME_CASINO "ItisBet"
#define VALUTA "Monete"

User utente;

void menuMain();

int main(void) {
	srand(time(NULL));
	SetConsoleOutputCP(CP_UTF8);
	while(true) {

		char usern[100+1] = "";
		int scelta = 0;
		printf("Cosa vuoi fare:\n");
		printf("0. Esci\n");
		printf("1. Registrati\n");
		printf("2. Login\n");
		printf("> ");
		scanf("%d", &scelta);

		switch(scelta) {
			case 0:
				system("cls");
				printf("Arrivederci...");
				Sleep(1000);
				return 0;
			case 1:
				system("cls");
				printf("Inserisci il tuo username: \n");
				printf("> ");
				scanf("%s", usern);
				scriviFile(usern);
				system("cls");
				printf("Registrazione effettuata con successo!\n");
				break;
			case 2:
				system("cls");
				printf("Inserisci il tuo username: \n");
				printf("> ");
				scanf("%s", usern);

				if(checkCredentials(&utente, usern)) {
					fflush(stdout);
					
					system("cls");
					menuMain();
				} else {
					system("cls");
					printf("Errore: username inesistente!\n");
					fflush(stdout);
				}
				break;
		}

	}

	return 0;
}

void menuMain() {
	while(true) {
		int scelta = 0;
	
		system("cls");
		printf("Benvenuto %s al %s\n", utente.username, NOME_CASINO);
		printf("Bilancio attuale: %d\n", utente.bilancio);
		printf("Fai una scelta:\n");
		printf("0. Esci\n");
		printf("1. Blackjack\n");
		printf("2. Roulette\n");
		printf("3. Craps\n");
		printf("4. Slots\n");
		printf("...Coming Soon...\n");
		printf("> ");
		scanf("%d", &scelta);

		switch(scelta) {
			case 0:
				system("cls");
				return;
			case 1:
				giocaBlackjack(&utente, VALUTA);
				break;
			case 2:
				giocaRoulette(&utente, VALUTA);
				break;
			case 3:
				giocaCraps(&utente, VALUTA);
				break;
			case 4:
				giocaSlots(&utente, VALUTA);
				break;
			default:
				system("cls");
				printf("Opzione invalida!\n");
				break;
		}
	}
}