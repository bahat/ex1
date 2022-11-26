//
// Created by omer.bahat on 11/24/22.
//

#include "AsciiArtTool.h"

asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if(list==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    const char* FOPEN_MODE = "w";
    FILE* stream = fopen (out_stream, FOPEN_MODE);
    if(stream==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    char* listExportStatus;
    char* encodedString = RLEListExportToString(list, listExportStatus);
    assert(list!=NULL);
    if(*listExportStatus!=RLE_LIST_SUCCESS)
    {
        fclose(stream);
        return *listExportStatus;
    }
    int writeStatus = fputs(encodedString, stream);
    free(encodedString);
    fclose(stream);
    if(writeStatus==EOF)
    {
        return RLE_LIST_ERROR;
    }
    return RLE_LIST_SUCCESS;
    
}

