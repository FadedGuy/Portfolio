#include "fileMan.h"

int checkFile(std::string filename)
{
    std::ifstream file(filename);
    if(!file.is_open())
    {
        return 1;
    }
    file.close();
    return 0;
}