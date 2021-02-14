#include "memory.h"

#ifdef PART_1 // see assignment_part.h


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

	ifs.close();
}

bool Memory::Write(unsigned int addr, unsigned int data) // write interface
{
	if (addr >= MEM_SIZE) { return false; } //make sure the address is valid
	this->memData[addr] = data;

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
	if (addr >= MEM_SIZE) { return false; }
	data = this->memData[addr];
	
	return true;
}

void Memory::printMemData(int endIndex)
{
	for (int i = 0; i < endIndex; i++)
	{
		cout << "Index " << i << ": " << this->memData[i] << endl;
	}
}

#endif // memory for PART_1