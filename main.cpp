#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <map>

#define MAX_SIZE_MAT 35
#define MAX_WORDS 10

/********************
 * Tiene que haber minimo 2 palabras en la sopa de letras
 * El tam minimo de cada palabra es de 3 y el maximo de MAX_SIZE_MAT
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

void getWordList(std::string filename, std::vector<std::string> &wordList, int &maxLength, std::map<char, int> wordListMap[], int &cnt)
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
        while(file.get(c) && wordList.size() < MAX_WORDS){
            if(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
            {
                line += toupper(c);
                wordListMap[cnt][toupper(c) - 'A']++;
            } 
            else if(c == '\n' || c == ',')
            {
                if(line.size() > maxLength) maxLength = line.size();
                if(line.size() > 0)
                {
                    wordList.push_back(line);
                    cnt++;
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
            //mat[i][j] = 'A' + std::rand()%26;
            mat[i][j] = '0';
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

void insertWordMatrix(char mat[MAX_SIZE_MAT][MAX_SIZE_MAT], std::vector<std::string> &words, int maxSize, int iPos, std::map<char, int> wordListMap[], int sizeWordListMapped)
{
    /*********************
     * wordListMap podria usarse para ver si una palabra cruza en alguna letra con las palabras anteriores para saber si es que un cruce es favorable
     * Espero que esto deberia de solucionar tambien las colisiones entre las palabras que actualmente hay
     *********************/
    int randLine = rand() % maxSize; //Elige la linea en la que ira la palabra
    int verticalHorizontal = rand() % 2; //Elige si va en vertical o horizontal (a futuro tambien diagonal)
    int init = 0;
    if(maxSize - words[iPos].size() > 0){init = rand()% (maxSize - words[iPos].size());} //Elige en que posicion inicia la palabra dentro de los limites y de su tamano. Default 0
    std::cout<<"Line: " << randLine << " Vertical: " << verticalHorizontal << " Init: " << init << "\n";
    if(verticalHorizontal == 0) //Vertical line
    {
        for(int j = 0; j < words[iPos].size(); j++)
        {
            mat[init][randLine] = words[iPos][j];
            init++;
        }
        }
    else //Horizontal line
    {
        for(int j = 0; j < words[iPos].size(); j++)
        {
            mat[randLine][init] = words[iPos][j];
            init++;
        }
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
        std::map<char, int> wordListMapped[MAX_WORDS];
        int maxSizeWord = 0;
        int sizeWordListMapped = 0;
        getWordList(argv[1], wordList, maxSizeWord, wordListMapped, sizeWordListMapped);
        if(wordList.size() > 1 && maxSizeWord >= 2 && maxSizeWord <= MAX_SIZE_MAT)
        {
            // for(int i = 0; i < sizeWordListMapped; i++)
            // {
            //     for(int j = 0; j < wordListMapped[i].size(); j++)
            //     {
            //         std::cout<<wordListMapped[i][j]<<" ";
            //     }
            //     std::cout<<"\t:"<<wordList[i];
            //     std::cout<<"\n";
            // }
            char matrix[MAX_SIZE_MAT][MAX_SIZE_MAT];
            fillMatrixRandom(matrix, maxSizeWord);
            printMatrix(matrix, maxSizeWord);
            printAllWords(wordList);

            //mat[i][j] i va para abajo, j para el lado
            srand(time(NULL));
            for(int i = 0; i < wordList.size(); i++)
            {
                insertWordMatrix(matrix, wordList, maxSizeWord, i, wordListMapped, sizeWordListMapped);
            }
            printMatrix(matrix, maxSizeWord);
        }
        else
        {
            std::cout<<"Error while parsing file: "<<argv[1]<<"\n";
        }
    }
    return 0;
}