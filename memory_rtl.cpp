#include "memory_rtl.h"

void MEMORY_RTL::rtl()
{
	bool AddrIsValid = false;
	AddrIsValid = Addr.read() < MEM_SIZE;

	// ensures that Ack is always 0 unless Addr is valid
	Ack.write(SC_LOGIC_0);

	// provided address is valid
	if (AddrIsValid)
	{

		// Ren is asserted
		if (Ren.read() == SC_LOGIC_1)
		{
			cout << "DataOut written to with value: " << memData[Addr.read()] << endl;
			DataOut.write(memData[Addr.read()]);
		}

		// Wen is asserted
		if (Wen.read() == SC_LOGIC_1)
		{
			cout << "RTL WRITE: " << DataIn.read() << endl;
			cout << "TO ADDRESS: " << Addr.read() << endl;
			memData[Addr.read()] = DataIn.read();
		}

		Ack.write(SC_LOGIC_1);

		// wait 2 ns for Ack to be processed

		/*
		double initialTime = sc_time_stamp().to_seconds() * pow(10, 9);
		double elapsedTime = 0;
		while (elapsedTime < 2)
		{
			double currTime = sc_time_stamp().to_seconds() * pow(10, 9);
			elapsedTime = currTime - initialTime;
		}
		*/
		//Ack.write(SC_LOGIC_0);
	}

}