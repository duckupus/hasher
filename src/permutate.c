#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "permutate.h"
#include "md5.h"


static int checkHash(char *x) {
	size_t i = 0;
	while(*x && i < MD5_HASH_LENGTH) {
		if(*x >= 'A' && *x <= 'F')
			*x |= 0x20; //convert to small letters
		if(*x < '0' || (*x > '9' && *x < 'a') || *x > 'f') {
			fprintf(stderr, "invalid hash\n");
			exit(-1);
			return 1;
		}
		x++;
		i++;
	}
	if(i == MD5_HASH_LENGTH) {
		*x = '\0'; //null out last part
	}
	return 0;
}

static int inc_str(char *s, size_t len, char min, char max) {
	size_t j = len;
	static int check = 0;
	if(s[len-1] == max) {
		for(j = len-1; j > 0 && s[j] == max; j--)
			s[j] = min;
		if(check && j == 0 && *s == max) {
			check = 0;
			return 1;
		}
		if(j == 0)
			check = 1;
		s[j]++;
	} else
		s[len-1]++;
	return 0;

}

static int hashcmp(const char *x, const char *y) { 
	/* 
	 * NOTE: This works like strcmp, just that it returns true if one string terminates early.
	 * This allows you to insert part of a hash.
	 * And still get a value for the corresponding hash
	 */
	while((*x && *y)) {
		if(*x != *y)
			break;
		x++;
		y++;
	}
	return (*x && *y);
}

static char *brute_char_md5(br_md5 ctx) {
	char guess[ctx.len];
	int correct = 0;
	char *val;
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
	if(!correct) return NULL;
	else {
		val = malloc(ctx.len*sizeof(char));
		*val = '\0';
		strcpy(val, guess);
		return val;
	}
}

int brute_md5(br_md5 ctx) {
	char *ans;
	clock_t start, end;
	double cpu_timing;
	size_t hours, minutes, seconds;
	checkHash(ctx.hash);
	printf("hash: %s\nmin: %d\nmax: %d\n", ctx.hash, ctx.min, ctx.max);
	start = clock();

	do {
		ctx.len++;
		printf("trying %lu chars...\n", ctx.len);
		ans = brute_char_md5(ctx);
	}while(ans == NULL);
	end = clock();
	cpu_timing = ((double)(end - start)) / CLOCKS_PER_SEC;
	seconds = cpu_timing;
	minutes = seconds / 60;
	hours = minutes / 60;
	minutes %= 60;
	seconds %= 60;
	printf("solved in %lu hours, %lu minutes, %lu seconds\nTotal time: %f\n",
			hours, minutes, seconds, cpu_timing);
	puts(ans);
	free(ans);
	return 0;
}
