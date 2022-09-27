#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "permutate.h"
#include "md5.h"

static int inc_str(char *s, size_t len, char min, char max) {
	size_t j = len;
	size_t i;
	if(s[len-1] == max) {
		for(j = len-1; j > 0 && s[j] == max; j--)
			s[j] = min;
		s[j]++;
	} else
		s[len-1]++;
	//printf("%s\n", s);
	for(i = 0; i < len && s[i] == max; i++) { }

	return (i == len);
}

char *brute_md5(br_md5 ctx) {
	if(ctx.min >= ctx.max) return (char *)-1; //error!

	char *guess = malloc(ctx.len*sizeof(char));
	for(size_t i = 0; i < ctx.len; i++) {
		guess[i] = ctx.min;
	}

	do {
		char *hash = compute_md5(guess, ctx.len);
		if(!strcmp(hash, ctx.hash)) {
			break;
		}
		free(hash);
	} while(!inc_str(guess, ctx.len, ctx.min, ctx.max));

	return guess;
}
