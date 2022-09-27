#ifndef PERMUTATE_H
#define PERMUTATE_H

#include <stdio.h>

typedef struct {
	char *hash;
	size_t len;
	unsigned char max;
	unsigned char min;
} br_md5;

char *brute_md5(br_md5 ctx);

#endif /* PERMUTATE_H */
