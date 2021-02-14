#ifndef TOP_H
#define TOP_H

#include "sad.h"

// Top module to connect the components
class Top : public sc_module
{
public:
	Memory memory_0;
	SAD sad_0;

#ifdef PART_2
	sc_signal< sc_logic > s_clk, s_wen, s_ren, s_ack;
	sc_signal< sc_uint<32> > s_datain, s_dataout, s_addr;
#endif

public:
	Top(sc_module_name name, char* memInitFileName) : sc_module(name), memory_0("MEMORY_0", memInitFileName), sad_0("SAD_0")
	{
		sad_0.bus(memory_0);

#ifdef PART_2
		// inputs for memRTL
		memory_0.memRTL->Clk(s_clk);
		memory_0.memRTL->Ren(s_ren);
		memory_0.memRTL->Wen(s_wen);
		memory_0.memRTL->DataIn(s_datain);
		memory_0.memRTL->Addr(s_addr);

		// outputs for memRTL
		memory_0.memRTL->DataOut(s_dataout);
		memory_0.memRTL->Ack(s_ack);

		// inputs for memory_0 interface
		memory_0.Ack(s_ack);

		// outputs for memory_0 interface
		memory_0.Clk(s_clk);
		memory_0.Ren(s_ren);
		memory_0.Wen(s_wen);
		memory_0.DataIn(s_datain);
		memory_0.Addr(s_addr);

#endif
	}
};

#endif // TOP_H