#include "RLEList.h"
#include <assert.h>
#include <stdlib.h>

struct RLEList_t
{
    //TODO: implement
    char val;
    int length;
    RLEList next;
};

RLEListResult removeNode(RLEList previousNode, RLEList currentNode, RLEList list)
{
    /*edge case I- first node shall be removed*/
    if(previousNode==NULL)
    {
        list = list->next;
        assert(currentNode!=NULL);
        free(currentNode);
        currentNode=list;
        return RLE_LIST_SUCCESS;
    }

    /*edge case II- last node shall be removed*/
    if(currentNode->next==NULL)
    {
        assert(currentNode!=NULL);
        free(currentNode);
        return RLE_LIST_SUCCESS;
    }

    /*edge case III- node before and after have same value*/
    if(currentNode->next->val==previousNode->val)
    {
        previousNode->length+=currentNode->next->length;
        previousNode->next=currentNode->next->next;
        RLEList todelete = currentNode->next;
        free(todelete);
        free(currentNode);
        return RLE_LIST_SUCCESS;
    }
    /*normal removal*/
    previousNode->next=currentNode->next;
    free(currentNode);
    return RLE_LIST_SUCCESS;
}
RLEList RLEListCreate()
{
    RLEList tmp=(RLEList)malloc(sizeof(struct RLEList_t));
    if(tmp==NULL)
    {
        return NULL;
    }
    tmp->next=NULL;
    tmp->length=0;
    tmp->val=0;
    return tmp;
}

void RLEListDestroy(RLEList list)
{
    while (list)
    {
        RLEList toDelete = list;
        list=list->next;
        assert(toDelete!=NULL);
        free(toDelete);
    }
    
}
RLEListResult RLEListAppend(RLEList list, char value)
{   
    if(list==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(list->val==0)
    {
        list->val = value;
        list->length = 1;
        return RLE_LIST_SUCCESS;
    }
    RLEList lastNode = list;
    assert(list->val!=0);
    while(lastNode->next!=NULL)
    {
        lastNode = lastNode->next;
    }
    if(lastNode->val==value)
    {
        lastNode->length+=1;
        return RLE_LIST_SUCCESS;
    }
    RLEList newNode = RLEListCreate();
    if(newNode==NULL)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    newNode->val = value;
    newNode->length = 1;
    lastNode->next = newNode;
    return RLE_LIST_SUCCESS;
}


int RLEListSize(RLEList va_list)
{
    if(va_list==NULL)
    {
        return -1;
    }
    assert(va_list);
    int len = 0;
    RLEList tempNode = va_list;

    while(tempNode!=NULL)
    {
        assert(tempNode->length>=0);
        len+= tempNode->length;
        tempNode=tempNode->next;
    }
    return len;
}

RLEListResult RLEListRemove(RLEList list, int index){
    //go over each node, if index is between index of start of node and index end of node start dpa A
    //else, remove node length from index, go to next and start from the start
    //if arrive at null node, index not in list, return 
    //if removing index within a node that's 1 char long, remove whole node and see if the nodes on each side are not the same
    const int MIN_NODE_LENGTH=1;
    if(list==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(index<0 || index>=RLEListSize(list))
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList currentNode=list;
    RLEList previousNode = NULL;
    while(currentNode!=NULL)
    {
        assert(currentNode->length>0);
        assert(index>=0);
        if(currentNode->length>index)
        {
            //if made it into this loop, the char we want to remove is within the current node :)
            if(currentNode->length==MIN_NODE_LENGTH)
            {
                return removeNode(previousNode,currentNode,list);
            }
            else
            {
                currentNode->length--;
                return RLE_LIST_SUCCESS;
            }
        }
        index-=currentNode->length;
        previousNode=currentNode;
        currentNode=currentNode->next;
    }
    assert(NULL);//we arent supposed to arrive here, all edge cases should be taken care of
    return RLE_LIST_INDEX_OUT_OF_BOUNDS;
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
    if(index<0 || index>=RLEListSize(list))
    {
        if(result!=NULL)
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return '\0';
    }
    RLEList currentNode = list;
    int currentNodeLength;
    while(currentNode!=NULL)
    {
        currentNodeLength=currentNode->length;
        assert(currentNodeLength>=0);
        if(index<currentNodeLength)
        {
            if(result!=NULL)
            {
                *result = RLE_LIST_SUCCESS;
            }
            return currentNode->val;
        }
        index-=currentNodeLength;
        assert(index>=0);
        currentNode=currentNode->next;
    }
    assert(NULL);//we arent supposed to arrive here, edge cases should have been taken care of
    return 0;

}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if(list==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList currentNode = list;
    assert(currentNode!=NULL);
    currentNode->val=map_function(currentNode->val);
    RLEList previousNode=currentNode;
    currentNode = currentNode->next;
    while(currentNode!=NULL)
    {
        assert(currentNode!=NULL&&previousNode!=NULL);
        currentNode->val = map_function(currentNode->val);
        if(currentNode->val==previousNode->val)
        {
            previousNode->length+=currentNode->length;
            currentNode=currentNode->next;
            free(previousNode->next);
            previousNode->next=currentNode;

        }
        else
        {
            previousNode=currentNode;
            currentNode=currentNode->next;
        }
    }
    return RLE_LIST_SUCCESS;
}


char* RLEListExportToString(RLEList list, RLEListResult* result)
{   
    const int CHAR_TO_STRING = 3;
    if(list==NULL)
    {
        *result=RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    //every char in word adds at max CHAR_TO_STRING=3 spaces to finalString "val,length,\n"
    //the +1 is for the '\0' in the end of finalString so that it is considered a String according to C rules
    char* finalString = malloc(CHAR_TO_STRING*RLEListSize(list)+1); 
    if(finalString==NULL)
    {
        *result=RLE_LIST_OUT_OF_MEMORY;
        return NULL;
    }
    finalString=""; 
    RLEList tmp=list; 
    for(int i=0 ;list!=NULL&&i<=(CHAR_TO_STRING*RLEListSize(list));list=list->next)
    {
        finalString[i]=(char)list->val;
        finalString[++i]=(char)list->length;
        finalString[++i]='\n';
        i++;
    }    

    list=tmp;
    *result=RLE_LIST_SUCCESS;
    return finalString;
}


