#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <Windows.h>
#include <time.h>
#include "giochi.h"
#include "utils.h"

void giocaBlackjack(User *utente, char VALUTA[]) {
	while(true) {
		int scommessa = accettaScommessa(utente->bilancio, VALUTA);

		int carteBanco[20] = {0};
		int carteGiocatore[20] = {0};
		int lastPlayer = 0;

		// banco
		carteBanco[0] = (rand() % 11) + 1;
		carteBanco[1] = (rand() % 11) + 1;
		if (carteBanco[0] == 11 && carteBanco[1] == 11) {
			carteBanco[1] = 1;
		}
		int sommaBanco = carteBanco[0] + carteBanco[1];
		int lastBanco = 2;

		printf("Banco: [%d] [%d]\n", carteBanco[0], carteBanco[1]);

		// giocatore
		carteGiocatore[0] = (rand() % 11) + 1;
		carteGiocatore[1] = (rand() % 11) + 1;
		if (carteGiocatore[0] == 11 && carteGiocatore[1] == 11) {
			carteGiocatore[1] = 1;
		}
		lastPlayer = 2;
		int sommaPlayer = carteGiocatore[0] + carteGiocatore[1];

		printf("%s: [%d] [%d]\n", utente->username, carteGiocatore[0], carteGiocatore[1]);

		while(true) {
			printf("Vuoi pescare?\nS/N\n> ");
			char scelta = 0;
			scanf(" %c", &scelta);
			scelta = toupper(scelta);

			if(scelta == 'S') {
				system("cls");
				int nuovaCarta = (rand() % 11) + 1;
				carteGiocatore[lastPlayer] = nuovaCarta;
				sommaPlayer += nuovaCarta;
				lastPlayer++;

				printf("Banco: [%d] [%d]\n", carteBanco[0], carteBanco[1]);
				printf("%s:", utente->username);
				for(int i = 0; i < lastPlayer; i++) {
					printf(" [%d]", carteGiocatore[i]);
				}
				printf("\n");

				if(sommaPlayer > 21) {
					printf("Hai sballato!\n");
					break;
				}
			} else {
				break;
			}
		}

		system("cls");

		while(sommaBanco < 17) {
			int nuovaCarta = (rand() % 11) + 1;
			carteBanco[lastBanco] = nuovaCarta;
			sommaBanco += nuovaCarta;
			lastBanco++;
		}

		printf("Banco: ");
		for(int i = 0; i < lastBanco; i++) {
			printf("[%d] ", carteBanco[i]);
			Sleep(500);
		}
		printf("\n%s: ", utente->username);
		for(int i = 0; i < lastPlayer; i++) {
			printf("[%d] ", carteGiocatore[i]);
		}
		printf("\n");

		if(sommaPlayer > 21 || (sommaBanco <= 21 && sommaBanco > sommaPlayer)) {
			utente->bilancio -= scommessa;
			printf("\nHai perso %d %s!\nOra hai %d %s.\n", scommessa, VALUTA, utente->bilancio, VALUTA);
			aggiornaBilancio(utente);
		} else if(sommaBanco > 21 || sommaPlayer > sommaBanco) {
			utente->bilancio += scommessa;
			printf("Hai vinto %d %s!\nOra hai %d %s.\n", scommessa, VALUTA, utente->bilancio, VALUTA);
			aggiornaBilancio(utente);
		} else {
			printf("Pareggio!\nHai ancora %d %s.\n", utente->bilancio, VALUTA);
		}

		printf("\nVuoi giocare ancora?\nS/N\n> ");
		char pips;
		scanf(" %c", &pips);
		pips = toupper(pips);

		if(pips == 'N') break;
		system("cls");
	}

	system("cls");
}