#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <Windows.h>
#include <time.h>
#include "giochi.h"
#include "utils.h"

void giocaCraps(User *utente, char VALUTA[]) {
	while(true) {
		int scommessa = 0;
		while(true) { // while scommessa
			system("cls");
			printf("Hai %d %s\n", utente->bilancio, VALUTA);
			printf("Quanto scommetti:\n> ");
			scanf("%d", &scommessa);

			if(scommessa > utente->bilancio) {
				system("cls");
				printf("Scommessa troppo alta!\nHai massimo %d %s.\n", utente->bilancio, VALUTA);
			} else {
				break;
			}
		}
		system("cls");
		int punto = 0;

		int dado1 = (rand() % 6) + 1;
		int dado2 = (rand() % 6) + 1;
		int somma = dado1 + dado2;

		printf("Rollando i dadi.");
		Sleep(500);
		printf(".");
		Sleep(500);
		printf(".\n");
		system("cls");

		printf("Dadi: [%d] [%d]\nSomma: %d\n", dado1, dado2, somma);

		if(somma == 2 || somma == 3 || somma == 12) {
			printf("Hai perso!");
			utente->bilancio -= scommessa;
			aggiornaBilancio(utente);
			return;
		} else if(somma == 7 || somma == 11) {
			utente->bilancio += 5*scommessa;
			printf("Hai vinto %d %s!\nOra hai %d %s.\n", 5*scommessa, VALUTA, utente->bilancio, VALUTA);
			aggiornaBilancio(utente);
			return;
		} else {
			punto = somma;
			printf("Punto! [%d]\n", punto);

			while(true) {
				printf("Premi invio per tirare i dadi...");
				getchar(); // per leggere il newline rimasto da scanf
				getchar();

				dado1 = (rand() % 6) + 1;
				dado2 = (rand() % 6) + 1;
				somma = dado1 + dado2;

				printf("Hai tirato: [%d] + [%d] = %d\n", dado1, dado2, somma);

				if(somma == punto) {
					// Vince
					utente->bilancio += scommessa;
					printf("Punto! Hai vinto %d %s!\nOra hai %d %s.\n", scommessa, VALUTA, utente->bilancio, VALUTA);
					aggiornaBilancio(utente);
					return;
				} else if(somma == 7) {
					// Perde
					utente->bilancio -= scommessa;
					printf("Hai perso!\nOra hai %d %s.\n", utente->bilancio, VALUTA);
					aggiornaBilancio(utente);
					return;
				} else {
					printf("Rilancio...\n");
				}
			}
		}

	}
}
