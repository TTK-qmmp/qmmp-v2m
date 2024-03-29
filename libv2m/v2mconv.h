#pragma once

// gives version deltas
int CheckV2MVersion(const unsigned char* inptr, const int inlen);

// converts V2M to newest version
void ConvertV2M(const unsigned char* inptr, const int inlen, unsigned char* * outptr, int* outlen);

extern const char * const v2mconv_errors[];
