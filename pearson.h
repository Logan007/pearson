#if defined (__SSE4_2__)
#include <immintrin.h>
#endif


void pearson_hash_256 (uint8_t *out, const uint8_t *in, size_t len);

void pearson_hash_128 (uint8_t *out, const uint8_t *in, size_t len);

uint32_t pearson_hash_32 (const uint8_t *in, size_t len, uint32_t hash);
