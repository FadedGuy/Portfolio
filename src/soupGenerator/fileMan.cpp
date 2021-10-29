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

// Parses file to get words, using as separators line breaks or comma.
// Add arg to set separator/separators 
std::vector<std::string> getWordsFile(std::string filename, int word_limit)
{
    std::ifstream file(filename);
    std::vector<std::string> words;
    if(!file.is_open())
    {
        std::cerr<<"Unable to open file: " << filename << "\n";
        return words;
    }

    std::string line;
    char c;
    while(file.get(c) && words.size() < word_limit)
    {
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        {
            line += toupper(c);
        }
        else if((c == '\n' || c == ','))
        {
            if(line.size() >= 2) //Verify word length is equal or greater than 3
            {
                words.push_back(line);
                line.clear();
            }
        }
        else
        {
            std::cerr<<"Invalid character: " << c << " skipped\n";
        }
    }

    return words;
}