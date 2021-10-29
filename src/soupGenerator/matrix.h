#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>

// Make MAX_SIZE_MAT and MAX_WORDS variable in function of the space available
#define MAX_SIZE_MAT 35
#define MAX_WORDS 10
#define MAX_TRIES 3
#define FILL_CHAR '0'

typedef struct{
    char mat[MAX_SIZE_MAT][MAX_SIZE_MAT];
    int sizeMat;
    std::string words[MAX_WORDS];
    int sizeWords;
}matrix_t;

matrix_t* newMat();
matrix_t* insertWordsMat(matrix_t*, std::string);
matrix_t* verifyAndInsertMat(matrix_t*, std::string, int);
matrix_t* fillSpacesMat(matrix_t*);
int setSizeMat(std::vector<std::string>);
void printMat(matrix_t *);
void freeMat(matrix_t*);