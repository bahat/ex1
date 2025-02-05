#include "./RLEList.h"
#include <assert.h>
#include <stdlib.h>

struct RLEList_t
{
    char value;
    int length;
    RLEList next;
};
RLEList RLEListCreate()
{
    RLEList list = malloc(sizeof(RLEList));
    if(list!=NULL)
    {
        list->value = 0;
        list->length = 0;
        list->next = NULL;
    }
    return list;
}
void RLEListDestroy(RLEList list)
{
    RLEList toDelete;
    while(list!=NULL)
    {
        toDelete = list;
        assert(toDelete!=NULL);
        list = list->next;
        free(toDelete);
    }
}
RLEListResult RLEListAppend(RLEList list, char value)
{
    if(list==NULL||value=='\0')
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList lastNode = list;
    while(lastNode->next!=NULL)
    {
        lastNode=lastNode->next;
    }
    if(value==lastNode->value)
    {
        lastNode->length+=1;
        return RLE_LIST_SUCCESS;
    }

        RLEList newNode = RLEListCreate();
        if(newNode==NULL)
        {
            return RLE_LIST_OUT_OF_MEMORY;
        }
        else
        {
            newNode->length = 1;
            newNode->value = value;
            lastNode->next = newNode;
        }
    return RLE_LIST_SUCCESS;


}
int RLEListSize(RLEList list)
{
    if(list==NULL)
    {
        return -1;
    }
    else
    {
        int totalLength=0;
        RLEList tempNode = list;
        while(tempNode!=NULL)
        {
            totalLength+=tempNode->length;
            tempNode=tempNode->next;
        }
        return totalLength;
    }
}
RLEListResult RLEListRemove(RLEList list, int index)
{
    int const MIN_NODE_LENGTH=1;
    if(list==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    if(index>=RLEListSize(list) || index<0)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    assert(RLEListSize(list)>0);
    assert(list->next!=NULL);

    RLEList previousNode = list;
    RLEList currentNode = list->next;
    int currentIndex = currentNode->length-1;
    while(index>currentIndex)
    {
        previousNode=currentNode;
        currentNode=currentNode->next;
        currentIndex+=currentNode->length;
    }
    assert(index<=currentIndex);//to remove in curr node
    if(currentNode->length>MIN_NODE_LENGTH)
    {
        //remove 1 from length
        currentNode->length-=1;
        return RLE_LIST_SUCCESS;
    }
    else
    {
        previousNode->next=currentNode->next;
        free(currentNode);
        if(previousNode->next==NULL)
        {
            return RLE_LIST_SUCCESS;
        }
        else
        {
            //tests if adjacent nodes are equal
            if(previousNode->value==previousNode->next->value)
            {
                RLEList duplicateNodeToDelete = previousNode->next;
                previousNode->length+=duplicateNodeToDelete->length;
                previousNode->next = duplicateNodeToDelete->next;
                free(duplicateNodeToDelete);
            }
            return RLE_LIST_SUCCESS;
        }
    }
}
char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if(list==NULL)
    {
        if(result!=NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
    if(index<0 || index>= RLEListSize(list))
    {
        if(result!=NULL)
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }
    assert(index< RLEListSize(list));
    RLEList currentNode = list->next;
    while(currentNode!=NULL)
    {
        if(index<currentNode->length)
        {
            //we need to return current char
            if(result!=NULL)
            {
                *result = RLE_LIST_SUCCESS;
            }
            return currentNode->value;
        }
        else
        {
            index-=currentNode->length;
            currentNode=currentNode->next;
        }
    }

    return 0;
}
char* RLEListExportToString(RLEList list, RLEListResult* result) {
    if (list == NULL)
    {
        if(result!=NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    int totalCharactersToAllocate=0;
    RLEList currentNode = list->next;
    int currentLength;
    while(currentNode!=NULL)
    {
        totalCharactersToAllocate+=2;//newline and char each have 1 char
        currentLength = currentNode->length;
        while(currentLength!=0)
        {
            totalCharactersToAllocate++;
            currentLength/=10;
        }
        currentNode=currentNode->next;
    }
    char* finalString = malloc(totalCharactersToAllocate+1);
    currentNode = list->next;//skipping dummy node
    char* currentStringValue = finalString;
    int currentIntLength;
    while(currentNode!=NULL)
    {
        *currentStringValue=currentNode->value;
        currentStringValue++;
        currentIntLength=sprintf((currentStringValue),"%d", currentNode->length );
        currentStringValue+=currentIntLength;
        *currentStringValue='\n';
        currentStringValue++;
        currentNode=currentNode->next;
    }
    *currentStringValue='\0';
    if(result!=NULL)
    {
        *result = RLE_LIST_SUCCESS;
    }
    return finalString;
}


RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if(list==NULL || map_function==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList currentNode = list->next;
    RLEList previousNode = list;
    while(currentNode!=NULL)
    {
        currentNode->value=map_function(currentNode->value);
        assert(currentNode->value!='\0');
        if(currentNode->value == previousNode->value)
        {
            previousNode->length+=currentNode->length;
            previousNode->next=currentNode->next;
            free(currentNode);
            currentNode=previousNode->next;
        }
        else
        {
            previousNode=currentNode;
            currentNode=currentNode->next;
        }
    }
    return RLE_LIST_SUCCESS;

}


//struct RLEList_t
//{
//    //TODO: implement
//    char val;
//    int length;
//    RLEList next;
//};
//
//RLEListResult removeNode(RLEList previousNode, RLEList currentNode, RLEList list)
//{
//    /*edge case I- list has one node*/
//    if(previousNode==NULL&&currentNode->next==NULL)
//    {
//        currentNode->val = '\0';
//        currentNode->length = 0;
//        return RLE_LIST_SUCCESS;
//    }
//    /*edge case II- first node shall be removed*/
//    if(previousNode==NULL)
//    {
//        list = list->next;
//        assert(currentNode!=NULL);
//        free(currentNode);
//        currentNode=list;
//        return RLE_LIST_SUCCESS;
//    }
//
//    /*edge case III- last node shall be removed*/
//    if(currentNode->next==NULL)
//    {
//        assert(currentNode!=NULL);
//        free(currentNode);
//        return RLE_LIST_SUCCESS;
//    }
//
//    /*edge case IV- node before and after have same value*/
//    if(currentNode->next->val==previousNode->val)
//    {
//        previousNode->length+=currentNode->next->length;
//        previousNode->next=currentNode->next->next;
//        RLEList todelete = currentNode->next;
//        free(todelete);
//        free(currentNode);
//        return RLE_LIST_SUCCESS;
//    }
//    /*normal removal*/
//    previousNode->next=currentNode->next;
//    free(currentNode);
//    return RLE_LIST_SUCCESS;
//}
//RLEList RLEListCreate()
//{
//    RLEList tmp=(RLEList)malloc(sizeof(struct RLEList_t));
//    if(tmp==NULL)
//    {
//        return NULL;
//    }
//    tmp->next=NULL;
//    tmp->length=0;
//    tmp->val=0;
//    return tmp;
//}
//
//void RLEListDestroy(RLEList list)
//{
//    while (list!=NULL)
//    {
//        RLEList toDelete = list;
//        list=list->next;
//        assert(toDelete!=NULL);
//        free(toDelete);
//    }
//
//}
//RLEListResult RLEListAppend(RLEList list, char value)
//{
//    if(list==NULL)
//    {
//        return RLE_LIST_NULL_ARGUMENT;
//    }
//    if(list->val=='\0')
//    {
//        list->val = value;
//        list->length = 1;
//        return RLE_LIST_SUCCESS;
//    }
//    RLEList lastNode = list;
//    assert(list->val!='\0');
//    while(lastNode->next!=NULL)
//    {
//        lastNode = lastNode->next;
//    }
//    if(lastNode->val==value)
//    {
//        lastNode->length+=1;
//        return RLE_LIST_SUCCESS;
//    }
//    RLEList newNode = RLEListCreate();
//    if(newNode==NULL)
//    {
//        return RLE_LIST_OUT_OF_MEMORY;
//    }
//    newNode->val = value;
//    newNode->length = 1;
//    lastNode->next = newNode;
//    return RLE_LIST_SUCCESS;
//}
//
//
//int RLEListSize(RLEList va_list)
//{
//    if(va_list==NULL)
//    {
//        return -1;
//    }
//    assert(va_list);
//    int len = 0;
//    RLEList tempNode = va_list;
//
//    while(tempNode!=NULL)
//    {
//        assert(tempNode->length>=0);
//        len+= tempNode->length;
//        tempNode=tempNode->next;
//    }
//    return len;
//}
//
//RLEListResult RLEListRemove(RLEList list, int index){
//    //go over each node, if index is between index of start of node and index end of node start dpa A
//    //else, remove node length from index, go to next and start from the start
//    //if arrive at null node, index not in list, return
//    //if removing index within a node that's 1 char long, remove whole node and see if the nodes on each side are not the same
//    const int MIN_NODE_LENGTH=1;
//    if(list==NULL)
//    {
//        assert(RLEListSize(list)==-1);
//        return RLE_LIST_NULL_ARGUMENT;
//    }
//
//    if(index<0 || index>=RLEListSize(list))
//    {
//        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
//    }
//    // printf("%d\n",index);
//    // printf("%d\n",RLEListSize(list));
//    RLEList currentNode=list;
//    RLEList previousNode = NULL;
//    while(currentNode!=NULL)
//    {
//        assert(currentNode->length>=0);
//        assert(index>=0);
//        if(currentNode->length>index)
//        {
//            //if made it into this loop, the char we want to remove is within the current node :)
//            if(currentNode->length==MIN_NODE_LENGTH)
//            {
//                return removeNode(previousNode,currentNode,list);
//            }
//            if(currentNode->length==0)
//            {
//                printf("aaaaaaa");
//                return RLE_LIST_ERROR;
//            }
//            else
//            {
//                currentNode->length--;
//                return RLE_LIST_SUCCESS;
//            }
//        }
//        index-=currentNode->length;
//        previousNode=currentNode;
//        currentNode=currentNode->next;
//    }
//    assert(NULL);//we arent supposed to arrive here, all edge cases should be taken care of
//    return RLE_LIST_INDEX_OUT_OF_BOUNDS;
//}
//
//char RLEListGet(RLEList list, int index, RLEListResult *result)
//{
//    if(list==NULL)
//    {
//        if(result!=NULL)
//        {
//            *result = RLE_LIST_NULL_ARGUMENT;
//        }
//        return '\0';
//    }
//    if(index<0 || index>=RLEListSize(list))
//    {
//        if(result!=NULL)
//        {
//            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
//        }
//        return '\0';
//    }
//    RLEList currentNode = list;
//    int currentNodeLength;
//    while(currentNode!=NULL)
//    {
//        currentNodeLength=currentNode->length;
//        assert(currentNodeLength>=0);
//        if(index<currentNodeLength)
//        {
//            if(result!=NULL)
//            {
//                *result = RLE_LIST_SUCCESS;
//            }
//            return currentNode->val;
//        }
//        index-=currentNodeLength;
//        assert(index>=0);
//        currentNode=currentNode->next;
//    }
//    assert(NULL);//we arent supposed to arrive here, edge cases should have been taken care of
//    return '\0';
//
//}
//
//RLEListResult RLEListMap(RLEList list, MapFunction map_function)
//{
//    if(list==NULL)
//    {
//        return RLE_LIST_NULL_ARGUMENT;
//    }
//    RLEList currentNode = list;
//    assert(currentNode!=NULL);
//    currentNode->val=map_function(currentNode->val);
//    RLEList previousNode=currentNode;
//    currentNode = currentNode->next;
//    while(currentNode!=NULL)
//    {
//        assert(currentNode!=NULL&&previousNode!=NULL);
//        currentNode->val = map_function(currentNode->val);
//        if(currentNode->val==previousNode->val)
//        {
//            previousNode->length+=currentNode->length;
//            currentNode=currentNode->next;
//            free(previousNode->next);
//            previousNode->next=currentNode;
//
//        }
//        else
//        {
//            previousNode=currentNode;
//            currentNode=currentNode->next;
//        }
//    }
//    return RLE_LIST_SUCCESS;
//}
//
//
//char* RLEListExportToString(RLEList list, RLEListResult* result)
//{
//    const int CHAR_TO_STRING = 3;
//    if(list==NULL)
//    {
//        *result=RLE_LIST_NULL_ARGUMENT;
//        return NULL;
//    }
//    //every char in word adds at max CHAR_TO_STRING=3 spaces to finalString "val,length,\n"
//    //the +1 is for the '\0' in the end of finalString so that it is considered a String according to C rules
//    char* finalString = malloc(CHAR_TO_STRING*RLEListSize(list)+1);
//    if(finalString==NULL)
//    {
//        *result=RLE_LIST_OUT_OF_MEMORY;
//        return NULL;
//    }
//    finalString="";
//    RLEList tmp=list->next;
//    for(int i=0 ;list!=NULL&&i<=(CHAR_TO_STRING*RLEListSize(list));list=list->next)
//    {
//        finalString[i]=(char)list->value;
//        finalString[++i]=(char)list->length;
//        finalString[++i]='\n';
//        i++;
//    }
//
//    list=tmp;
//    *result=RLE_LIST_SUCCESS;
//    return finalString;
//}
//

