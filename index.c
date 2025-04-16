#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void scrambleWord(char *original, char *scrambled) {
    int length = strlen(original);
    int used[length];
    for (int i = 0; i < length; i++) {
        used[i] = 0;
    }

    srand(time(0)); 

    for (int i = 0; i < length; i++) {
        int randomIndex;
        do {
            randomIndex = rand() % length;
        } while (used[randomIndex]);

        scrambled[i] = original[randomIndex];
        used[randomIndex] = 1;
    }
    scrambled[length] = '\0'; 
}


void showHint(const char *word) {
    printf("Hint: The word starts with '%c' and ends with '%c'.\n", word[0], word[strlen(word) - 1]);
}

int main() {
    
    char playerName[50];
    int highScore = 0; // Track the highest score
    printf("Welcome to the Enhanced Word Scramble Game!\n");
    printf("Please enter your name: ");
    scanf("%s", playerName);
    printf("Hello, %s! Get ready for the challenge!\n\n", playerName);

   
    const char *easyWords[] = {"cat", "dog", "sun", "book", "pen"};
    const char *mediumWords[] = {"apple", "grape", "banana", "orange", "cherry"};
    const char *hardWords[] = {"elephant", "pineapple", "strawberry", "universe", "dictionary"};
    int easySize = 5, mediumSize = 5, hardSize = 5;

    
    int level = 1; // Start from level 1
    int score = 0;
    int attempts = 0;
    const char *chosenWord;
    char scrambledWord[100];
    char playerGuess[100];
    time_t start, end;

    while (level <= 3) {
        printf("Level %d: ", level);
        switch (level) {
            case 1:
                printf("Easy Words\n");
                chosenWord = easyWords[rand() % easySize];
                break;
            case 2:
                printf("Medium Words\n");
                chosenWord = mediumWords[rand() % mediumSize];
                break;
            case 3:
                printf("Hard Words\n");
                chosenWord = hardWords[rand() % hardSize];
                break;
        }

        // Scramble the word
        scrambleWord((char *)chosenWord, scrambledWord);

        // Start timer and display scrambled word
        time(&start); // Start timer
        printf("The scrambled word is: %s\n", scrambledWord);

        // Gameplay loop: Guess the word
        while (1) {
            printf("Guess the word (or type 'hint' for help): ");
            scanf("%s", playerGuess);

            if (strcmp(playerGuess, "hint") == 0) {
                showHint(chosenWord); // Provide a hint
                continue;
            }

            time(&end); // End timer
            double timeTaken = difftime(end, start); // Calculate time taken
            if (timeTaken > 15.0) { // 15-second time limit
                printf("Time's up! The correct word was: %s\n", chosenWord);
                break;
            }

            attempts++; // Count attempts
            if (strcmp(playerGuess, chosenWord) == 0) {
                printf("Correct! Great job, %s. You guessed it in %.1f seconds.\n", playerName, timeTaken);
                score++;
                break;
            } else {
                printf("Wrong! Try again.\n");
            }
        }

        // Progress to the next level
        if (level == 1 && score >= 2) {
            printf("\nCongratulations! You're advancing to Medium Level!\n");
            level++;
        } else if (level == 2 && score >= 4) {
            printf("\nAwesome! You're advancing to Hard Level!\n");
            level++;
        } else if (level == 3) {
            printf("\nYou've completed the final level!\n");
            break;
        }
    }

    // Update high score
    if (score > highScore) {
        highScore = score;
    }

    // End of game stats
    printf("\nGame Over, %s! Your total score: %d\n", playerName, score);
    printf("High Score: %d\n", highScore);
    printf("Total Attempts: %d\n", attempts);
    printf("Accuracy: %.2f%%\n", (double)score / attempts * 100);
    if (score >= 6) {
        printf("You're a Word Scramble Master!\n");
    } else {
        printf("Keep practicing! You'll improve in no time.\n");
    }

    return 0;
}