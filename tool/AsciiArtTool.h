//
// Created by omer.bahat on 11/24/22.
//

#ifndef EX1_ASCIIARTTOOL_H
#define EX1_ASCIIARTTOOL_H
#ifndef HW1_RLELIST_H
#include "../RLEList.h"
#endif

/**
 * asciiArtRead: Reads given file and compresses it via RLE technique
 * @param in_stream - FILE* type object which contains the image to be compressed
 * @return
 *      linked list of type RLEList which contains all characters in image
 */
RLEList asciiArtRead(FILE* in_stream);

/**
 * asciiArtPrint: Prints an image represented by a linked list of type RLEList to file
 * @param list - RLEList containing all characters of an image
 * @param out_stream - FILE* object which will contain printed image
 * @return
 *      RLE_LIST_NULL_ARGUMENT if one of the arguments is NULL
 *      RLE_LIST_SUCCESS in case of success
 */
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

/**
 * asciiArtPrintEncoded: Prints the linked list representation of the image (exported by RLEExportToString) of type RLEList to file
 * @param list - RLEList containing all characters of an image
 * @param out_stream - ILE* object which will contain exported string representation of the image
 * @return
 *      RLE_LIST_NULL_ARGUMENT if one of the arguments is NULL
 *      RLE_LIST_SUCCESS in case of success
 */
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);




#endif //EX1_ASCIIARTTOOL_H

