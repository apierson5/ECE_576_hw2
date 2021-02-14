/*
* Author: Austin Pierson, Hector Garcia, Christian Garcia, Kaden Skow, Sofia Carreon
* Group: 4
* Date: February 14, 2021
* Course: ECE 576
* Description: This assignment is an introduction to modeling with SystemC.
* The assignment consists of creating an untimed SAD component and a mixed
* cycle-accurate and approximate-timed SAD model involving a memory component.
* The SAD component will compute values from memory. Memory values are obtained
* from an input file (specified by user through command line argument <see below>)
* 
* Usage: main memFileName
*/

#include <systemc.h>
#include "top.h"

int sc_main(int argc, char* argv[])
{
	Top* top_0;

	// argv[1] is the name of the file to read from
	top_0 = new Top("Top_0", argv[1]);

#ifdef PART_2
	// trace timed and cycle-accurate model
	sc_trace_file* fp;
	fp = sc_create_vcd_trace_file("vcd_trace");
	fp->set_time_unit(1, SC_NS);

	// add signals to trace
	sc_trace(fp, top_0->s_clk, "Clk");
	sc_trace(fp, top_0->s_ren, "Ren");
	sc_trace(fp, top_0->s_wen, "Wen");
	sc_trace(fp, top_0->s_addr, "Addr");
	sc_trace(fp, top_0->s_datain, "DataIn");
	sc_trace(fp, top_0->s_dataout, "DataOut");
	sc_trace(fp, top_0->s_ack, "Ack");

	// begin
	sc_start(200, SC_NS);
	sc_close_vcd_trace_file(fp);

	// display all of memory data to console
	top_0->memory_0.printMemData();
	return (0);
#endif
	
	// untimed model
	sc_start();
	top_0->memory_0.printMemData();

	return(0);
}
