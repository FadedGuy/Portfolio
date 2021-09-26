#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>

int checkFile(char *filename)
{
    std::ifstream file(filename);
    if(file.is_open())
    {
        return 0;
    }
    else
    {
        printf("Unable to open file: ", filename);
        return -1;
    }
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("A file has to be passes in a txt form, one word per line");
        return -1;
    }

    checkFile(argv[1]);
   
    return 0;
}