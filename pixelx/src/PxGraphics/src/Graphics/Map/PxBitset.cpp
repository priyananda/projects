#include "PxBitSet.h"

bool PxBitSet::Init(int numberOfBits)
{
	//Delete any memory allocated to bits
	if(bits)
		delete [] bits;
	bits=nullptr;

	//Calculate size
	numBytes=(numberOfBits>>3)+1;

	//Create memory
	bits=new unsigned char[numBytes];
	if(!bits)
	{
		PxLog::LogMessage("Unable to allocate space for a PxBitSet of %d bits", numberOfBits);
		return false;
	}

	ClearAll();

	return true;
}

void PxBitSet::ClearAll()
{
	memset(bits, 0, numBytes);
}

void PxBitSet::SetAll()
{
	memset(bits, 0xFF, numBytes);
}

void PxBitSet::Clear(int bitNumber)
{
	bits[bitNumber>>3] &= ~(1<<(bitNumber & 7));
}

void PxBitSet::Set(int bitNumber)
{
	bits[bitNumber>>3] |= 1<<(bitNumber&7);
}

unsigned char PxBitSet::IsSet(int bitNumber)
{
	return bits[bitNumber>>3] & 1<<(bitNumber&7);
}

