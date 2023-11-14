#pragma once
#ifndef _DES_UTILS_H_
#define _DES_UTILS_H_

#include <stdint.h>

/**
 * Transpose a 64x64 binary matrix.
 *
 * Generate a new matrix by swapping rows and columns based on the provided
 * matrix. The resulting matrix will have each row representing every nth bit of
 * each of the 64 blocks, and each column representing a distinct nth block.
 *
 * Note: The input and output buffer have to be preallocated by the caller.
 */
void DES_transpose(uint64_t *out, const uint64_t *in);

#endif // !_DES_UTILS_H_
