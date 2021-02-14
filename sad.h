#ifndef SAD_H
#define SAD_H

#include <iomanip>
#include "memory.h"

class SAD : public sc_module
{
	// module ports
public:
	int i, v;
	unsigned int block, sad;
	sc_port<simple_mem_if> bus;

	SC_HAS_PROCESS(SAD);

	SAD(sc_module_name name) : sc_module(name)
	{
		this->block = 0;
		this->sad = 0;
		this->i = 0;
		this->v = 0;
		SC_THREAD(sad_main);
	}

	void sad_main();
};

#endif // SAD_H