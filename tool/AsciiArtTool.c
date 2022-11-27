//
// Created by omer.bahat on 11/24/22.
// and then comes ahmad.fadool did some changes on 11/26-27/22
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
    RLEListResult* listExportStatus=RLE_LIST_SUCCESS;
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
{   const int LINE_LINGTH=300;
    char* buffer= malloc(LINE_LINGTH*sizeof(char));
    if(!buffer)
    {
        return NULL;
    }
    buffer="";/////////////////////////////////////////////////////////////////
    RLEList newList= RLEListCreate();
    if(!newList)
    {
        return NULL;
    }
    
    while(fgets(buffer,sizeof buffer, in_stream)!= NULL)
    {
        int i=0;
        while(buffer[i]!='\0')   // was \n gotta check if it work 
        {
            if(RLEListAppend(newList,buffer[i])==RLE_LIST_OUT_OF_MEMORY)
            {
                RLEListDestroy(newList);
                return NULL;
            }
            i++;
        }

        buffer="";

    }
   
    return newList;

   
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{   RLEListResult* result =RLE_LIST_SUCCESS;
    if(!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
     int size = RLEListSize(list);
    // no need to check for null list already checked
    // size+1= string length with the \0 in the end 
    char* string = malloc((size+1)*sizeof(char));
    if(!string)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    string ="";
    for(int i=0; i<size; i++)
    {
        string[i]=RLEListGet(list,i,result);
        if(string[i]==0)
        {
            free(string);
            return *result;
        }
    }
    string[size]='\0';

    fputs(string,out_stream);
    return RLE_LIST_SUCCESS;
}
