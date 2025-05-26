#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <Windows.h>
#include <time.h>
#include "giochi.h"
#include "utils.h"

void giocaRoulette(User *utente, char VALUTA[]) {
	while(true) {
		int vincita_prob, scommessa, scelta_scommessa = 0;
		int numero_s = -1;
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

		while(true) { // while sceltaScommessa
			printf("Su cosa vuoi scommettere?\n");
			printf("0. Numeri Rossi\n");
			printf("1. Numeri Neri\n");
			printf("2. Numeri pari\n");
			printf("3. Numeri dispari\n");
			printf("4. Numero singolo\n");

			int scelta = 0;
			scanf("%d", &scelta);
			scelta_scommessa = scelta;

			switch(scelta) {
				default:
					printf("Scelta non valida!\n");
					break;
				case 0:
				case 1:
				case 2:
				case 3:
					vincita_prob = scommessa;
					break;
				case 4:
					while(true) {
						printf("Scegli un numero [0-36]:\n");
						scanf("%d", &numero_s);

						if(numero_s < 0 || numero_s > 36) {
							system("cls");
							printf("Numero non valido!\n");
						} else {
							vincita_prob = scommessa*36;
							break;
						}
					}
					break;
			}
			break;
		}

		int numeri_rossi[] = {
			1, 3, 5, 7, 9, 12, 14, 16, 18,
			19, 21, 23, 25, 27, 30, 32, 34, 36
		};
		int numeri_neri[] = {
			2, 4, 6, 8, 10, 11, 13, 15, 17,
			20, 22, 24, 26, 28, 29, 31, 33, 35
		};

		int size = sizeof(numeri_neri) / sizeof(numeri_neri[0]);

		int numeroCasuale = rand() % 37;

		// spin

		printf("La roulette sta girando..\n");
		for(int i = 0; i < 20; i++) {
			int n = rand() % 37;
			printf("%d ", n);
			fflush(stdout);
			Sleep(100);
		}
		printf("\n");

		switch (scelta_scommessa) {
			case 0: // rossi
				if (in_array(numeroCasuale, numeri_rossi, size)) {
					utente->bilancio += vincita_prob;
					printf("Hai vinto %d %s! Ora hai %d %s\n", vincita_prob, VALUTA, utente->bilancio, VALUTA);
					aggiornaBilancio(utente);
				} else {
					printf("Hai perso! Era il numero %d\n", numeroCasuale);
					aggiornaBilancio(utente);
				}
				break;

			case 1: // neri
				if (in_array(numeroCasuale, numeri_neri, size)) {
					utente->bilancio += vincita_prob;
					printf("Hai vinto %d %s! Ora hai %d %s\n", vincita_prob, VALUTA, utente->bilancio, VALUTA);
					aggiornaBilancio(utente);
				} else {
					utente->bilancio -= scommessa;
					printf("Hai perso! Era il numero %d\n", numeroCasuale);
					aggiornaBilancio(utente);
				}
				break;

			case 2: // pari
				if (numeroCasuale != 0 && numeroCasuale % 2 == 0) {
					utente->bilancio += vincita_prob;
					printf("Hai vinto %d %s! Ora hai %d %s\n", vincita_prob, VALUTA, utente->bilancio, VALUTA);
					aggiornaBilancio(utente);
				} else {
					utente->bilancio -= scommessa;
					printf("Hai perso! Era il numero %d\n", numeroCasuale);
					aggiornaBilancio(utente);
				}
				break;

			case 3: // dispari
				if (numeroCasuale % 2 == 1) {
					utente->bilancio += vincita_prob;
					printf("Hai vinto %d %s! Ora hai %d %s\n", vincita_prob, VALUTA, utente->bilancio, VALUTA);
					aggiornaBilancio(utente);
				} else {
					utente->bilancio -= scommessa;
					printf("Hai perso! Era il numero %d\n", numeroCasuale);
					aggiornaBilancio(utente);
				}
				break;

			case 4: // numero_solo
				if (numeroCasuale == numero_s) {
					utente->bilancio += vincita_prob;
					printf("Hai indovinato il numero! Hai vinto %d %s! Ora hai %d %s\n", vincita_prob, VALUTA, utente->bilancio, VALUTA);
					aggiornaBilancio(utente);
				} else {
					utente->bilancio -= scommessa;
					printf("Hai perso! Il numero era %d\n", numeroCasuale);
					aggiornaBilancio(utente);
				}
				break;
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