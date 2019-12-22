#include <stdio.h>
#include <stdlib.h>

// Declare printSudoku function
void printSudoku(int ***);
// Declare solveSudoku function
int solveSudoku(int ***);

//Check to see if it is finished
int isDone(int ***block){
    //1 is done, 0 is not done
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                if (*(*(*(block + i) + j) + k) == 0){
                    return 0;
                }
            }
        }
    }
    return 1;
}

//Check the square to be safe
int squareArg(int ***block, int num, int a){
    //1 if there is conflict, 0 if no conflict
    //Checks each square for conflict
    for(int j = 0; j < 3; j++){
        for (int k = 0; k < 3; k++){
            if (*(*(*(block + a)+j)+ k) == num){
                return 1;
            }
        }
    }
    return 0;
}

//Check the row to see if it is safe
int checkRow(int ***block, int num, int i, int j){
    if(i < 3){
        i = 0;
        for(int r = i; r < 3; r++){
            for(int k = 0; k < 3; k++){
                if(*(*(*(block+r)+j)+k) == num){
                    return 1;
                }
            }
        }
    }
    else if(i >= 3 && i < 6){
        i = 3;
        for(int r = i; r < 6; r++){
            for(int k = 0; k < 3; k++){
                if(*(*(*(block+r)+j)+k) == num){
                    return 1;
                }
            }
            
        }
    }
    else if(i >= 6 && i < 9){
        i = 6;
        for(int r = i; r < 9; r++){
            for(int k = 0; k < 3; k++){
                if(*(*(*(block+r)+j)+k) == num){
                    return 1;
                }
            }
            
        }
    }
    return 0;
}

//Checks the column to see if it is safe
int checkCol(int ***block, int num, int i, int k){
    int r1 = 0;
    int r2 = 0;
    int count = 0;
    int temp = 0;
    if(i == 0 || i == 3 || i == 6){
        r1 = 0;
        r2 = 7;
    }
    else if(i == 1 || i == 4 || i == 7){
        r1 = 1;
        r2 = 8;
    }
    else{
        r1 = 2;
        r2 = 9;
    }
    for(count = r1; count < r2; count+=3){
        for(int j = 0; j < 3; j++){
            temp = *(*(*(block+count)+j)+k);
            if(temp == num){
                return 1;
                }
            }
        }
    return 0;
}

int isSafe(int ***blocks, int num, int i, int j, int k){
    if(checkCol(blocks, num, i, k) == 0 && checkRow(blocks, num, i, j) == 0 && squareArg(blocks, num, i) == 0){
        return 1;
    }
    else
        return 0;
}
/*
The main program reads a text file containing the block values of the Sudoku grid.
It then saves each 3x3 block into a 2D array. The Sudoku grid is composed of 9 3x3 blocks.
*/
int main(int argc, char **argv){
    if (argc != 2){
        fprintf(stderr, "Usage: %s <file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;
    int ***blocks = (int ***)malloc(9 * sizeof(int **));

    // Open file for reading
    fptr = fopen(argv[1], "r");
    if (fptr == NULL){
        printf("Cannot Open File!\n");
        return 0;
    }

    // Read 9x9 blocks into 2D arrays
    for (i = 0; i < 9; i++){
        *(blocks + i) = (int **)malloc(3 * sizeof(int *));
        printf("Reading numbers in block %d... \n", i + 1);
        for (j = 0; j < 3; j++){
            *(*(blocks + i) + j) = (int *)malloc(3 * sizeof(int));

            fscanf(fptr, "%d %d %d", *(*(blocks + i) + j), *(*(blocks + i) + j) + 1, *(*(blocks + i) + j) + 2);
            printf("%d %d %d\n", *(*(*(blocks + i) + j)), *(*(*(blocks + i) + j) + 1), *(*(*(blocks + i) + j) + 2));
        }
    }

    // Print out original Sudoku grid
    printf("Printing Sudoku before being solved:\n");
    printSudoku(blocks);

    // Call solveSudoku and print out result
    printf("\nSolving Sudoku...\n\n");
    if (solveSudoku(blocks)){
        printf("Sudoku solved!\n");
        printSudoku(blocks);
    }
    else
        printf("This Sudoku cannot be solved!\n");

    return 0;
}

void printSudoku(int ***arr){
    // This function will print out the complete Sudoku grid (arr). It must produce the output in the SAME format as the samples in the instructions.

    //Need to print
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                printf("%d ", *(*(*(arr + j) + i) + k));
            } 
            printf("| ");   
        }
        printf("\n");
    }
    printf("-----------------------");
    printf("\n");
    for (int i = 0; i < 3; i++){
        for (int j = 3; j < 6; j++){
            for (int k = 0; k < 3; k++){
                printf("%d ", *(*(*(arr + j) + i) + k));
            }
            printf("| ");
        }
        printf("\n");
    }
    printf("-----------------------");
    printf("\n");
    for (int i = 0; i < 3; i++){
        for (int j = 6; j < 9; j++){
            for (int k = 0; k < 3; k++){
                printf("%d ", *(*(*(arr + j) + i) + k));
            }
            printf("| ");
        }
        printf("\n");
    }
}

int solveSudoku(int ***blocks)
{
    // This is the function to solve the Sudoku (blocks). Feel free to use any helper functions.
    // YOU MUST NOT USE ANY ARRAY NOTATION ([])!
    //Your implementation here
    if (isDone(blocks) == 1){ //Zero case
        return 1;
    }
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 3; j++){
                for(int k = 0; k < 3; k++){
                    if(*(*(*(blocks+i)+j)+k) == 0){
                        for(int num = 1; num <= 9; num++){
                            if(isSafe(blocks, num, i, j, k) == 1){
                                *(*(*(blocks+i)+j)+k) = num;
                                if(solveSudoku(blocks) == 1){                              
                                    return 1;
                                }                            
                            }   
                        } 
                    *(*(*(blocks+i)+j)+k) = 0;
                    return 0;
                    }            
                }
            }       
        }
    return 1;
}
