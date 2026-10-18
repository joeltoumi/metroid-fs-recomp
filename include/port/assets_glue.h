#ifndef PORT_ASSETS_GLUE_H
#define PORT_ASSETS_GLUE_H

/*
 * mzm-android: runtime game data. The generated wrappers around the src/data files
 * (tools/port/gen_assets.py) describe where every array extracted from the
 * ROM lives; port/src/assets.c fills them from the player's ROM at startup.
 * Libc-free on purpose: it's included from game translation units.
 */

typedef struct PortAsset {
    unsigned char* dst;     /* first byte of the ROM data inside the array */
    unsigned int romOffset; /* offset in the cartridge image */
    unsigned int size;      /* bytes to copy */
    unsigned long arraySize;/* sizeof the whole array, for sanity checks */
} PortAsset;

void Port_RegisterAssets(PortAsset* assets, unsigned long count);

#endif /* PORT_ASSETS_GLUE_H */
