#include "bitset.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

unsigned short sbox[4][4] = {
        {9, 4, 10, 11},
        {13, 1, 8, 5},
        {6, 2, 0, 3},
        {12, 14, 15, 7}
};

void init(Bitset *bitset, unsigned short length, unsigned short value){
    bitset->bits = value;
    bitset->length = length;
}

void setBit(Bitset *bitset, int index){
    bitset->bits = bitset->bits | 1 << (bitset->length -index-1);
}

void resetBit(unsigned short *bitset, int index, int length){
    *bitset = *bitset & ~(1 << (length -index-1));
}

bool getBit(Bitset *bitset, int index){
    return bitset->bits & 1 << (bitset->length-index-1);
}

Bitset* getkmsbs(Bitset *bitset, int k){
    Bitset *newBitset = malloc(sizeof(Bitset));
    init(newBitset, k, 0);
    newBitset->bits = bitset->bits / (1 << (bitset->length-k));
    return newBitset;
}

Bitset* getklsbs(Bitset *bitset, int k){
    Bitset *newBitset = malloc(sizeof(Bitset));
    init(newBitset, k, 0);
    newBitset->bits = bitset->bits & ((1 << k) - 1);
    return newBitset;
}

void flip(unsigned short *bitset, int index, int length){
    *bitset = *bitset ^ 1 << (length-index-1);
}

void swapNibbles(Bitset *bitset){
    unsigned short mask = 15;   //lower 4 bits on
    unsigned short newBits = (bitset->bits & mask) << 4;
    newBits = newBits | (((bitset->bits)>>4)&mask);
    bitset->bits = newBits;
}

void substitute(Bitset *bitset){
    Bitset *row = getkmsbs(bitset, 2);
    Bitset *col = getklsbs(bitset, 2);
    bitset->bits = sbox[row->bits][col->bits];
    free(row);
    free(col);
}

Bitset* copyBitset(Bitset *bitset){
    Bitset *newBitset = malloc(sizeof(Bitset));
    init(newBitset, bitset->length, bitset->bits);
    return newBitset;
}

void printBitset(Bitset *bitset){
    printf("Length: %d\n", bitset->length);
    for (int i = 0; i < bitset->length; ++i) {
        printf("%d ", getBit(bitset, i));
    }
    printf("\n");
}