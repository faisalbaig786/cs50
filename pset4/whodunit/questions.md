1.  stdint.h is a header that declares sets of integer types (typedef and macros) with specified, fixed widths.
2.  These are various typedefs that set the exact amount of space you want to use. For example, uint8_t sets an
    integer type with an exact width of 8 and all are unsigned except for int32_t which is signed.
3.  BYTE is 1 bit, DWORD is 4 bits, LONG is 4 bits, and WORD is 2 bits.
4.  The first 2 bytes are 'B' and 'M' (ASCII).
5.  bfSize is the size of the bitmap file in bytes and biSize is the number of bytes in the structure/info header.
6.  If biHeight is negative then the bitmap is a top-down DIB and its origin is the upper-left corner,
    cannot be compressed.
7.  biBitCount specifies BMP color depth (bits per pixel).
8.  If the file can't be found/doesn't exist, then fopen will return NULL.
9.  The third argument to fread is always 1 because we're reading each file once.
10. The value assigned to padding is 3.
11. fseek moves the offset of a pointer and sets to a specific position in the file.
12. When used with fseek, specifies the offset to the current file position.
