#include <stdio.h>
#include <string.h>


/***************************
******** Menu Items ********
****************************/

#define REVERSE 1
#define PALINDROME 2
#define SENTENCES 3
#define ZIP 4
#define SUDOKU 5
#define EXIT 6


/***************************
*** DIMENSION PARAMETERS ***
****************************/

#define LONGEST_TERM 20
#define LONGEST_SENTENCE 62
#define MAX_NUMBER_OF_TERMS 10

#define ZIP_MAX_GRID_SIZE 20

#define SUDOKU_GRID_SIZE 9
#define SUDOKU_SUBGRID_SIZE 3

/***************************
*** DEFINED CONSTANTS ***
****************************/

#define SMALLEST_NUMBER_ZIP 1
#define VISITED -2

#define EMPTY_CELL 0
#define SMALLEST_NUMBER_SUDOKU 1

/***************************
* USER INTEFACE PROTOTYPES *
****************************/

void task1ReversePhrase();
void task2CheckPalindrome();
void task3GenerateSentences();
void task4SolveZipBoard();
void task5SolveSudoku();


/****************************
* IMPLEMENTATION PROTOTYPES *
*****************************/

void task1ReversePhraseImplementation();
int task2CheckPalindromeImplementation(int);
void task3GenerateSentencesImplementation(char[][LONGEST_TERM+1], int, char[][LONGEST_TERM+1], int,
                                            char[][LONGEST_TERM+1], int);
int task4SolveZipBoardImplementation(int[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                        char[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE], int, int, int, int);
int task5SolveSudokuImplementation(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE]);


/******************************
* HELPER FUNCTIONS PROTOTYPES *
*******************************/

int readTerms(char[][LONGEST_TERM+1], int, char[]);
int task3HelperNumOfTerms(int, char[][LONGEST_TERM+1]);
int task4HelperHighestInBoard(int[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE], int, int, int, int);
int task4HelperAllTilesVisited(int[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE], int, int, int, int);
void printSudoku(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE]);
int task5HelperSudokuSolver(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int, int, int, int);
int task5HelperCheckRow(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int, int, int, int);
int task5HelperCheckCol(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int, int, int, int);
int task5HelperCheckBox(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int, int, int, int);
int task5HelperSetRowCol(int);

/******************************
********** MAIN MENU **********
*******************************/

int main()
{
    int task;
    do
    {
        printf("Please choose a task (1-5) or 6 to exit:\n");
        printf("%d. Reverse a phrase\n", REVERSE);
        printf("%d. Check Palindrome\n", PALINDROME);
        printf("%d. Generate sentences\n", SENTENCES);
        printf("%d. Solve Zip Board\n", ZIP);
        printf("%d. Solve Sudoku\n", SUDOKU);
        printf("%d. Exit\n", EXIT);

        scanf(" %d", &task);
        scanf("%*c");
        switch (task)
        {
        case REVERSE:
            task1ReversePhrase();
            break;
        case PALINDROME:
            task2CheckPalindrome();
            break;
        case SENTENCES:
            task3GenerateSentences();
            break;
        case ZIP:
            task4SolveZipBoard();
            break;
        case SUDOKU:
            task5SolveSudoku();
            break;
        case EXIT:
            printf("Goodbye!\n");
            break;
        default:
            printf("Please choose a task number from the list.\n");
            break;
        }
        printf("\n=============================\n\n");
    } while (task != EXIT);

    return 0;
}


/***************************
****** USER INTERFACE ******
****************************/


void task1ReversePhrase()
{
    printf("Please insert the phrase to reverse:\n");
    task1ReversePhraseImplementation();
    printf("\n");
}


void task2CheckPalindrome()
{
    printf("Please insert the phrase length:\n");
    int n;
    scanf("%d", &n);
    printf("Please insert the phrase to check:\n");
    scanf(" ");
    if (task2CheckPalindromeImplementation(n))
        printf("The phrase is a palindrome.\n");
    else
        printf("The phrase is not a palindrome.\n");
}


