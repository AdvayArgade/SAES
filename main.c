#include <stdio.h>
#include <stdlib.h>
#include "./bitset.h"
#define fori(n) for(int i = 0; i<n; i++)

Bitset* key;
Bitset* keys[3];
unsigned short rcons[2] = {128, 48};

void initKey(int value){
    key =  malloc(sizeof(Bitset));
    init(key, 16, value);
    keys[0] = key;
}

void generateKey(int index){
    Bitset* wl = getkmsbs(keys[index-1], 8);
    Bitset* wr = getklsbs(keys[index-1], 8);
    // printBitset(wl);
    printf("wr:\n");
    printBitset(wr);

    Bitset* wlCurr = malloc(sizeof(Bitset));
    init(wlCurr, 8, wl->bits ^ rcons[index-1]);
    swapNibbles(wr);
    printf("After rotate:\n");
    printBitset(wr);

    wr = subByte(wr);
    printf("After substitute:\n");
    printBitset(wr);

    wlCurr->bits = wlCurr->bits ^ wr->bits;
    printf("After exor with wl:\n");
    printBitset(wlCurr);
    //========= left byte generated

    //======== right byte generation
    Bitset* wrCurr = malloc(sizeof(Bitset));
    init(wrCurr, 8, wlCurr->bits ^ getklsbs(keys[index-1], 8)->bits);
    printf("Right byte:\n");
    printBitset(wrCurr);

    //concat
    keys[index] = concat(wlCurr, wrCurr);
    printf("Key %d\n", index);
    printBitset(keys[index]);

}

void generateKeys(){
    fori(2) {
        generateKey(i+1);
    }
}

void printKeys(){
    fori(3){
        printBitset(keys[i]);
    }
}

int main(){
    initKey(19189);
    generateKeys();
    printKeys();
}