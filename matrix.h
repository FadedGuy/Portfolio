#include <cstdlib>
#include <iostream>
#include <string>

#define MAX_SIZE_MAT 35
#define MAX_WORDS 10
#define FILL_CHAR '0'

typedef struct{
    char mat[MAX_SIZE_MAT][MAX_SIZE_MAT];
    int sizeMat;
    std::string words[MAX_WORDS];
    int sizeWords;
}matrix_t;



matrix_t* newMat();
void printMat(matrix_t *);
void freeMat(matrix_t*);