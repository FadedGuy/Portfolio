#include "matrix.h"
#include "fileMan.h"

matrix_t* newMat()
{
    matrix_t *mat = (matrix_t*) malloc(sizeof(matrix_t));
    if(mat == NULL)
        return NULL;

    int cnt = 0;
    for(int i = 0; i < MAX_SIZE_MAT; i++)
    {
        for(int j = 0; j < MAX_SIZE_MAT; j++)
        {
            mat->mat[i][j] = FILL_CHAR;
            cnt++;
        }
    }

    mat->sizeWords = 0;
    mat->sizeMat = 0;

    return mat;
}

matrix_t* insertWordsMat(matrix_t* mat, std::string filename)
{
    if(mat == NULL)
        return mat;

    std::vector<std::string> words = getWordsFile(filename, MAX_WORDS);
    if(words.size() == 0)
    {
        std::cerr<<"Unable to parse file " << filename << "\n";
        return mat;
    }


    for(int i = 0; i < words.size(); i++)
    {
        std::cout<<i<<". "<<words[i]<<"\n";
    }
        srand(time(NULL));

    mat->sizeMat = setSizeMat(words);
    for(int i = 0; i < words.size(); i++)
    {
    srand(time(NULL));

        mat = verifyAndInsertMat(mat, words[i], 0);
    }

    return mat;
}

matrix_t* verifyAndInsertMat(matrix_t* mat, std::string word, int tries)
{
    int colRow = rand()% mat->sizeMat;
    int x = rand()% 2;
    int y = x == 0 ? 1 : 0;
    int diff = (mat->sizeMat - (word.size()-1));
    int pos = rand()% diff;
    int xI = pos, yI = pos;
    bool possible = true;

    while(possible && ((xI < word.size()+pos) && (yI < word.size()+pos)))
    {
        if(mat->mat[yI][xI] != FILL_CHAR)
        {
            possible = false;
        }
        yI+=y;
        xI+=x;
    }

    if(possible)
    {
        xI = pos; yI = pos;
        int wrdCnt = 0;
        while((xI < word.size()+pos) && (yI < word.size()+pos))
        {
            mat->mat[yI][xI] = word[wrdCnt];
            wrdCnt++;
            xI+=x;
            yI+=y;
        }

        mat->words[mat->sizeWords] = word;
        mat->sizeWords++;
    }
    else
    {
        //std::cout<<"Space for "<<word << " not available\n";
        if(tries < MAX_TRIES)
            verifyAndInsertMat(mat, word, tries+1);
    }

    return mat;
}

matrix_t* fillSpacesMat(matrix_t* mat)
{
    for(int i = 0; i < mat->sizeMat; i++)
    {
        for(int j = 0; j < mat->sizeMat; j++)
        {
            if(mat->mat[i][j] == FILL_CHAR)
            {
                mat->mat[i][j] = 'A' + rand()% 26;
            }
        }
    }

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
    return max + (2+rand()%3);
}

void printMat(matrix_t *mat)
{
    if(mat->sizeMat == 0)
    {
        std::cerr<<"Empty matrix\n";
        return;
    }

    for(int i = 0; i < mat->sizeMat; i++)
    {
        for(int j = 0; j < mat->sizeMat; j++)
        {
            std::cout<<mat->mat[i][j]<<" ";
        }
        std::cout<<"\n";
    }

    std::cout<<"\tWords in Soup\n";
    for(int i = 0; i < mat->sizeWords; i++)
    {
        std::cout<<i+1<<". "<<mat->words[i]<<"\n";
    }
}

void freeMat(matrix_t *mat)
{
    free(mat);
}