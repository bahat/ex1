//
// Created by omer.bahat on 11/24/22.
// and then comes ahmad.fadool did some changes on 11/26-27/22
//
#include <assert.h>
#include <stdlib.h>
#include "AsciiArtTool.h"
#define SINGLE_CHAR_BUFFER_LENGTH 2

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
    RLEListResult listExportStatus=RLE_LIST_SUCCESS;
    char* encodedString = RLEListExportToString(list, &listExportStatus);
    assert(list!=NULL);
    if(listExportStatus!=RLE_LIST_SUCCESS)
    {
        return listExportStatus;
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
    if(in_stream==NULL)
    {
        return NULL;
    }
    RLEList artList = RLEListCreate();
    if(artList==NULL)
    {
        return NULL;
    }
    char buffer[SINGLE_CHAR_BUFFER_LENGTH] = "";
    while(fgets(buffer, SINGLE_CHAR_BUFFER_LENGTH, in_stream)!= NULL)
    {
        RLEListAppend(artList, *buffer);
    }
    return artList;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{   RLEListResult result =RLE_LIST_SUCCESS;
    if(list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(out_stream==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    int size = RLEListSize(list);
    for(int i=0; i<size; i++)
    {
        fprintf(out_stream, "%c", RLEListGet(list, i, &result));
    }
    return RLE_LIST_SUCCESS;
}

