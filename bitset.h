#include <stdbool.h>
#ifndef SAES_BITSET_H
#define SAES_BITSET_H

typedef struct{
    unsigned short bits;
    unsigned short length;
}
Bitset;

void init(Bitset *bitset, unsigned short length, unsigned short value);
void setBit(Bitset *bitset, int index);
void resetBit(unsigned short *bitset, int index, int length);
bool getBit(Bitset *bitset, int index);
Bitset* getkmsbs(Bitset *bitset, int k);
Bitset* getklsbs(Bitset *bitset, int k);
void flip(unsigned short *bitset, int index, int length);
void swapNibbles(Bitset *bitset);
void substitute(Bitset *bitset);
Bitset* subByte(Bitset *bitset);
void swap2nd4thNibble(Bitset* bitset);
Bitset* concat(Bitset* left, Bitset* right);
Bitset* copyBitset(Bitset *bitset);
void printBitset(Bitset *bitset);

#endif //SAES_BITSET_H
