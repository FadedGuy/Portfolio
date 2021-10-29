#include "matrix.h"
#include "fileMan.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        std::cerr<< "Invalid parameters\n";
        return 1;
    }

    if(checkFile(argv[1]) != 0)
    {
        std::cerr<<"Error while opening file" << argv[1] << "\n";
        return 1;
    }

    matrix_t *mat = insertWordsMat(newMat(), argv[1]);
    if(mat == NULL)
    {
        std::cerr<<"Unable to allocate space\n";
        return 1;
    }

    fillSpacesMat(mat);
    printMat(mat);

    free(mat);
    return 0;
}