#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hangman.h"
 
int main () {
    srand(time(NULL));
    char secret[100];
    int result = get_word(secret);
    if (result != 0) {
        printf("Error");
        return 1;
    }
    printf("%s\n", secret);
 
    //printf("%d\n", is_word_guessed("secret", "aeiou"));
    // prints: 0
    //printf("%d\n", is_word_guessed("hello", "aeihoul"));
    // prints: 1
 
    char result3[30];
    get_guessed_word("container", "arpstxgoieyu", result3);
    // result = "_o_tai_er"
 
    // char result2[30] = "";
    // get_available_letters("", result2);
    // printf("%s\n", result2);
    // result = "bcdfhjklmnqvwz"
 
    hangman(secret);
    return 0;
}