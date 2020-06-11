#if defined (__SSE4_2__)
#include <immintrin.h>
#endif


void pearson_hash_128 (uint8_t *out, uint8_t *in, size_t len);

uint32_t pearson_hash_32 (uint8_t *in, size_t len);
