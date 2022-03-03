// libraries for i/o, boolean types, strlen and toupper/tolower, as well as custom String type
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
typedef char *String;

// function prototypes
void askForWord ();
void step ();
void printGuessedWord ();
void printLives ();
bool stringContains (String str, char letter);
void toLowerString (String str);
void toUpperString (String str);

// global vars
char word[64];
int lives = 8;

bool guessed[64];
int guessedCount = 0;

char guesses[128];
int guessesCount = 0;

bool end = false;


int main () {
    // ask for the word to be guessed and print "_"s
    askForWord();
    printGuessedWord();

    // game loop
    while (!end) {
        step();

        // on win or lose

        if(lives == 0) {
            toUpperString(word);
            printf("\n\nYou lost! \nThe correct word was: %s", word);
            end = true;
        }

        if(guessedCount >= strlen(word)) {
            toUpperString(word);
            printf("\n\nYou won! \nThe correct word was %s, congrats!", word);
            end = true;
        }
    }

    scanf(" %c");
    return 0;
}

void askForWord () {
    printf("Enter a Word: ");
    scanf("%[^\n]s", word);
    toLowerString(word);
}

void step () {
    // ask user to enter a letter
    char letter;
    printf("\nEnter a Letter: ");
    scanf(" %c", &letter);
    printf("\n");

    // if already guessed
    if (stringContains(guesses, letter)) {
        printf("The Letter %c was already guessed!", toupper(letter));
        return;
    
    // if the guess is correct
    } else if (stringContains(word, letter)) {
        printf("Correct! \n");

        for(int i = 0; i < strlen(word); i++) {
            if (word[i] == letter) {
                guessed[i] = true;
                guessedCount++;
            }
        }

    // if incorrect
    } else {
        printf("Incorrect! \n");
        lives--;
        printLives();
    }

    // add letter to guesses
    guesses[guessesCount] = letter;
    guessesCount++;

    // print guessed letters or "_"s
    printGuessedWord();
}

// for printins guessed letters or "_"s
void printGuessedWord () {
    for(int i = 0; i < strlen(word); i++){
        if(guessed[i]) printf("%c ", toupper(word[i]));
        else printf("_ ");
    }
}

// print how many lives user has left
void printLives () {
    printf("You have %i lives left\n", lives);
}


// helper functions

bool stringContains (String str, char letter) {
    for(int i = 0; i < strlen(str); i++) {
        if (str[i] == letter) return true;
    }
    return false;
}

void toLowerString (String str) {
    for(int i = 0; i < strlen(str); i++){
        str[i] = tolower(str[i]);
    }
}

void toUpperString (String str) {
    for(int i = 0; i < strlen(str); i++){
        str[i] = toupper(str[i]);
    }
}