void task3GenerateSentences()
{
    char subjects[MAX_NUMBER_OF_TERMS][LONGEST_TERM+1];
    char verbs[MAX_NUMBER_OF_TERMS][LONGEST_TERM+1];
    char objects[MAX_NUMBER_OF_TERMS][LONGEST_TERM+1];
    int subjectsCount, verbsCount, objectsCount;

    subjectsCount=readTerms(subjects, MAX_NUMBER_OF_TERMS, "subjects");
    verbsCount=readTerms(verbs, MAX_NUMBER_OF_TERMS, "verbs");
    objectsCount=readTerms(objects, MAX_NUMBER_OF_TERMS, "objects");
    printf("List of Sentences:\n");
    task3GenerateSentencesImplementation(subjects, subjectsCount, verbs, verbsCount, objects, objectsCount);
}


void task4SolveZipBoard()
{
    int size;
    int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE] = {0};
    char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE] = {0};
    int row, col;
    int highest=0;
    printf("Please enter the board size:\n");
    scanf("%d", &size);
    if (size < 1 || size > ZIP_MAX_GRID_SIZE)
    {
        printf("Invalid board size.\n");
        return;
    }

    printf("Please enter the grid:\n");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            scanf("%d", &board[i][j]);
            if (board[i][j] == 1)
            {
                row = i;
                col = j;
            }
            if(board[i][j]>highest){
                highest=board[i][j];
            }
        }
    }

    if (task4SolveZipBoardImplementation(board, solution, size, row, col, highest))
    {
        printf("Solution:\n");
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                printf("%c ", solution[i][j] ? solution[i][j] : 'X');
            }
            printf("\n");
        }
    }
    else
    {
        printf("No solution exists.\n");
    }
}


void task5SolveSudoku()
{
    printf("Please enter the sudoku board:\n");
    int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE] = {0};
    for (int i = 0; i < SUDOKU_GRID_SIZE; i++)
    {
        for (int j = 0; j < SUDOKU_GRID_SIZE; j++)
        {
            scanf("%d", &board[i][j]);
        }
    }
    if (task5SolveSudokuImplementation(board))
    {
        printf("Solution found:\n");
        printSudoku(board);
    }
    else
    {
        printf("No solution exists.\n");
    }

}


/***************************
********* HELPERS **********
****************************/
// Task 3
int readTerms(char terms[][LONGEST_TERM+1], int maxNumOfTerms, char type[])
{
    int termsCount;
    printf("Please insert number of %s:\n", type);
    scanf("%d", &termsCount);
    if(termsCount < 1 || termsCount > maxNumOfTerms){
        termsCount = maxNumOfTerms;
    }
    printf("Please insert the list of %s:\n", type);
    for(int i=0;i<termsCount;i++){
        printf("%d. ",i+1);
        scanf(" %[^\n]",terms[i]);
    }
    return termsCount;
}

int task3HelperNumOfTerms(int i, char terms[][LONGEST_TERM+1])
{
    if ((terms[i][0] != '\0') && (i < MAX_NUMBER_OF_TERMS))
    {
        i = task3HelperNumOfTerms(i+1, terms);
    }
    return i;
}


// Task 4
int task4HelperHighestInBoard(int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                            int size, int row, int col, int highest)
{
    if (board[row][col] > highest)
    {
        highest = board[row][col];
    }
    if (col + 1 < size)
    {
        int right = task4HelperHighestInBoard(board, size, row, col + 1, highest);
        if (right > highest)
        {
            highest = right;
        }
        if (row + 1 < size && col == 0) {
            int down = task4HelperHighestInBoard(board, size, row + 1, col, highest);
            if (down > highest)
            {
                highest = down;
            }
        } 
    }
    
    return highest;
}

int task4HelperAllTilesVisited(int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                            int size, int row, int col, int num)
{
    if (board[row][col] == 0)
    {
        num = board[row][col];
    } else if (board[row][col] == VISITED) {
        num = board[row][col];
    }
    if (col + 1 < size)
    {
        int right = task4HelperAllTilesVisited(board, size, row, col + 1, num);
        if (right == 0)
        {
            num = right;
        }
        if (row + 1 < size && col == 0) {
            int down = task4HelperAllTilesVisited(board, size, row + 1, col, num);
            if (down == 0)
            {
                num = down;
            }
        }
    }
    return num;
}


