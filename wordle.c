#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

char** loadDictionary(const char *filename, int *wordCount){
	FILE *file = fopen(filename, "r");
	if(file == NULL){
		printf("Error: Could not open dictionary file %s\n", filename);
		return NULL;
	}

	int capacity = 100;
	int count = 0;
	char **words = malloc(capacity * sizeof(char*));
	char buffer[32];

	while(fgets(buffer, sizeof(buffer), file) != NULL){
		buffer[strcspn(buffer, "\r\n")] = '\0';

		if(strlen(buffer) == 5){
			if(count >= capacity){
				capacity *= 2;
				char **temp = realloc(words, capacity * sizeof(char*));
				if(temp == NULL){
					fclose(file);
					return words;
				}
				words = temp;
			}
			words[count] = malloc(6 * sizeof(char));
			strcpy(words[count], buffer);
			count++;
		}
	}

	fclose(file);
	*wordCount = count;
	return words;
}


void evaluateGuess(const char *target, const char *guess){
	int state[5] = {0};
	int targetUsed[5] = {0};
	int guessUsed[5] = {0};

	for(int i = 0; i < 5; i++){
		if(guess[i] == target[i]){
			state[i] = 2;
			targetUsed[i] = 1;
			guessUsed[i] = 1;
		}
	}

	for(int i = 0; i < 5; i++){
		if(guessUsed[i]) continue;
		for(int j = 0; j < 5; j++){
			if(!targetUsed[j] && guess[i] == target[j]){
				state[i] = 1;
				targetUsed[j] = 1;
				break;
			}
		}
	}


	for(int i = 0; i < 5; i++){
		if(state[i] == 2){
			printf("\033[1;32m[%c]\033[0m", toupper(guess[i]));
		}else if (state[i] == 1){
			printf("\033[1;33m[%c]\033[0m", toupper(guess[i]));
		}else{
			printf("\033[1;30m[%c]\033[0m", toupper(guess[i]));
		}
	}
	printf("\n");
}

int main(void){
	int wordCount = 0;
	char **dictionary = loadDictionary("words.txt", &wordCount);

	if(dictionary == NULL || wordCount == 0){
		printf("Failed to load dictionary. Make sure 'words.txt' ecists!\n");
		return 1;
	}

	srand((unsigned int) time(NULL));
	char *target = dictionary[rand() % wordCount];

	printf("Welcome to Cordle!\n");
	printf("Guess the 5-letter word in 6 tries or less!\n\n");


	int attempts = 6;
	int won = 0;

	for(int turn = 1; turn <= attempts; turn++){
		char guess[32];
		printf("Attempt %d/%d - Enter guess: ", turn, attempts);

		if(scanf("%s", guess) != 1){
			printf("Input error.\n");
			break;
		}

		if(strlen(guess) != 5){
			printf("Error: Guess must be exactly 5 letters.\n");
			turn--;
			continue;
		}

		for(int i = 0; i < 5; i++){
			guess[i] = tolower(guess[i]);
		}

		evaluateGuess(target, guess);

		if(strcmp(target, guess) == 0){
			printf("\nCongratulations! You guessed the word: %s\n", target);
			won = 1;
			break;
		}
	}

	if(!won){
		printf("\nGame Over! The target word was: %s\n", target);
	}


	for(int i = 0; i < wordCount; i++){
		free(dictionary[i]);
	}
	free(dictionary);

	return 0;
}
