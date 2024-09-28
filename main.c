#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "utils.h"

void play_game(char dictionary[DICT_SIZE][WORD_SIZE + 1]) {
    char true_word[WORD_SIZE + 1];
    char guess[WORD_SIZE + 1];
    int attempts = 6;
    int idx;

    // Select a random word
    srand(time(NULL));
    idx = rand() % DICT_SIZE;
    snprintf(true_word, sizeof(true_word), "%s", dictionary[idx]);

    while (attempts > 0) {
        printf("Enter your guess (5 letters): ", "\t");
        printf("\n");
        fgets(guess, sizeof(guess), stdin);

        // Validate input: check length and validity
        guess[strcspn(guess, "\n")] = 0; // Remove newline character

        // Check if the guess is exactly 5 letters
        if (strlen(guess) != 5) {
            printf("Invalid input. Please enter exactly 5 letters.\n");
            continue;
        }

        // Check if all characters are letters
        int all_letters = 1; // Assume true until proven otherwise
        for (int i = 0; i < 5; i++) {
            if (!isalpha(guess[i])) {
                all_letters = 0;
                break;
            }
        }

        if (!all_letters) {
            printf("Invalid input. Please use letters only.\n");
            continue;
        }

        // Convert to lowercase for comparison
        for (int i = 0; i < 5; i++) {
            guess[i] = tolower(guess[i]);
        }

        // Check if the guess is in the dictionary
        int valid_guess = 0;
        for (int i = 0; i < DICT_SIZE; i++) {
            if (strcmp(guess, dictionary[i]) == 0) {
                valid_guess = 1;
                break;
            }
        }

        if (!valid_guess) {
            printf("Invalid word. Please try a word from the list.\n");
            continue;
        }

        // Process the guess and provide feedback
        char feedback[WORD_SIZE + 1] = "-----"; // Initialize with dashes
        int correct_letters[WORD_SIZE] = {0}; // Track correct letters in correct position

        // Check for correct letters in the correct position
        for (int i = 0; i < 5; i++) {
            if (guess[i] == true_word[i]) {
                feedback[i] = guess[i];
                correct_letters[i] = 1;
            }
        }

        // Check for letters in the word but in the wrong position
        for (int i = 0; i < 5; i++) {
            if (!correct_letters[i]) { // Only check incorrect positions
                for (int j = 0; j < 5; j++) {
                    if (guess[i] == true_word[j] && !correct_letters[j]) {
                        // Letter is in the word but not in the correct position
                        feedback[i] = '-'; // Keep dash for incorrect position
                        break;
                    }
                }
            }
        }

        // Print feedback
        printf("Feedback: %s\n", feedback);

        // Check if the guess matches the true word
        if (strcmp(guess, true_word) == 0) {
            printf("Congratulations! You've guessed the word: %s\n", true_word);
            return;
        }

        attempts--;
        printf("Attempts remaining: %d\n", attempts);
    }
    printf("Sorry, you've run out of attempts. The correct word was: %s\n", true_word);
}

int main() {
    char dictionary[DICT_SIZE][WORD_SIZE + 1];

    load_word_list(dictionary); // Load the word list
    play_game(dictionary);       // Start the game

    return 0;
}