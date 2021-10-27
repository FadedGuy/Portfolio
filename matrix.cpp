#include "matrix.h"

matrix_t* newMat()
{
    matrix_t *mat = (matrix_t*) malloc(sizeof(matrix_t));
    if(mat == NULL)
        return NULL;

    for(int i = 0; i < MAX_SIZE_MAT; i++)
    {
        for(int j = 0; j < MAX_SIZE_MAT; j++)
        {
            mat->mat[i][j] = FILL_CHAR;
        }
    }

    mat->sizeWords = 0;
    mat->size = 0;

    return mat;
}


void printMat(matrix_t *mat)
{
    for(int i = 0; i < MAX_SIZE_MAT; i++)
    {
        for(int j = 0; j < MAX_SIZE_MAT; j++)
        {
            std::cout<<mat->mat[i][j]<<" ";
        }
        std::cout<<"\n";
    }
}

void freeMat(matrix_t *mat)
{
    free(mat);
}