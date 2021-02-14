#ifndef SIMPLE_MEM_IF_H
#define SIMPLE_MEM_IF_H

#include <systemc.h>
#include <math.h>
#include "assignment_part.h"

#define NUM_BLOCKS 1
#define BLOCK_SIZE 3
#define INPUT1_ADDR 0
#define INPUT2_ADDR 3
#define SAD_OUTPUT_ADDR 6
#define MEM_SIZE 10

class simple_mem_if : virtual public sc_interface
{
public:

	virtual bool Write(unsigned int addr, unsigned int data) = 0;
	virtual bool Read(unsigned int addr, unsigned int& data) = 0;
};

#endif // SIMPLE_MEM_IF_H