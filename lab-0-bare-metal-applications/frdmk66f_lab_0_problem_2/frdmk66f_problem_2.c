// Endianness: Little
// Cell Size: 8-byte
// Radix: Hex

// Extra (filled) bytes specified by ‘X’

struct struct1
{
    char x2;
    int x1;
};

// Answer struct1: XXXXXXAA AAAAAAAA

struct struct2
{
    short x2;
    int x1;
};

// Answer struct2 : XXXXAAAA AAAAAAAA

struct struct3
{
    int x1;
    short x2;
};

// Answer struct3: AAAAAAAA XXXXAAAA

struct struct4
{
    struct inner_struct
    {
        char x1;
        short x2;
        int x3;
    } inner_struct_1;

    // inner_struct: XXXXXXAA XXXXAAAA AAAAAAAA

    int x1;
};

// Answer struct4: XXXXXXAA XXXXAAAA AAAAAAAA AAAAAAAA