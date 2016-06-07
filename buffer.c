#include "buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>

typedef struct Buffer_s 
{
	int mCapacity;
	int mSize;

	int mFront;
	int mRear;

	byte* mBuf;
}Buffer_t;

#ifndef MIN
#define MIN(x, y)		(x > y)?(y):(x)
#endif

Buffer Buffer_Create(int capacity) 
{
	Buffer buffer = (Buffer)malloc(sizeof(Buffer_t) + sizeof(byte) * capacity);

	buffer->mCapacity = capacity;
	buffer->mSize  = 0;
	buffer->mFront = 0;
	buffer->mRear  = 0;
	buffer->mBuf   = (byte*)(buffer + 1);

	return buffer;
}

void Buffer_Delete(Buffer buffer)
{
	if(buffer != NULL)
		free(buffer);
} 

int Buffer_Write(Buffer buffer, const byte* data, int len)
{
	int writeSize;

	if(buffer == NULL)
		return -1;

	if(data == NULL || len < 1)
		return -2;

	if((buffer->mCapacity - buffer->mSize) < len)
	{
		fprintf(stderr, "Insufficient space to store : len %d / remain %d\n", len, (buffer->mCapacity - buffer->mSize));
		return -3; 
	}

	writeSize = buffer->mCapacity - buffer->mRear;
	if(writeSize < len)
	{
		memcpy(&buffer->mBuf[buffer->mRear], data, writeSize);
		memcpy(&buffer->mBuf[0], data + writeSize, len - writeSize);
		buffer->mRear = len - writeSize;
	}
	else
	{
		memcpy(&buffer->mBuf[buffer->mRear], data, len);
		buffer->mRear += len;
	}

	buffer->mSize += len;

	return len;
}

int Buffer_Read(Buffer buffer, byte* data, int len) 
{
	int readSize;

	if(buffer == NULL)
		return -1;

	if(data == NULL || len < 1)
		return -2;

	if(buffer->mSize < len)
	{
		fprintf(stderr, "Insufficient buffer : len %d / buffered %d\n", len, buffer->mSize);
		return -3; 
	}
	
	readSize = buffer->mCapacity - buffer->mFront;
	if(readSize < len)
	{
		memcpy(data, &buffer->mBuf[buffer->mFront], readSize);
		memcpy(data + readSize, &buffer->mBuf[0], len - readSize);
		buffer->mFront = len - readSize;
	}
	else
	{
		memcpy(data, &buffer->mBuf[buffer->mFront], len);
		buffer->mFront += len;
	}

	buffer->mSize -= len;

	return len;
}

int Buffer_AvailableData(Buffer buffer)
{
	if(buffer == NULL)
		return -1;

	return buffer->mSize;
}

int Buffer_AvailableSpace(Buffer buffer)
{
	if(buffer == NULL)
		return -1;

	return (buffer->mCapacity - buffer->mSize);
}

int Buffer_Flush(Buffer buffer)
{
	if(buffer == NULL)
		return -1;

	buffer->mSize  = 0;
	buffer->mFront = 0;
	buffer->mRear  = 0;
	
	return 0;
}


#define TEST_MAIN
#ifdef TEST_MAIN
int main()
{
	int  ii, ret;
	byte buf[1024];

	Buffer buffer = Buffer_Create(10);

	for(ii = 0; ii < 12; ii++)
		buf[ii] = ii;

	printf("#1. try write 12 len\n");
	ret = Buffer_Write(buffer, buf, 12);
	if(ret < 0)
		printf("Failed to write !\n");
	else
		printf("success to write !\n");

	printf("#2. try write 10 len\n");
	ret = Buffer_Write(buffer, buf, 10);
	if(ret < 0)
		printf("Failed to write !\n");
	else
		printf("success to write !\n");
	
	ret = Buffer_Read(buffer, buf, 5);
	if(ret < 0)
		printf("Failed to read !\n");
	else
		printf("success to read !\n");

		
	return 0;
}
#endif
