#ifndef __BUFFER_H_
#define __BUFFER_H_

typedef unsigned char byte;

typedef struct Buffer_s* Buffer;

Buffer Buffer_Create(int capacity);
void   Buffer_Delete(Buffer buffer);

int    Buffer_Write(Buffer buffer, const byte* data, int len);
int    Buffer_Read(Buffer buffer, byte* data, int len);

int    Buffer_AvailableData(Buffer buffer);
int    Buffer_AvailableSpace(Buffer buffer);

int    Buffer_Flush(Buffer buffer);

#endif // __BUFFER_H_
