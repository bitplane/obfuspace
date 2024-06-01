#ifndef __OBFUSPACE_H__
#define __OBFUSPACE_H__

char whitespace[] = {32, 9, 10, 13};

// Crumb being 2 bits
#define WHITESPACE_TO_CRUMB(c) (((c) & 3) + (((c) & 4) >> 1))
#define CRUMB_TO_WHITESPACE(n) (whitespace[n])
#define GET_CRUMB(c, n) (((c) >> ((3 - (n)) * 2)) & 3)
#define SET_CRUMB(c, n) (((c) & 3) << ((3 - (n)) * 2))

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#   define GET_BYTE(i, n) (((i) >> ((3 - (n)) * 8)) & 0xFF)
#   define SET_BYTE(c, n) ((c) << ((3 - (n)) * 8))
#else
#   define GET_BYTE(i, n) (((i) >> ((n) * 8)) & 0xFF)
#   define SET_BYTE(c, n) ((c) << ((n) * 8))
#endif

#define WHITESPACE_TO_BYTE(i) ( \
    SET_CRUMB(WHITESPACE_TO_CRUMB(GET_BYTE(i, 0)), 0) | \
    SET_CRUMB(WHITESPACE_TO_CRUMB(GET_BYTE(i, 1)), 1) | \
    SET_CRUMB(WHITESPACE_TO_CRUMB(GET_BYTE(i, 2)), 2) | \
    SET_CRUMB(WHITESPACE_TO_CRUMB(GET_BYTE(i, 3)), 3) \
)

#define BYTE_TO_WHITESPACE(b) ( \
    SET_BYTE(CRUMB_TO_WHITESPACE(GET_CRUMB(b, 0)), 0) | \
    SET_BYTE(CRUMB_TO_WHITESPACE(GET_CRUMB(b, 1)), 1) | \
    SET_BYTE(CRUMB_TO_WHITESPACE(GET_CRUMB(b, 2)), 2) | \
    SET_BYTE(CRUMB_TO_WHITESPACE(GET_CRUMB(b, 3)), 3) \
)

//#define SANITY_MASK_8(c) (!(32 | 10 | 9 | 13))


#endif // __OBFUSPACE_H__
