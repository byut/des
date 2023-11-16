# Data Encryption Standard

A straightforward yet notably efficient implementation of the Data Encryption Standard (DES)
algorithm in C.

## Overview

To attain optimal efficiency, the algorithm incorporates several optimization techniques
proposed by Eli Biham in his paper titled "A Fast New DES Implementation in Software."

The core concept is to parallelize encryption operations. The quantity of
encryptions is limited by the hardware employed in the encryption process. Nonetheless,
leveraging widely available 64-bit processors enables the simultaneous execution of
64 encryptions. To achieve this, we can represent 64 data blocks as a transposed matrix of bits.
This approach facilitates encryption through straightforward bitwise operations, eliminating
the need for iterative processing through each bit 64 times.

Furthermore, we obviate the need for expensive permutations. Instead, we directly access
individual bits as if they were permuted. This eliminates the need for performing initial
permutations or generating subkeys for each round, resulting in significant time and resource
savings during the encryption process.

Another notable improvement in performance was achieved by employing logic gate operations
within S-boxes as opposed to the traditional approach of using lookup tables. Moreover, each S-box
already includes the P permutation and the E expansion in its 64-bit result. The implementation of
S-boxes within this algorithm is indeed noteworthy, boasting an impressive average gate count of 56.
The code, credited to Matthew Kwan, was obtained from this [website](https://darkside.com.au/bitslice/).
You can gain further insights by consulting his paper on the subject, titled "Reducing the Gate Count of
Bitslice DES." There is an even faster implementation, enhanced by an impressive 17%, that is utilized in
the John the Ripper password cracker.

## Performance

Overall, according to the set of simple tests, this algorithm attains an average speed of 143 MB/s.
It's worth noting that the testing environment was somewhat favorable, allowing the algorithm
to concentrate solely on encryption. In real-world scenarios, the efficiency may likely be
marginally slower.
