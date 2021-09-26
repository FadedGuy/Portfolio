#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <time.h>

#define MAX_SIZE_MAT 35

/********************
 * Tiene que haber minimo 2 palabras en la sopa de letras
 * El tam minimo de la palabra mas larga es de 3 y el maximo
 * de MAX_SIZE_MAT
 ********************/

int checkFile(std::string filename)
{
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cerr<<"Unable to open file: " << filename << "\n";
        return -1;
    }
    return 0;
}

void getWordList(std::string filename, std::vector<std::string> &wordList, int &maxLength)
{
    std::ifstream file(filename);

    if(!file.is_open())
    {
        std::cerr<<"Unable to open file: " << filename << "\n";
    }
    else
    {
        std::string line;
        char c;
        while(file.get(c)){
            if(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
            {
                line += toupper(c);
            } 
            else if(c == '\n' || c == ',')
            {
                if(line.size() > maxLength) maxLength = line.size();
                if(line.size() > 0)
                {
                    wordList.push_back(line);
                    line = "";
                }
            }
        }
    }
}

void fillMatrixRandom(char mat[MAX_SIZE_MAT][MAX_SIZE_MAT], int maxL)
{
    srand(time(NULL));
    for(int i = 0; i < maxL; i++)
    {   
        for(int j = 0; j < maxL; j++)
        {
            mat[i][j] = 'A' + std::rand()%26;
        }
    }
}

void printMatrix(char mat[MAX_SIZE_MAT][MAX_SIZE_MAT], int maxL)
{
    for(int i = 0; i < maxL; i++)
    {   
        for(int j = 0; j < maxL; j++)
        {
            std::cout<<mat[i][j]<<" ";
        }
        std::cout<<"\n";
    }
}

void printAllWords(std::vector<std::string> &wordList)
{
    for(int i = 0; i < wordList.size(); i++)
    {
        std::cout<<i<<". "<<wordList[i]<<"\n";
    }
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        std::cerr<< "A file has to be passes in a txt form, one word per line\n";
        return -1;
    }

    if(checkFile(argv[1]) == 0)
    {
        std::vector<std::string> wordList;
        int maxSizeWord = 0;
        getWordList(argv[1], wordList, maxSizeWord);
        if(wordList.size() > 1 && maxSizeWord >= 2 && maxSizeWord <= MAX_SIZE_MAT)
        {
            // std::sort(wordList.begin(), wordList.end()); //No se si ordenarlas ayude realmente
            char matrix[MAX_SIZE_MAT][MAX_SIZE_MAT];
            fillMatrixRandom(matrix, maxSizeWord);
            printMatrix(matrix, maxSizeWord);
            printAllWords(wordList);

        }
        else
        {
            std::cout<<"Error while parsing file: "<<argv[1]<<"\n";
        }
    }
    return 0;
}