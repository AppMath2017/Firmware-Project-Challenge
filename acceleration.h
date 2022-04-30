/*
 * The purpose of this code is to compute instantaneous acceleration 
 * using the finite difference method.
 */
#include "include/RingBuffer.h"
#include "velocity.h"
#define MAX_SIZE 4097

struct R
{
     float v;
     int p;
};

struct ACC
{
     float a;
     float v;
};

ACC acceleration ( RingBuffer<32, int> buffer, Block<int> block, int i, float posprev, float deltaT, float veloprev)
{
	// Compute velocity 
	R result = velocity(buffer, block, i, posprev, deltaT);
	// Compute acceleration using FDM
	float a = (result.v - veloprev)/(deltaT);
	// store previous velocity
	veloprev = result.v;
	return {a , veloprev};
}