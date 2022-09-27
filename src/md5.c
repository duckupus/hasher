#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if defined(__APPLE__)
#  define COMMON_DIGEST_FOR_OPENSSL
#  include <CommonCrypto/CommonDigest.h>
#  define SHA1 CC_SHA1
#else
#include <openssl/md5.h>
#endif

#include "md5.h"

char *compute_md5(const char *str, unsigned int len) {
	MD5_CTX  ctx;
	unsigned char digest[16];
	char *hash = (char*)malloc(33);
	MD5_Init(&ctx);
	while(len > 512) {
		MD5_Update(&ctx, str, 512);
		len -= 512;
		str += 512;
	}
	MD5_Update(&ctx, str, len);
	MD5_Final(digest, &ctx);
	for (int n = 0; n < 16; ++n) {
		snprintf(&(hash[n*2]), 16*2, "%02x", (unsigned int)digest[n]);
	}
	return hash;
}
