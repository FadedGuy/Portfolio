#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <map>
#include <math.h>

#define MAX_SIZE_MAT 35
#define MAX_WORDS 10
#define FILL_CHARACTER '0'

/********************
 * Tiene que haber minimo 2 palabras en la sopa de letras
 * El tam minimo de cada palabra es de 3 y el maximo de MAX_SIZE_MAT
 * 
 * TODO
 *  -Cambiar codigo a distintos archivos y mas funciones 
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
            mat[i][j] = FILL_CHARACTER;
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

void charInsertMatrix(char mat[MAX_SIZE_MAT][MAX_SIZE_MAT], int line, int lineBegin, std::string word, int direction, int limits)
{
	//dx y dy para la direccion
	//Todo se hace en fors distintos para evitar aumentar la complejidad a lo baboso
	//Chequeo inicial si toda la linea esta libre, si no esta libre la linea, checar si alguna letra de la linea se encuentra en word, si se encuentra, intentar hacer cruce. 
	//Si el cruce es valido, insertar, si no es valido, generar una nueva posicion
	int lineCnt = lineBegin, i = 0;

	//Map the current word
	std::map<char, int> charsWord;
	for(int j = 0; j < word.size(); j++)
	{
		charsWord[toupper(word[j]) - 'A']++;
	}
	// for(int j = 0; j < charsWord.size(); j++)
	// {
	// 	std::cout<<charsWord[j]<<" ";
	// }
	// std::cout<<word<<"\n";

	//Chequeo de linea si esta libre
	while(direction == 0 && i < word.size() && mat[lineCnt][line] == FILL_CHARACTER)
	{
		lineCnt++;
		i++;
	}
	if(direction == 0 && i < word.size())
	{
		printMatrix(mat, limits);
		//Checar invirtiendo direccion y usando line para recorrer la linea y checar si esa linea opuesta tiene algun caracter presente tambien en la palabra actual
		//Al no saber a que palabra pertenece la letra no es posible usar el map para evitar usar find, pero si se puede usar find para cada encuentro.
		for(int z = 0; z < limits; z++)
		{
			if(word.find(mat[z][line]) != std::string::npos)
			{
				std::cout<<"Hay match para "<<word << " con "<<mat[z][line]<<"\n";
			}
		}
		std::cout << "\nNo libre para "<<word<<" en la posicion " << line<<","<<lineCnt<<" en direccion:"<<direction<<" >"<<mat[lineCnt][line]<<"\n";
		return void();
	}
	lineCnt = lineBegin;
	i = 0;
	while(direction == 1 && i < word.size() && mat[line][lineCnt] == FILL_CHARACTER)
	{
		lineCnt++;
		i++;
	}
	if(direction == 1 && i < word.size())
	{
		printMatrix(mat, limits);
		for(int z = 0; z < limits; z++)
		{
			if(word.find(mat[line][z]) != std::string::npos)
			{
				std::cout<<"Hay match para "<<word << " con "<<mat[line][z]<<"\n";
			}
		}
		//Checar invirtiendo direccion y usando line para recorrer la linea y checar si esa linea opuesta tiene algun caracter presente tambien en la palabra actual
		std::cout << "\nNo libre para "<<word<<" en la posicion " << lineCnt<<","<<line<<" en direccion:"<<direction<<" >"<<mat[line][lineCnt]<<"\n";
		return void();
	}

	lineCnt = lineBegin;
    for(int i = 0; i < word.size(); i++)
    {
		if(direction == 0)
			mat[lineCnt][line] = word[i];
		else 
			mat[line][lineCnt] = word[i];
        lineCnt++;
    }
}

void insertWordMatrix(char mat[MAX_SIZE_MAT][MAX_SIZE_MAT], std::vector<std::string> &words, int maxSize, int iPos, std::map<char, int> wordListMap[])
{
    /*********************
     * wordListMap podria usarse para ver si una palabra cruza en alguna letra con las palabras anteriores para saber si es que un cruce es favorable
     * Espero que esto deberia de solucionar tambien las colisiones entre las palabras que actualmente hay
     *********************/
    int randLine = rand() % maxSize; //Elige la linea en la que ira la palabra
    int verticalHorizontal = rand() % 2; //Elige si va en vertical o horizontal (a futuro tambien diagonal) 
    int initLine = 0;
    if(maxSize - words[iPos].size() > 0){initLine = rand()% (maxSize - words[iPos].size());} //Elige en que posicion inicia la palabra dentro de los limites y de su tamano. Default 0
    //std::cout<<"Line: " << randLine << " Vertical: " << verticalHorizontal << " initLine: " << initLine << "\n";
    // for(int j = iPos-1; j >= 0; j--) //Recorre las palabras anteriores
    // {    
    //     int cruces = 0, k = 0; 
	// 	while (k < wordListMap[j].size() && k < wordListMap[iPos].size() && cruces == 0) //Checar palabra anterior con palabra actual buscando si coinciden en algun caracter
    //     {   
    //         if(wordListMap[j][k] > 0 && wordListMap[iPos][k] > 0) //No esta vacia esa casilla de la letra
    //         {

    //             //std::cout<<"Cruce en " << static_cast<char>(k+'A')<<" ";
    //             //Checar cruce aqui mismo no hay necesidad de hacerlo despues
    //             wordListMap[j][k] > wordListMap[iPos][k] ? cruces=wordListMap[j][k] : cruces=wordListMap[iPos][k];
    //             std::cout << words[j] << " " << words[iPos] << " cruzan " << cruces << " veces con "<<char(k+'A')<<"\n";
    //             // int ind_iPos = 0, ind_j = 0;
    //             // for(int m = 1; m <= cruces; m++)
    //             // {
    //             //     ind_iPos = words[iPos].find(k+'A', ind_iPos);
    //             //     ind_j = words[j].find(k+'A', ind_j);
    //             //     std::cout<<words[iPos] << " " << words[j] << " cruzan en " << ind_iPos++ << " " << ind_j << "\n";
                    
    //             // }
    //         }
    //         cruces = 0;
	// 		k++;
    //     }


    //     //If cruces, ver si cabe en la matriz volteando verticalHorizontal usando mismo randLine ya que es cuadrado
    //     // if(cruces > 0)
    //     // {
    //     //     //Cruce es valido si la letra que tiene cruce va de init a su tama;o y estos estan dentro de 0 y maxSize
    //     //     std::cout<<words[j] << " tiene " << cruces << " cruces con " << words[iPos] << "\n";
    //     // }
    //     // else
    //     // {
    //     //     std::cout<<words[j] << " no tiene cruces con " << words[iPos] << "\n";
    //     // }
    // }
    charInsertMatrix(mat, randLine, initLine, words[iPos], verticalHorizontal, maxSize);
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
			//Print palabras mapeadas
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
            //printMatrix(matrix, maxSizeWord);
            printAllWords(wordList);
			std::cout<<"TAM: "<<maxSizeWord<<"\n";

            //mat[i][j] i va para abajo, j para el lado
            srand(time(NULL));
            for(int i = 0; i < wordList.size(); i++)
            {
                insertWordMatrix(matrix, wordList, maxSizeWord, i, wordListMapped);
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