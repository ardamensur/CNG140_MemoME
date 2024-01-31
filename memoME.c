//Arda MENSUR
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void displayBoard(char** board, int size, int** opened);
int boardSize();
void initializeBoard(char** board, int size);
int validateCoordinates(int row1, int column1, int row2, int column2, int size, int** opened);
int checkMatch(int row1, int column1, int row2, int column2, char** board);

int main(){
    char quit;
    srand(time(NULL));
    do{
        printf("Welcome to MemoME!\n");


        int size = boardSize(); // Get the board size from the user

        char **board = (char **) malloc(size * sizeof(char *));
        for (int i = 0; i < size; i++) {
            board[i] = (char *) malloc(size * sizeof(char));
        }

        int **opened = (int **) malloc(size * sizeof(int *));
        for (int i = 0; i < size; i++) {
            opened[i] = (int *) malloc(size * sizeof(int));
            for (int j = 0; j < size; j++) {
                opened[i][j] = 0; // Initialize all doors as closed
            }
        }

        initializeBoard(board, size); // Generate game board
        printf("\nA board is created for you with the size of %dx%d!\n", size,size); // Display the initial board with closed doors

        int player1Score = 0;
        int player2Score = 0;
        int totalMatches = (size * size) / 2; // Calculate the total number of matches
        int currentPlayer = 1;
        int row1, column1, row2, column2;

        while (totalMatches > 0) {
            printf("\n--Player %d Turn:--\n", currentPlayer);
            displayBoard(board, size, opened); // Display the updated board
            do {
                printf("Enter the coordinates of doors to open:");
                scanf(" (%d,%d)", &row1, &column1);
                scanf(" (%d,%d)", &row2, &column2);

                if (!validateCoordinates(row1, column1, row2, column2, size, opened))
                    continue; // Repeat the input prompt if the coordinates are invalid or doors are already opened
                break;
            } while (1);

            opened[row1 - 1][column1 - 1] = 1; // Open the first coordinates
            opened[row2 - 1][column2 - 1] = 1; // Open the second coordinates
            displayBoard(board, size, opened); // Display the updated board
            if (checkMatch(row1, column1, row2, column2, board)) {
                if (currentPlayer == 1) {
                    player1Score += 2; // Increase player 1's score by 2 for a correct match
                    printf("Lucky you! Your score: 2,total score: %d\n", player1Score);
                } else {
                    player2Score += 2; // Increase player 2's score by 2 for a correct match
                    printf("Lucky you! Your score: 2,total score: %d\n", player2Score);
                }
                totalMatches--; // Decrease the total number of matches
            } else {
                if (currentPlayer == 1) {
                    player1Score -= 1; // Decrease player 1's score by 2 for a wrong match
                    printf("Unlucky! Your score: -1,total score: %d\n", player1Score);
                } else {
                    player2Score -= 1; // Decrease player 2's score by 2 for a wrong match
                    printf("Unlucky! Your score: -1,total score: %d\n", player2Score);
                }
                opened[row1 - 1][column1 - 1] = 0; // Close the first door
                opened[row2 - 1][column2 - 1] = 0; // Close the second door
            }

            if (currentPlayer == 1)
                currentPlayer = 2;
            else
                currentPlayer = 1;
        }

        if (player1Score > player2Score)
            printf("\n***Winner is Player1\n");
        else if (player2Score > player1Score)
            printf("\n***Winner is Player2\n");
        else
            printf("\n***Winner is friendship.The game ended in a draw\n");

        // Free memory
        for (int i = 0; i < size; i++) {
            free(board[i]);
            free(opened[i]);
        }

        free(board);
        free(opened);
        printf("\nWould you like to play again (Y/N)?");
        fflush(stdin);// to clear quit
        scanf("%c",&quit);
        printf("\n");
    }while(quit == 'Y'||quit == 'y');

    printf("Byee");
    return 0;
}

void displayBoard(char** board, int size, int** opened){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (opened[i][j] == 1)
                printf("%c ", board[i][j]); // If the door is opened, display the character at that position
            else
                printf("@ "); // If the door is closed, display '@'
        }
        printf("\n");
    }
}

int boardSize(){
    int boardsize;
    do {
        printf("Please specify the board size (2-30):");
        scanf("%d",&boardsize);
        if (boardsize>30 || boardsize<2)
            printf("Board size can only be between 2-30!\n");
        else{
            if (boardsize%2==1)
                printf("Board size can only be a multiple of two!\n");

        }
    }while (boardsize%2==1 || boardsize>30 || boardsize<2);
    return boardsize;
}

void initializeBoard(char** board, int size){
    int totalChars = (size * size) / 2;
    char characters[totalChars];

    // Generate random characters
    for (int i = 0; i < totalChars; i++){
        characters[i] = rand() % 31 + 33; // Randomly assign characters to the board
    }

    // Place characters on the board randomly
    int count = 0;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            board[i][j] = characters[count / 2]; // Assign characters to the board in pairs
            count++;
        }
    }
}

int validateCoordinates(int row1, int column1, int row2, int column2, int size, int** opened){
    if (row1 < 1 || row1 > size || column1 < 1 || column1 > size || row2 < 1 || row2 > size || column2 < 1 || column2 > size){
        printf("Sorry, wrong coordinates!\n"); // Check if the coordinates are within the board limits
        return 0;
    }
    else if (opened[row1 - 1][column1 - 1] == 1 || opened[row2 - 1][column2 - 1] == 1){
        printf("Coordinates (%d,%d) and (%d,%d) are already opened!\n", row1, column1, row2, column2); // Check if the doors at the given coordinates are already opened
        return 0;
    }
    else if (row1 == row2 && column1 == column2){
        printf("Sorry, two door coordinates are the same!\n"); // Check if the coordinates for the two doors are the same
        return 0;
    }
    else
        return 1; // If the coordinates are valid, return 1 (true)
}

int checkMatch(int row1, int column1, int row2, int column2, char** board){
    if (board[row1 - 1][column1 - 1] == board[row2 - 1][column2 - 1])
        return 1; // If the characters at the given coordinates match, return 1 (true)
    else
        return 0; // If the characters do not match, return 0 (false)
}