// SPDX-License-Identifier: GPL-3.0-or-later
// mf-android — SHA-1 (FIPS 180-4), only used to identify the ROM.
#include "port_assets.h"

#include <string.h>

static uint32_t Rol(uint32_t v, int n)
{
    return (v << n) | (v >> (32 - n));
}

static void Block(uint32_t h[5], const uint8_t* p)
{
    uint32_t w[80];
    uint32_t a = h[0], b = h[1], c = h[2], d = h[3], e = h[4];

    for (int i = 0; i < 16; i++)
        w[i] = (uint32_t)p[i * 4] << 24 | (uint32_t)p[i * 4 + 1] << 16 | (uint32_t)p[i * 4 + 2] << 8 | p[i * 4 + 3];
    for (int i = 16; i < 80; i++)
        w[i] = Rol(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);

    for (int i = 0; i < 80; i++) {
        uint32_t f, k;
        if (i < 20) {
            f = (b & c) | (~b & d);
            k = 0x5A827999;
        } else if (i < 40) {
            f = b ^ c ^ d;
            k = 0x6ED9EBA1;
        } else if (i < 60) {
            f = (b & c) | (b & d) | (c & d);
            k = 0x8F1BBCDC;
        } else {
            f = b ^ c ^ d;
            k = 0xCA62C1D6;
        }
        const uint32_t t = Rol(a, 5) + f + e + k + w[i];
        e = d;
        d = c;
        c = Rol(b, 30);
        b = a;
        a = t;
    }
    h[0] += a;
    h[1] += b;
    h[2] += c;
    h[3] += d;
    h[4] += e;
}

void Port_Sha1(const void* data, size_t size, uint8_t out[20])
{
    uint32_t h[5] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 };
    const uint8_t* p = (const uint8_t*)data;
    uint8_t tail[128];
    size_t full = size & ~(size_t)63;
    size_t rest = size - full;
    const uint64_t bits = (uint64_t)size * 8;

    for (size_t i = 0; i < full; i += 64)
        Block(h, p + i);

    memset(tail, 0, sizeof(tail));
    memcpy(tail, p + full, rest);
    tail[rest] = 0x80;
    const size_t tailLen = (rest + 9 <= 64) ? 64 : 128;
    for (int i = 0; i < 8; i++)
        tail[tailLen - 1 - i] = (uint8_t)(bits >> (8 * i));
    Block(h, tail);
    if (tailLen == 128)
        Block(h, tail + 64);

    for (int i = 0; i < 5; i++) {
        out[i * 4] = (uint8_t)(h[i] >> 24);
        out[i * 4 + 1] = (uint8_t)(h[i] >> 16);
        out[i * 4 + 2] = (uint8_t)(h[i] >> 8);
        out[i * 4 + 3] = (uint8_t)h[i];
    }
}
