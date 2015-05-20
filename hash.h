#ifndef HASH_H_
#define HASH_H_

typedef struct {
    int size;
    int saturation;
    int **data;
} map;

unsigned int hash(unsigned int x);
unsigned int hash_max(unsigned int x, unsigned int max);
int map_init(map *m, int size);
int map_free(map *m);

#endif // HASH_H_
