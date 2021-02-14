#ifndef MEMORY_RTL_H
#define MEMORY_RTL_H

#include "simple_mem_if.h"

class MEMORY_RTL : public sc_module
{
public:
	// inputs
	sc_in< sc_logic > Clk;
	sc_in< sc_logic > Ren, Wen;
	sc_in< sc_uint<32> > Addr;
	sc_in< sc_uint<32> > DataIn;

	// outputs
	sc_out< sc_uint<32> > DataOut;
	sc_out< sc_logic > Ack;

	unsigned int* memData;

	SC_HAS_PROCESS(MEMORY_RTL);

	MEMORY_RTL(sc_module_name name, unsigned int memData[]) : sc_module(name)
	{
		this->memData = memData;
		SC_METHOD(rtl);
		sensitive << Clk.pos();
	}

	void rtl(); // memory behaviors
};

#endif // MEMORY_RTL_H