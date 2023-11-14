#pragma once
#ifndef _DES_CORE_H_
#define _DES_CORE_H_

#include <stdint.h>

/**
 * The DES Algorithm (Encryption)
 *
 * Performs 64 encryption operations simultaneously on a given set of
 * blocks utilizing the specified key sequence.
 *
 * The pointer to the output buffer may match the
 * pointer to the input buffer. Otherwise, it must be pre-allocated by the
 * caller.
 */
void DES_e(uint64_t *out, const uint64_t *in, const uint64_t *keys);

/**
 * The DES Algorithm (Decryption)
 *
 * Performs 64 decryption operations simultaneously on a given set of
 * blocks utilizing the specified key sequence.
 *
 * The pointer to the output buffer may match the
 * pointer to the input buffer. Otherwise, it must be pre-allocated by the
 * caller.
 */
void DES_d(uint64_t *out, const uint64_t *in, const uint64_t *keys);

#endif // !_DES_CORE_H_
