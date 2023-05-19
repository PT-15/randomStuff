#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ever (;;)

void newCode(int repeat, int n, char *code, int *used)
{
    srand(time(NULL));
    for (int i = 0; i < n;){
        int codeDigit = rand() % 10;
        if (repeat || !used[codeDigit]){
            used[codeDigit]++;
            code[i] = codeDigit + '0';
            i++;
        }
    }
    //REMOVE
    /*for (int i = 0; i < 10; i++){
        printf("%d: %d\n", i, used[i]);
    }*/
    //printf("%s", code);
    //printf("\n");
    //END REMOVE
}

void instructions(int n, int tries)
{
    printf("\nThe program has generated a random number code of size %d. The goal of the game is for you to guess it.", n);
    printf("\nEnter a %d number code (without spaces between the numbers)\n", n);
    printf("P is the number of digits that exist in the code in the same position\n");
    printf("C is the number of digits that exist in the code but are in a different position\n");
    printf("If you want a summary of all your guesses input \"g\"\n");
    printf("To see this instructions again input \"h\"\n");
    printf("You have %d tries. Good luck!\n", tries);
}

void showGuesses(int n, char guesses[][n+2], int guessNum){
    printf("\n");
    if (!guessNum){
        printf("You haven't guessed anything yet");
        return;
    }
    for (int i = 1; i < guessNum+1; i++){
        for (int j = 0; j < n; j++){
            printf("%c", guesses[i][j]);
        }
        printf("\tP = %c C = %c\n", guesses[i][n], guesses[i][n+1]);
    }
}

int checkGuess(int n, char *code, char *guess, int *used, char *checks){
    checks[0] = '0';
    checks[1] = '0';
    int appeared[10] = {0};
    for (int i = 0; i < n; i++){
        if (guess[i] == code[i]){
            appeared[guess[i] - '0']++;
            checks[0]++;
        }
        else if (used[guess[i] - '0'] && (used[guess[i] - '0'] > appeared[guess[i] - '0'])){
            checks[1]++;
            appeared[guess[i] - '0']++;
        }
    }
    if (checks[0] == n + '0'){
        printf("\nYou have done well. Here, have a cookie.\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⡀\n⠀⠀⠀⠀⠀⠀⠀⣀⡠⠾⠭⠀⠉⠓⠀⠤⢤⠖⠂⠤⡀\n⠀⢀⡤⠐⠒⡚⢩⡂⠉⠉⣲⠀⠀⣀⠤⠤⢄⡑⠂⠀⣘⣤⣄\n⢀⡯⠤⠐⠊⠁⠀⠚⠭⠉⠀⠀⠈⠣⢄⣀⣠⠵⠤⠼⣄⣀⠉⢻⣆\n⠘⠀⡄⠒⠒⡢⠀⠀⡀⠤⠤⢄⠀⠀⠀⢀⠥⠤⢄⡀⠈⠂⠉⣁⢸\n⠘⣄⠈⠉⠉⠀⠙⠂⠓⠤⡄⠄⠃⣀⣀⠑⠀⠤⠤⠝⠀⣔⡡⣴⠋\n⠀⠈⠑⠢⠤⣄⣀⣀⣀⣀⣀⣀⣀⣑⣀⣁⣀⣀⣀⡤⠤⠐⠋\n");
        return 1;
    }
    printf("P = %c\nC = %c\n", checks[0], checks[1]);
    return 0;
}

void replay(){
    for ever {
        printf("\nPlay again? (y/n): ");
        char ans[10];
        scanf("%s", ans);
        if (!strcmp(ans, "n")){
            exit(0);
        }
        else if (!strcmp(ans, "y")){
            return;
        }
    }
}

void guessNum(int n, char *code, int *used, int tries)
{
    int guessed = 0;
    int guessNum = 0;
    char guesses[tries][n+2];
    for ever {
        if (guessNum == tries){
            printf("\nYou run out of tries. Better luck next time\n");
            printf("The code was ");
            //for (int i = 0; i < n; i++){
                printf("%s", code);
            //}
            replay();
            //printf("\n");
            return;
        }
        printf("\n> ");
        char guess[n];
        scanf("%s", guess);
        if (guess[0] == 'g'){
            showGuesses(n, guesses, guessNum);
            printf("\nYou have %d tries left\n", tries - guessNum);
        }
        else if (guess[0] == 'h'){
            instructions(n, tries);
        }
        else {
            int isCorrectGuess = 1;
            for (int i = 0; i < n; i++){
                if (guess[i] < '0' || guess[i] > '9'){
                    isCorrectGuess = 0;
                    break;
                }
            }
            if (isCorrectGuess){
                char checks[2];
                guessed = checkGuess(n, code, guess, used, checks);
                if (guessed){
                    replay();
                    return;
                }
                guessNum++;
                for (int i = 0; i < n; i++){
                    guesses[guessNum][i] = guess[i];
                }
                guesses[guessNum][n] = checks[0];
                guesses[guessNum][n+1] = checks[1];
            }
            else {
                printf("Error. Remember to not leave spaces between the digits\n");
            }
        }
    }
}

int main()
{
    int tries = 0;
    int repeat = 0;
    int n = 0;
    int baseCase[2] = {4, 10}; //code length - number of tries

    for ever {
        printf("\nChoose game mode:\n\t0. Numbers do not repeat\n\t1. Numbers can repeat\nPress 3 to exit\n\n> ");
        scanf("%d", &repeat);
        if (repeat != 0 && repeat != 1 && repeat != 3){
            continue;
        }
        if (repeat == 3){
            break;;
        }
        printf("Choose number quantity: ");
        scanf("%d", &n);
	    if (n < 2) continue;
        if (!repeat && n > 9){
            n = 9;
        }

        tries = (n * baseCase[1]) / baseCase[0];

        char code[n];
        int used[10] = {0};

        instructions(n, tries);

        newCode(repeat, n, code, used);

        guessNum(n, code, used, tries);
    }

    return 0;
}
