#include "memory_rtl.h"

void MEMORY_RTL::rtl()
{
	bool AddrIsValid = false;
	AddrIsValid = Addr.read() < MEM_SIZE;

	// provided address is valid
	if (AddrIsValid)
	{
		Ack.write(SC_LOGIC_1);

		// Ren is asserted
		if (Ren.read() == SC_LOGIC_1)
		{
			DataOut.write(memData[Addr.read()]);
		}

		// Wen is asserted
		if (Wen.read() == SC_LOGIC_1)
		{
			cout << "RTL WRITE: " << DataIn.read() << endl;
			cout << "TO ADDRESS: " << Addr.read() << endl;
			memData[Addr.read()] = DataIn.read();

		}
		return;
	}

	// ensures that Ack is always 0 in the event that Addr is not valid
	Ack.write(SC_LOGIC_0);
}