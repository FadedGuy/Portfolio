#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

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

std::vector<std::string> getWordList(std::string filename)
{
    std::vector<std::string> wordList;
    std::ifstream file(filename);
    int maxLength = 0;

    if(!file.is_open())
    {
        std::cerr<<"Unable to open file: " << filename << "\n";
        return wordList;
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
            else if(c == '\n' || c == ',' || c == ' ')
            {
                if(line.size() > maxLength)
                {
                    maxLength = line.size();
                }
                wordList.push_back(line);
                line = "";
            }
            else
            {
                //Ignorar caracter no valido
            }
        }
    }
    wordList.push_back(std::to_string(maxLength));
    return wordList;
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
        wordList = getWordList(argv[1]);   
        for(int i = 0; i <= wordList.size()-1; i ++){
            std::cout<<wordList[i]<<"\n";
        }     
        std::cout<<wordList[wordList.size()];
    }
    return 0;
}