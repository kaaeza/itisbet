#ifndef UTILS_H
#define UTILS_H
typedef struct {
	char username[100+1];
	int bilancio;
} User;

bool in_array(int numero, int array[], int size);
void scriviFile(char * nameScrivi);
bool checkCredentials(User *utente, char *nameCheck);
int sommaArray(int array[], size_t size);
void aggiornaBilancio(User *utente);
int accettaScommessa(int max, char VALUTA[]);

#endif