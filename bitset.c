#include "./bitset.h"
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

Bitset* subByte(Bitset* bitset){
    Bitset* sub0 = getkmsbs(bitset, 4);
    Bitset* sub1 = getklsbs(bitset, 4);
    substitute(sub0);
    substitute(sub1);
    return concat(sub0, sub1);
}

Bitset* concat(Bitset* left, Bitset* right){
    Bitset* combined = malloc(sizeof(Bitset));
    init(combined, left->length+right->length, left->bits);
    combined->bits = left->bits << right->length;
    combined->bits += right->bits;

    return combined;
}

Bitset* copyBitset(Bitset *bitset){
    Bitset *newBitset = malloc(sizeof(Bitset));
    init(newBitset, bitset->length, bitset->bits);
    return newBitset;
}

void swap2nd4thNibble(Bitset* bitset){
    //extract 4 lsbs
    unsigned short mask = 15;
    unsigned short fourthNibble = bitset->bits & mask;

    //extract 2nd nibble
    mask = 3840;
    unsigned short secondNibble = bitset->bits & mask;

    //shift
    fourthNibble = fourthNibble << 8;
    secondNibble = secondNibble >> 8;

    //clear 4 lsbs of bitset
    mask = 65520;
    bitset->bits = bitset->bits & mask;

    //OR with second nibble
    bitset->bits = bitset->bits | secondNibble;

    //clear 2nd nibble of bitset
    mask = 61695;
    bitset->bits = bitset->bits & mask;

    //OR with 4th nibble
    bitset->bits = bitset->bits | fourthNibble;
}

void mixColsEncrypt(Bitset* bitset){
    unsigned short M[2][2] = {{1, 4}, {4, 1}};
    unsigned short S[2][2];

    S[0][0] = getkmsbs(bitset, 4)->bits;
    S[1][1] = getklsbs(bitset, 4)->bits;

    S[1][0] = bitset->bits & 3840;
    S[0][1] = bitset->bits & 240;

}

unsigned short** matrixMul(unsigned short M[2][2], unsigned short S[2][2]){
    // unsigned short** result = malloc(sizeof(unsigned short*)*2);
    // for (int i = 0; i < 2; i++)
    // {
    //     result[i] = malloc(sizeof(unsigned short)*2);
    // }

    unsigned short result[2][2];
    
}

void printBitset(Bitset *bitset){
    printf("Length: %d\n", bitset->length);
    for (int i = 0; i < bitset->length; ++i) {
        printf("%d ", getBit(bitset, i));
    }
    printf("\n\n");
}