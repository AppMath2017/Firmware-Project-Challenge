/*
 * The purpose of this code is to compute instantaneous velocity 
 * using the finite difference method.
 */
#include "include/RingBuffer.h"
#include <iostream>
#define MAX_SIZE 4097
struct R
{
     float v;
     int p;
};

R velocity ( RingBuffer<32, int> buffer, Block<int> block, int i, float posprev, float deltaT)
{
	/* Read a block */
	block = buffer.Read(MAX_SIZE);
	buffer.Skip(block.Length());
	// Compute velocity using FDM
	float v = (block.At(i)-posprev)/(deltaT);
	// store previous position
	posprev = block.At(i);
	return {v , posprev};
}