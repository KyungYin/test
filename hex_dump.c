#include "hex_dump.h"

#include <stdio.h>

#define ISPRINTABLE(c)  (((c)>=32 && (c)<=126) || ((c)>=161 && (c)<=254))

void HEX_Dump(const void* ptr, size_t size)
{
	size_t ii;
    size_t offset = 0;
    const unsigned char* data = (const unsigned char*)ptr;

    while(offset < size)
	{
        size_t remain = size - offset;

        printf("0x%04x  ", (unsigned)offset);
        if(remain > 16)
            remain = 16;

        for(ii = 0; ii < 16; ii++)
		{
            if(ii == 8) 
                printf(" ");

            if(offset + ii < size)
                printf("%02x ", data[offset + ii]);
            else
                printf("   ");
        }

        printf(" ");
        for(ii = 0; ii < remain; ii++)
		{
            if(ISPRINTABLE(data[offset + ii]))
                printf("%c", data[offset + ii]);
            else 
                printf(".");
        }
        printf("\n");

        offset += 16;
    }
}


#define TEST_MAIN
#ifdef  TEST_MAIN
unsigned char TEST_BIN[] = 
{	
	0x01, 0x02, 0x03, 0x04, 0x05,
	0x06, 0x07, 0x08, 0x09, 0x10,
	0x11, 0x12, 0x13, 0x14, 0x15,
	0x16, 0x17, 0x18, 0x19, 0x20,
};

int main(int argc, char* arv[])
{
	HEX_Dump(TEST_BIN, sizeof(TEST_BIN));
	return 0;
}
#endif
