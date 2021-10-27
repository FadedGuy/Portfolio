#include "matrix.h"
#include "fileMan.h"

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
    mat->sizeMat = 0;

    return mat;
}

matrix_t* insertWordsMat(matrix_t* mat, std::string filename)
{
    std::vector<std::string> words = getWordsFile(filename, MAX_WORDS);
    if(words.size() == 0)
    {
        std::cerr<<"Unable to parse file " << filename << "\n";
        return mat;
    }
    mat->sizeMat = setSizeMat(words);

    return mat;
}

int setSizeMat(std::vector<std::string> wordList)
{   
    int max = 0;
    for(int i = 0; i < wordList.size(); i++)
    {
        if(max < wordList[i].size()) 
            max = wordList[i].size();
    }
    return max;
}

void printMat(matrix_t *mat)
{
    if(mat->sizeMat == 0)
    {
        std::cerr<<"Empty matrix\n";
        return;
    }

    for(int i = 0; i < MAX_SIZE_MAT; i++)
    {
        for(int j = 0; j < MAX_SIZE_MAT; j++)
        {
            std::cout<<mat->mat[i][j]<<" ";
        }
        std::cout<<"\n";
    }

    std::cout<<"\tWords in Soup\n";
    for(int i = 0; i < mat->sizeWords; i++)
    {
        std::cout<<i<<". "<<mat->words[i]<<"\n";
    }
}

void freeMat(matrix_t *mat)
{
    free(mat);
}