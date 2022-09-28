#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>
#include "permutate.h"
#include "md5.h"

static int inc_str(char *s, size_t len, char min, char max) {
	size_t j = len;
	size_t i;
	for(i = 0; i < len && s[i] == max; i++) {}
	if(i == len)
		return 1;
	if(s[len-1] == max) {
		for(j = len-1; j > 0 && s[j] == max; j--)
			s[j] = min;
		s[j]++;
		/*
		if(j == 0 && s[j-1] == max) {
			return 1;
		} */
	} else
		s[len-1]++;
	return 0;

}

static int hashcmp(const char *x, const char *y) { /* NOTE: This works like strcmp, just that it returns true if one string terminates early*/
	while((*x && *y)) {
		if(*x != *y)
			break;
		x++;
		y++;
	}
	return (*x && *y);
}

char *brute_md5(br_md5 ctx) {
	char *guess = malloc(ctx.len*sizeof(char));
	int correct = 0;
	for(size_t i = 0; i < ctx.len; i++) {
		guess[i] = ctx.min;
	}

	do {
		char *hash = compute_md5(guess, ctx.len);
		if(!hashcmp(ctx.hash, hash)) {
			correct = 1;
			break;
		}
		free(hash);
	} while(!inc_str(guess, ctx.len, ctx.min, ctx.max));
	if(correct) return guess;
	else {
		free(guess);
		return NULL;
	}
}
