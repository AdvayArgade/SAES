#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bitset.h"

bool plaintext[16] = {true, true, false, true, false, true, true, true, false, false, true, false, true, false, false, false};
bool key[16] = {false, true, false, false, true, false, true, false, true, true, true, true, false, true, false, true};
bool keys[3][16];

bool rcons[2][8] = {
    {true, false, false, false, false, false, false, false},
    {false, false, true, true, false, false, false, false}
};

void copyArray(bool a1[], bool a2[], int start, int end){
  for (int i = start; i < end; i++) {
    a1[i] = a2[i];
  }
}

void copyArrayOffset(bool a1[], bool a2[], int start, int end, int offset){
  for (int i = start; i < end; i++) {
    a1[i-offset] = a2[i];
  }
}

void printArray(bool arr[], int size){
    printf("\n");
  for (int i = 0; i < size; i++) {
    /* code */
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void swap(bool arr[], int arrSize){
    for (int i = 0; i < arrSize/2; ++i) {
        bool temp = arr[i];
        arr[i] = arr[i+arrSize/2];
        arr[i+arrSize/2] = temp;
    }
}

//bool* substitute(bool nibble[]){
//    int row = 2*nibble[0] + nibble[1];
//    int col = 2*nibble[2] + nibble[3];
//
//    int sub = sbox[row][col];
//    printf("sub: %d\n", sub);
//
//    bool* subArr = malloc(sizeof(bool)*4);
//    for (int i = 0; i < 4; i++)
//    {
//        subArr[i] = sub & 1 << (3-i);
//    }
//    return subArr;
//
//}

void exor(bool a1[], bool a2[], int size){
  for (int i = 0; i < size; i++) {
    /* code */
    a1[i] = a1[i] ^ a2[i];
  }
}

void generateKey(int index){
    bool wl[8], wr[8], w0[8], w1[8], nibble[4], *subVal;
    copyArray(w0, keys[index-1], 0, 8);
    copyArrayOffset(w1, keys[index-1], 8, 16, 8);
    printArray(w0, 8);
    printArray(w1, 8);

    exor(w0, rcons[index-1], 8);
    swap(w1, 8);
    copyArray(nibble, w1, 0, 4);
//    subVal = substitute(nibble);
}

void generateKeys(){
    copyArray(keys[0], key, 0, 16);

}

int main(){
//    generateKeys();
//    // printArray(keys[0], 16);
//    generateKey(1);
    Bitset* bitset = malloc(sizeof(Bitset));
    init(bitset, 4, 5);
    printBitset(bitset);
    substitute(bitset);
    printBitset(bitset);
    free(bitset);
    return 0;
}