// Task 5
void printSudoku(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE])
{
    printf("+-------+-------+-------+\n");
    for (int i = 0; i < SUDOKU_GRID_SIZE; i++)
    {
        printf("| ");
        for (int j = 0; j < SUDOKU_GRID_SIZE; j++)
        {
            if (board[i][j] == 0)
                printf(". ");
            printf("%d ", board[i][j]);

            if ((j + 1) % SUDOKU_SUBGRID_SIZE == 0)
                printf("| ");
        }
        printf("\n");
        if ((i + 1) % SUDOKU_SUBGRID_SIZE == 0)
            printf("+-------+-------+-------+\n");
    }
}

int task5HelperSudokuSolver(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int size, int row, int col, int num)
{
    if (board[row][col] == EMPTY_CELL)
    {
        if (row < SUDOKU_GRID_SIZE && col < SUDOKU_GRID_SIZE)
        {
            // Sets temp row and col to the top-left corner of the current box
            int tempR = task5HelperSetRowCol(row);
            int tempC = task5HelperSetRowCol(col);
        
            // Checks if num can be placed in the cell
            int boxCheck = task5HelperCheckBox(board, size, tempR, tempC, num);
            int colCheck = task5HelperCheckCol(board, size, 0, col, num);
            int rowCheck = task5HelperCheckRow(board, size, row, 0, num);

            if (boxCheck && colCheck && rowCheck)
            {
                board[row][col] = num;
                printf("Placing %d at (%d,%d)\n", board[row][col], row, col);
            } else {
                if (num <= SUDOKU_GRID_SIZE)
                {
                    return task5HelperSudokuSolver(board, size, row, col, num + 1);
                }
                return 0;
            }
        }
    }
    if (col + 1 < SUDOKU_GRID_SIZE && row + 1 < SUDOKU_GRID_SIZE &&
        task5HelperSudokuSolver(board, size, row, col + 1, SMALLEST_NUMBER_SUDOKU))
    {
        if (!col && task5HelperSudokuSolver(board, size, row + 1, col, SMALLEST_NUMBER_SUDOKU))
        {
            return 1;
        }
    }
    return 1;
}

int task5HelperCheckBox(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int size, int row, int col, int num)
{
    if (col < SUDOKU_GRID_SIZE && row < SUDOKU_GRID_SIZE && 1 && board[row][col] == num)
    {
        return 0;
    }
    if (col < SUDOKU_GRID_SIZE && row < SUDOKU_GRID_SIZE && col < (col / SUDOKU_SUBGRID_SIZE + 1) * SUDOKU_SUBGRID_SIZE)
    {
        if (task5HelperCheckBox(board, size, row, col + 1, num))
        {
            if (!(col % SUDOKU_SUBGRID_SIZE))
            {
                if (task5HelperCheckBox(board, size, row + 1, col, num))
                {
                    return 1;
                }
                return 0;
            }
        }
    }
    return 1;
}

int task5HelperCheckRow(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int size, int row, int col, int num)
{
    if (board[row][col] == num)
    {
        return 0;
    }
    if (col + 1 < SUDOKU_GRID_SIZE)
    {
        return task5HelperCheckRow(board, size, row, col + 1, num);
    }
    return 1;
}

int task5HelperCheckCol(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int size, int row, int col, int num)
{
    if (board[row][col] == num)
    {
        return 0;
    }
    if (row + 1 < SUDOKU_GRID_SIZE)
    {
        return task5HelperCheckCol(board, size, row + 1, col, num);
    }
    return 1;
}

int task5HelperSetRowCol(int index)
{
    if (index % SUDOKU_SUBGRID_SIZE)
    {
        index = task5HelperSetRowCol(index - 1);
    }
    return index;
}

/***************************
*********** TODO ***********
****************************/


void task1ReversePhraseImplementation()
{
    char c;
    int i = 1;
    scanf("%c", &c);
    if (c != '\n')
    {
        i--;
        task1ReversePhraseImplementation();
    }
    if (i)
    {
        printf("The reversed phrase is:");
    }
    printf("%c", c);
}


