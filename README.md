# Pearson Hashing
This repository contains a custom implementation of a "Fast Hashing of Variable-Length Text Strings" as suggested by Peter K. Pearson in The Communications of the ACM  Vol.33, No.  6 (June 1990), pp. 677-680 – the so called _Pearson Hashing_.

The [Wikipedia](https://en.wikipedia.org/wiki/Pearson_hashing) article contains a good description. Also, it links to a `.pdf` copy the original paper.

The underlying principle of this algorithm is easy to understand. Simplicity shines!

Note that this is not a cryptographicly secure hashing function, so it cannot unencryptedly be used to prove knowledge of a secret without needing to present that secret. But it is well suited for keying hash tables or to compress or expand given entropy of some byte-string to a different number of bytes or just as a checksum. Its design also allows to verify smaller parts of the hash value if required.

For use as checksum of to-be-encrypted data (including the checksum), it is noteworthy that the random permutation as repeating but also final step makes Pearson Hashing even a better choice than CRC – especially with a view to exclusive-ored stream ciphers.

# Thoughts

To get to output bit-widths beyond eight, Pearson describes an extension scheme which uses different starting values. Unfortunately, output will never contain the same two bytes in the various positions then – diminishing the codomain. This can be avoided by using a different permutation per position (output byte). In that case, there is no need for different starting values anymore.

Not to use another look-up-table for each and every output byte, this implementation changes every byte by a constant value  – different for each position – just before the look-up. If the table is random (and not arithmetically generated), it will seem to be a different permutation (from the new-index-look-up point of view). Remember, this is all modulo 256. After the look-up, the applied change could be reversed but it does not have to (gaining some speed).

Talking about speed, it seems to be feasible to use exclusive-or to change the to-be-looked-up index. A big advantage can be assumed for parallel implementation in regular C then (if not using SSE's vetorized bytewise operations).

In a hunt for more speed, a quick test using a linear congruential generator with full periodicity of 256 (trying to avoid the look-up in memory) resulted in ugly-distributed output. I am not able to see that my parameters were badly chosen and I stopped these test maybe too soon, but for now, this road does not want to be gone down.

This hasing function could easily be customized ot _tweaked_ (here, I would avoid the term _keyed_) just by changing the permutation along some provided tweak. A possible solution would be to use a tweak as seed for a pseudo-random number generator (maybe not a linear congruential one…) and repeatedly switch any two values in the table indicated by the pseduo-random number generator. Good thing here: The setup happens once _before_ use, it does not impact the actual hashing speedwise.

# Changes vis-à-vis the Original
… (draft: as above, also: SSE, maybe AVX to follow) …
