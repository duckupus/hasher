#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include "permutate.h"

static void help() {
	puts("Usage:");
	puts("hasher [OPTIONS]");
	puts("-h\t--help prints help message");
	puts("-H\t--hash [md5 hash] e.g. -H dd76adf401d8ed0cc5485230dc83758b");
	puts("-m\t--min [min value(inclusive)] e.g. -m 5");
	puts("-M\t--max [max value(inclusive)] e.g. -M 10");
	puts("-l\t--len [length of inputs to test(without null)] e.g. -l 10");
	puts("-a\t--alph sets min max value to A-z");
	puts("-A\t--anum sets min max value to all printable ascii values"); //according to ascii chart
}

static struct option long_options[] = {
	{"help", no_argument, NULL, 'h'},
	{"hash", required_argument, NULL, 'H'},
	{"min", required_argument, NULL, 'm'},
	{"max", required_argument, NULL, 'M'},
	{"alph", no_argument, NULL, 'a'},
	{"anum", no_argument, NULL, 'A'},
	{"len", required_argument, NULL, 'l'}
};


int main(int argc, char **argv) {
	int i;
	int hash, min, max;
	hash = 0;
	min = 0;
	max = 0;
	br_md5 ctx;
	ctx.len = 0;
	long srlen;
	while((i = getopt_long(argc, argv, "hH:m:M:aAl:", long_options, NULL)) != -1)  {
		switch(i) {
			case 'h':
				help();
				return 0;
				break;
			case 'H':
				srlen = strlen(optarg);
				ctx.hash = malloc(srlen*sizeof(char));
				ctx.hash[srlen] = 0x00;
				strncpy(ctx.hash, optarg, srlen);
				hash = 1;
				break;
			case 'm':
				ctx.min = atoi(optarg);
				min = 1;
				break;
			case 'M':
				ctx.max = atoi(optarg);
				max = 1;
				break;
			case 'a':
				ctx.min = 'A';
				min = 1;
				ctx.max = 'z';
				max = 1;
				break;
			case 'A':
				ctx.min = ' ';
				min = 1;
				ctx.max = '~';
				max = 1;
				break;
			case 'l':
				if(atoi(optarg) > 0) { //ctx.len gets incremented later
					ctx.len = atoi(optarg) - 1;
				}
		}
	}
	if(!hash) {
		help();
		exit(-1);
	}
	if(!min) ctx.min = 0x00;
	if(!max) ctx.max = 0xff;
	if(ctx.min >= ctx.max) {
		fprintf(stderr, "invalid values for min and max, try something else!\n");
		fprintf(stderr, "min: %d\n", ctx.min);
		fprintf(stderr, "max: %d\n", ctx.max);
	}

       	brute_md5(ctx);

	return 0;
}