int task2CheckPalindromeImplementation(int length)
{
    int c1, c2;
    c1 = getchar();

    if (!(length - 2))
    {
        c2 = getchar();
        if (c1 == c2)
        {
            return 1;
        }
        return 0;
    } else if (!(length - 1) || !length) {
        return 1;
    }
    
    if (task2CheckPalindromeImplementation(length - 2)) {
        c2 = getchar();
        if (c1 == c2)
        {
            return 1;
        }
        return 0;
    }
    getchar();
    return 0;
}


void task3GenerateSentencesImplementation(char subjects[][LONGEST_TERM+1], int subjectsCount,
                                        char verbs[][LONGEST_TERM+1], int verbsCount,
                                        char objects[][LONGEST_TERM+1], int objectsCount)
{
    char sentence[LONGEST_SENTENCE+1] = "";
    int numSubs = task3HelperNumOfTerms(0, subjects);
    int numVerbs = task3HelperNumOfTerms(0, verbs);
    int numObs = task3HelperNumOfTerms(0, objects);
    int currentCount = (numSubs - subjectsCount) * numVerbs * numObs +
        (numVerbs - verbsCount) * numObs + (numObs - objectsCount) + 1;
    strcat(sentence, subjects[numSubs - subjectsCount]);
    strcat(sentence, " ");
    strcat(sentence, verbs[numVerbs - verbsCount]);
    strcat(sentence, " ");
    strcat(sentence, objects[numObs - objectsCount]);
    if (objectsCount > 0 && verbsCount > 0 && subjectsCount > 0 &&
        subjectsCount <= numSubs && verbsCount <= numVerbs && objectsCount <= numObs)
    {
        printf("%d. %s\n", currentCount, sentence);
        task3GenerateSentencesImplementation(subjects, subjectsCount, verbs, verbsCount, objects, objectsCount-1);
        if (verbsCount > 0 && numObs == objectsCount)
        {
            task3GenerateSentencesImplementation(subjects, subjectsCount, verbs, verbsCount-1, objects, numObs);
            if (subjectsCount > 0 && numVerbs == verbsCount)
            {
                task3GenerateSentencesImplementation(subjects, subjectsCount-1, verbs, numVerbs, objects, numObs);
            }
        }
    }
    return;
}


int task4SolveZipBoardImplementation(int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                    char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                    int size, int startR, int startC, int highest)
{
    // Check boundaries
    if (startR < 0 || startC < 0 || startR >= size || startC >= size)
    {
        return 0;
    }
    int originalValue = board[startR][startC];
    int highestInBoard = task4HelperHighestInBoard(board, size, 0, 0, SMALLEST_NUMBER_ZIP);
    int lowestInBoard = task4HelperAllTilesVisited(board, size, 0, 0, VISITED);

    // Check cell value and change it if needed
    if (originalValue != 0)
    {
        if (originalValue == highest + 1)
        {
            if (originalValue == highestInBoard)
            {
                if (lowestInBoard == VISITED)
                {
                    return 1;
                }
                return 0;
            }
            highest = originalValue;
            return task4SolveZipBoardImplementation(board, solution, size, startR, startC, highest);
        } else if (originalValue == SMALLEST_NUMBER_ZIP)
        {
            highest = originalValue;
        } else if (originalValue == VISITED || originalValue > highest)
        {
            return 0;
        }
    }

    board[startR][startC] = VISITED; // Mark as visited

    if (task4SolveZipBoardImplementation(board, solution, size, startR - 1, startC, highest))
    {
        solution[startR][startC] = 'U';
        return 1;
    }

    if (task4SolveZipBoardImplementation(board, solution, size, startR + 1, startC, highest))
    {
        solution[startR][startC] = 'D';
        return 1;
    }

    if (task4SolveZipBoardImplementation(board, solution, size, startR, startC - 1, highest))
    {
        solution[startR][startC] = 'L';
        return 1;
    }

    if (task4SolveZipBoardImplementation(board, solution, size, startR, startC + 1, highest))
    {
        solution[startR][startC] = 'R';
        return 1;
    }
    board[startR][startC] = originalValue; // Backtracking
    
    return 0;
}


int task5SolveSudokuImplementation(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE])
{
    if (task5HelperSudokuSolver(board, SUDOKU_GRID_SIZE, 0, 0, SMALLEST_NUMBER_ZIP))
    {
        return 1;
    }
    return 0;
}