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
    const char* SOURCE_F_OPEN_MODE = "r";
    const char * TARGET_F_OPEN_MODE = "w";
    if(argc!=4)
    {
        return 0;
    }
    char* flag = argv[1];
    FILE* source = fopen(argv[2], SOURCE_F_OPEN_MODE);
    if(source==NULL)
    {
        return 0;
    }
    FILE* target = fopen(argv[3], TARGET_F_OPEN_MODE);
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
        RLEListDestroy(sourceList);
    }
    return 0;
}

