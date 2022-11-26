#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../RLEList.h"
#include "./AsciiArtTool.h"

char invertChar(char val)
{
    if(val=='@')
    {
        return ' ';
    }
    if(val==' ')
    {
        return '@';
    }
    return val;
}
int main(int argc, char** argv)
{
    const char* sourceFOpenMode = "r";
    const char * targetFOpenMode = "w";
    if(argc!=4)
    {
        return 0;
    }
    char* flag = argv[1];
    FILE* source = fopen(argv[2], sourceFOpenMode);
    if(source==NULL)
    {
        return 0;
    }
    FILE* target = fopen(argv[3], targetFOpenMode);
    if(target==NULL)
    {
        fclose(source);
        return 0;
    }
    RLEList sourceList = asciiArtRead(source);
    if(strcmp(flag, "-i")==0)
    {
        RLEListMap(sourceList, invertChar);
        asciiArtPrint(sourceList, target);
    }
    if(strcmp(flag, "-e")==0)
    {
        asciiArtPrintEncoded(sourceList, target);
    }
    fclose(source);
    fclose(target);
    if(sourceList!=NULL)
    {
        free(sourceList);
    }
    return 0;
}

