/*
* 
*/

#include "memory.h"

#ifdef PART_2 // see assignment_part.h


Memory::Memory(sc_module_name name, char* memInitFilename) : sc_module(name)
{	
	memFilename = memInitFilename;

	unsigned int initData;
	unsigned int initLocation;

	// initialize memory to 0
	for (int i = 0; i < MEM_SIZE; i++) { memData[i] = 0; }

	// initialize memory contents from file
	ifstream ifs(memFilename, ifstream::in);

	//check if able to read memory file
	if (!ifs.good()) {
		cout << "Warning: Could not open memory initialization file: " << memFilename << "." << endl;
		cout << "Memory contents initialized to all 0s." << endl << endl;
		cout << flush;
	}

	initLocation = 0;

	//read memory file into memData memory array.
	while ((ifs >> initData) && initLocation < MEM_SIZE) {
		memData[initLocation] = initData;
		initLocation++;
	}

	memRTL = new MEMORY_RTL("MEMORY_RTL_0", memData);

	SC_THREAD(oscillator);

	ifs.close();
}


bool Memory::Write(unsigned int addr, unsigned int data) // write interface
{
	cout << "\nWriting...\n";
	// make sure the address is valid
	if (addr >= MEM_SIZE) 
	{ 
		Wen.write(SC_LOGIC_0); // disable writing since addr invalid
		return false; 
	}

	Wen.write(SC_LOGIC_1);
	DataIn.write(data);
	Addr.write(addr);

	// these aren't up-to-date values, need to print after next posedge of clk
	cout << "Wen: " << Wen.read() << endl;
	cout << data << endl;
	cout << "DataIn: " << DataIn.read() << endl;
	cout << addr << endl;
	cout << "Addr: " << Addr.read() << endl;

	// write data to output file
	/*
	ofstream outputFile;
	outputFile.open("output.txt");
	outputFile << memData[addr];
	outputFile.close();
	*/
	return true;
}

bool Memory::Read(unsigned int addr, unsigned int& data) // read interface
{
	cout << "\nReading...\n";
	cout << "Intended addr: " << addr << endl;

	// make sure the address is valid
	if (addr >= MEM_SIZE) 
	{ 
		Ren.write(SC_LOGIC_0); // disable reading since addr invalid
		return false; 
	}
	data = memData[addr];
	cout << "Intended data: " << data << endl;

	Ren.write(SC_LOGIC_1);
	Addr.write(addr);

	// these aren't up-to-date values, need to print after next posedge of clk
	cout << "Ren: " << Ren.read() << endl;
	cout << "DataIn: " << DataIn.read() << endl;
	cout << "Addr: " << Addr.read() << endl;

	return true;
}

void Memory::oscillator()
{
	while (1)
	{
		Clk.write(SC_LOGIC_0);
		wait(2, SC_NS);
		Clk.write(SC_LOGIC_1);
		wait(2, SC_NS);
	}
}

// prints memData up to desired index (default to MEM_SIZE);
void Memory::printMemData(int endIndex)
{
	for (int i = 0; i < endIndex - 1; i++)
	{
		cout << "Index " << i << ": " << memData[i] << endl;
	}
}

#endif // memory for PART_2