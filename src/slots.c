#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <Windows.h>
#include <time.h>
#include "giochi.h"
#include "utils.h"

void giocaSlots(User *utente, char VALUTA[]) {
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
		char c1, c2, c3;
		int roll = (rand() % 10);
		
		printf("Combacia 2 o 3 lettere per vincere!\n");
		while(roll != 0) {
			c1 = 'A' + rand() % 27;
			c2 = 'A' + rand() % 27;
			c3 = 'A' + rand() % 27;

			printf("\r%c %c %c", c1, c2, c3); // \r scrive la linea da capo senza andare a capo

			Sleep(500);
			roll--;
		}
		if(c1 == '[' && c1 == c2 && c2 == c3) {
			utente->bilancio += 10*scommessa;
			aggiornaBilancio(utente);
			printf("JACKPOT!!!\n");
			printf("Hai vinto %d %s!\nOra hai %d %s.\n", scommessa, VALUTA, utente->bilancio, VALUTA);
			system("pause");
		} else if(c1 == c2 && c2 == c3) {
			utente->bilancio += 3*scommessa;
			aggiornaBilancio(utente);
			printf("Hai vinto %d %s!\nOra hai %d %s.\n", scommessa, VALUTA, utente->bilancio, VALUTA);
			system("pause");
		} else if(c1 == c2 || c2 == c3 || c1 == c3) {
			utente->bilancio += 2*scommessa;
			aggiornaBilancio(utente);
			printf("Hai vinto %d %s!\nOra hai %d %s.\n", scommessa, VALUTA, utente->bilancio, VALUTA);
			system("pause");
		} else {
			utente->bilancio -= scommessa;
			aggiornaBilancio(utente);
			printf("\nHai perso %d %s!\nOra hai %d %s.\n", scommessa, VALUTA, utente->bilancio, VALUTA);
			system("pause");
		}
	char pips;
	printf("Vuoi giocare ancora? [S/N]\n>");
	scanf(" %c", &pips);
	pips = toupper(pips);
	
	if(pips == 'N') return;
	}
}