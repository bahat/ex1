//
// Created by omer.bahat on 11/24/22.
//
#include <assert.h>
#include <stdlib.h>
#include "AsciiArtTool.h"

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if(list==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(out_stream==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult* listExportStatus = (RLEListResult*)RLE_LIST_ERROR;
    char* encodedString = RLEListExportToString(list, listExportStatus);
    assert(list!=NULL);
    if(*listExportStatus!=RLE_LIST_SUCCESS)
    {
        return *listExportStatus;
    }
    int writeStatus = fputs(encodedString, out_stream);
    free(encodedString);
    if(writeStatus==EOF)
    {
        return RLE_LIST_ERROR;
    }
    return RLE_LIST_SUCCESS;
    
}

RLEList asciiArtRead(FILE* in_stream)
{
    return NULL;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    return RLE_LIST_SUCCESS;
}
