#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include "hangman.h"

int main () {
    srand(time(NULL));
    char secret[100];
    int result = get_word(secret);
    if (result !=0){
        printf("Error");
        return 1;
    }
    printf("%s",secret);

    printf("%d\n", is_word_guessed("secret", "aeiou"));
    // prints: 0
    printf("%d\n", is_word_guessed("hello", "aeihoul"));
    // prints: 1


    char result2[30];
    get_guessed_word("container", "arpstxgoieyu", result2);
    printf("%s",result2);
    // result = "_o_tai_er"

    
    return 0;
}