#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define STR_SIZE 256

typedef struct player {
	char name[STR_SIZE];
	int jersey;
	float avgPPG;
	int gradYear;
	struct player* prev;
	struct player* next;
} player_t;

// a is the first struct, b is the second struct
void change(player_t* a, player_t* b) {
	player_t* aPrev = a->prev;
	player_t* bNext = b->next;

	b->next = a;
	b->prev = aPrev;
	if (bNext != NULL) {
		bNext->prev = a;
	}

	a->next = bNext;
	a->prev = b;
	if (aPrev != NULL) {
		aPrev->next = b;
	}
}

int main(int argc, char *argv[]) {
	// reading the file
	char fileName[STR_SIZE];
	strcpy(fileName, argv[1]);
	FILE* file = fopen(fileName, "rt");
	char line[STR_SIZE];
	char done[] = "DONE\n";

	// creating the structs
	player_t* nextPlayer = (player_t*) malloc(sizeof(player_t));
	int numberOfStructs = 1;
	nextPlayer->prev = NULL;
	fgets(line, sizeof(line), file);
	while (line != NULL) {
		// create struct
		line[strlen(line) - 1] = 0; strcpy(nextPlayer->name, line);
		fgets(line, sizeof(line), file); nextPlayer->jersey = atoi(line);
		fgets(line, sizeof(line), file); nextPlayer->avgPPG = atof(line);
		fgets(line, sizeof(line), file); nextPlayer->gradYear = atoi(line);

		nextPlayer->next = NULL;

		fgets(line, sizeof(line), file);
		if (strcmp(line, done) == 0) {
			break;
		}

		// next pointer
		player_t* tempPlayer = (player_t*) malloc(sizeof(player_t));
		nextPlayer->next = tempPlayer;
		// prev pointer
		tempPlayer->prev = nextPlayer;
		nextPlayer = nextPlayer->next;

		numberOfStructs++;
	}

	fclose(file);

	// sort the struct nodes using bubble sort
	player_t* head = nextPlayer;
	while (head->prev != NULL) {
		head = head->prev;
	}
	player_t* currPlayer = head;

	for (int i = 0; i < numberOfStructs; i++) {
		while (currPlayer->next != NULL) {
			// first PPG lower than second
			if (currPlayer->avgPPG < currPlayer->next->avgPPG) {
				change(currPlayer, currPlayer->next);
			}

			// same PPG: sort lexicographically
			else if (currPlayer->avgPPG == currPlayer->next->avgPPG) {
				if (strcmp(currPlayer->name, currPlayer->next->name) > 0) {
					change(currPlayer, currPlayer->next);
				}
				else {
					currPlayer = currPlayer->next;
				}
			}

			// first PPG higher than second
			else  {
				currPlayer = currPlayer->next;
			}
		}

		// Finding the real head
		player_t* head = currPlayer;
		while (head->prev != NULL) {
			head = head->prev;
		}
		currPlayer = head;
	}

	// Printing the values
	while (currPlayer->next != NULL) {
		printf("%s %d %d\n", currPlayer->name, currPlayer->jersey, currPlayer->gradYear);
		currPlayer = currPlayer->next;
		if (currPlayer->prev != NULL) {
			free(currPlayer->prev);
		}
	}
	printf("%s %d %d\n", currPlayer->name, currPlayer->jersey, currPlayer->gradYear);
	free(currPlayer);

	return 0;
}
