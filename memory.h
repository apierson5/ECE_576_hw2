
#ifndef MEMORY_H
#define MEMORY_H

#include "simple_mem_if.h"
#include "memory_rtl.h"


class Memory : public sc_channel, public simple_mem_if
{
public:
	char* memFilename;
	unsigned int memData[MEM_SIZE];

#ifdef PART_2
	MEMORY_RTL* memRTL;

	// interface output signals that connect to MEMORY_RTL
	sc_out< sc_logic > Wen, Ren, Clk;
	sc_out< sc_uint<32> > DataIn, Addr;

#endif

public:
	SC_HAS_PROCESS(Memory);
	Memory(sc_module_name name, char* memInitFilename);

#ifdef PART_2
	// clock handler for part 2
	void oscillator();
#endif

	//using the interface	
	bool Write(unsigned int addr, unsigned int data);  //write interface
	bool Read(unsigned int addr, unsigned int& data);  //read interface

	void printMemData(int endIndex = MEM_SIZE); // prints memData up to desired index (default to MEM_SIZE)

};

#endif // MEMORY_H