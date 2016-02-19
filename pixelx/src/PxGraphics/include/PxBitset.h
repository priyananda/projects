#ifndef _PIXELX_PxBitSet_H
#define _PIXELX_PxBitSet_H

#include "Common.h"

class PxBitSet
{
public:
	PxBitSet() : numBytes(0), bits(nullptr)
	{}
	~PxBitSet()
	{
		if(bits)
			delete [] bits;
		bits=nullptr;
	}

	bool Init(int numberOfBits);
	void ClearAll();
	void SetAll();

	void Clear(int bitNumber);
	void Set(int bitNumber);

	unsigned char IsSet(int bitNumber);

protected:
	int numBytes;	//size of bits array
	unsigned char * bits;
};
#endif

