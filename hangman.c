#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include "hangman.h"
 
int get_word(char secret[])
{
    // check if file exists first and is readable
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if (fp == NULL)
    {
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }
 
    // get the filesize first
    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;
 
    do
    {
        // generate random number between 0 and filesize
        long int random = (rand() % size) + 1;
        // seek to the random position of file
        fseek(fp, random, SEEK_SET);
        // get next word in row ;)
        int result = fscanf(fp, "%*s %20s", secret);
        if (result != EOF)
            break;
    } while (1);
 
    fclose(fp);
 
    return 0;
}
 
int is_word_guessed(const char secret[], const char letters_guessed[])
{
    int findFlag = 0;
    for (int i = 0; i < strlen(secret); i++)
    {
        findFlag = 0;
        for (int j = 0; j < strlen(letters_guessed); j++)
        {
            if (secret[i] == letters_guessed[j])
            {
                findFlag = 1;
                break;
            }
        }
        if (findFlag == 0)
        {
            return 0;
        }
    }
 
    return 1;
}
 
void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[])
{
    for (int i = 0; i < strlen(secret); i++)
    {
        guessed_word[i] = '_';
        for (int j = 0; j < strlen(letters_guessed); j++)
        {
            if (secret[i] == letters_guessed[j])
            {
                guessed_word[i] = letters_guessed[j];
            }
        }
    }
    guessed_word[strlen(secret)] = '\0';
}
 
void get_available_letters(const char letters_guessed[], char available_letters[])
{
    char alph[30] = "abcdefghijklmnopqrstuvwxyz";
    int a = 0;
    int findFlag = 0;
    for (int i = 0; i < strlen(alph); i++)
    {
        findFlag = 0;
        for (int j = 0; j < strlen(letters_guessed); j++)
        {
            if (letters_guessed[j] == alph[i])
            {
                findFlag = 1;
                break;
            }
        }
        if (findFlag == 0)
        {
            available_letters[a] = alph[i];
            a++;
        }
    }
    available_letters[a] = '\0';
}
 
bool char_in_string(const char string[], char symbol)
{
    for (int i = 0; i < strlen(string); i++) {
        if (symbol == string[i]) {
            return true;
        }
    }
    return false;
}
 
void hangman(const char secret[]) 
{
    int attempts = 8;
    int secretLength = strlen(secret);
    int letters_guessed_index = 0;
    char letters_guessed[100] = "";
    char available_letters[30] = "";
    char guessed_word[secretLength];
 
    printf("Welcome to the game, Hangman!\n");
    printf("I am thinking of a word that is %d letters long.\n", secretLength);
    while(1) {
        printf("\n-------------\n");
        if(attempts == 0){
            printf("Sorry, you ran out of guesses. The word was undeserved.\n");
            break;
        }
        printf("You have %d guesses left.\n", attempts);
        get_available_letters(letters_guessed, available_letters);
        printf("Available letters: %s\n", available_letters);
        printf("Please guess a letter: ");
        char tmpInput[30] = "";
        fgets(tmpInput, 30, stdin);
        if (strlen(tmpInput) - 1 == 1) {
            // this is a char
            if (tmpInput[0] >= 97 && tmpInput[0] <= 122) {
                if (char_in_string(letters_guessed, tmpInput[0])) {
                    printf("Oops! You've already guessed that letter: ");
                } else {
                    letters_guessed[letters_guessed_index] = tmpInput[0];
                    letters_guessed_index++;
                     if(is_word_guessed(secret, letters_guessed)){
                        printf("Congratulations, you won!\n");
                        break;
                    }
                    if (char_in_string(secret, tmpInput[0])) {
                        printf("Good guess: ");
                    } else {
                        attempts--;
                        printf("Oops! That letter is not in my word: ");
                    }
                }
            } else if (tmpInput[0] >= 65 && tmpInput[0] <= 90) {
                if (char_in_string(letters_guessed, tmpInput[0] + 32)) {
                    printf("Oops! You've already guessed that letter: ");
                } else {
                    letters_guessed[letters_guessed_index] = (int)tmpInput[0] + 32;
                    letters_guessed_index++;
                    if(is_word_guessed(secret, letters_guessed)){
                        printf("Congratulations, you won!\n");
                        break;
                    }
                    if (char_in_string(secret, (int)tmpInput[0] + 32)) {
                        printf("Good guess: ");
                    } else {
                        attempts--;
                        printf("Oops! That letter is not in my word: ");
                    }
                }
            } else {
                printf("Oops! '%c' is not a valid letter: ", tmpInput[0]);
            }
            get_guessed_word(secret, letters_guessed, guessed_word);
            for (int i = 0; i < strlen(guessed_word); i++) {
                printf("%c ", guessed_word[i]);
            }
        } else if(strlen(tmpInput) - 1 > 1) {
            // this is a string
            if (strlen(secret) == strlen(tmpInput) - 1) {
                int currectFlag = 1;
                for (int i = 0; i < strlen(secret); i++) {
                    if (secret[i] != tmpInput[i]) {
                        currectFlag = 0;
                        printf("Sorry, bad guess. The word was %s.\n", secret);
                        break;
                    }
                }
                if (currectFlag == 1) {
                    printf("Congratulations, you won!\n");
                }
            } else {
                printf("Sorry, bad guess. The word was %s.\n", secret);
            }
            break;
        }
    }
}