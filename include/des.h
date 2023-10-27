#pragma once
#ifndef _DES_H_
#define _DES_H_

#include <stdint.h>

/**
 * Key Schedule Algorithm
 *
 * This function produces 16 round keys
 * based on the provided input key.
 *
 * @param out Pointer to a pre-allocated memory space
 *            for storing generated round keys.
 * @param in Input key.
 */
void DES_key_schedule(uint64_t *out, uint64_t in);

#endif // !_DES_H_
