#include <stdlib.h>
#include "hash.h"

#define MAPSIZE 1024

/*
 * Function returns an integer
 */
unsigned int hash(unsigned int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x);
    return x;
}

/*
 * Function returns an integer 0 <= x < max
 */
unsigned int hash_max(unsigned int x, unsigned int max) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x);
    return x % max;
}

int map_init(map *m, int size) {
    m->data = malloc( sizeof(int*) * size );
    return 0;
}

int map_free(map *m) {
    for( int i = 0; i < m->size; i++ ) {
        if( m->data[i] ) free( m->data[i] );
    }
    free( m->data );
    return 0;
}
