#include "matrix.h"
#include "fileMan.h"

#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        std::cerr<< "Invalid parameters\n";
        return 1;
    }

    if(checkFile(argv[1]) != 0)
    {
        std::cerr<<"Error with file" << argv[1] << "\n";
        return 1;
    }

    matrix_t *mat = newMat();
    printMat(mat);

    std::cout<<"Sucess with file\n";

    return 0;
}