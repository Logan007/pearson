#include <stdio.h>
#include <stdint.h>

#include <time.h>
#include <stddef.h>

#include "pearson.h"

#define NUM_ITER	200000
#define PACKET_SIZE	1024

typedef int64_t timestamp_t;


timestamp_t get_timestamp(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
    return ts.tv_sec * 1000000000LL + ts.tv_nsec;
}


int main(int argc, char* argv[]) {

	uint8_t packet[PACKET_SIZE] = { 0 };
	uint32_t null_data  =   0;
	fprintf (stdout, "the two following lines should read the same:\n");
	fprintf (stdout, "0x00000000 --> 0xf285e1228df0347cd757198c649a95f9\n");
	fprintf (stdout, "0x");
	for (size_t j=0; j < 4; j++)
		fprintf (stdout, "%02x",packet[j]);
	fprintf (stdout, " --> 0x");
	pearson_hash_128 (packet, packet, 4);
	for (int j=0; j<16;j++)
		fprintf (stdout, "%02x",packet[j]);
	fprintf (stdout, "\n");

	fprintf (stdout, ".........................................%08x\n",
	                  pearson_hash_32((uint8_t*)&null_data,4));

	timestamp_t start, end;

	start = get_timestamp();
        for (uint32_t i=0; i < NUM_ITER; i++)
		*(uint32_t*)packet = pearson_hash_32 (packet, sizeof (packet));
	end = get_timestamp();
	fprintf (stderr, "throughput  32-bit hashing: %7.1f MB/s\n",
		          sizeof (packet) * (float)NUM_ITER / 1024.0 / 1024.0 /
			  (end - start) * 1000000000.0 );

	start = get_timestamp();
        for (uint32_t i=0; i < NUM_ITER; i++)
		pearson_hash_128 (packet, packet, sizeof (packet));
	end = get_timestamp();
	fprintf (stderr, "throughput 128-bit hashing: %7.1f MB/s\n",
		          sizeof (packet) * (float)NUM_ITER / 1024.0 / 1024.0 /
			  (end - start) * 1000000000.0 );
}
