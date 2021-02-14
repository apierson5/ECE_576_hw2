#include "sad.h"

#ifdef PART_2 // see assignment_part.h

// this function performs a simple manipulation of the command line
void cmd_separator(int length, char c)
{
	cout << std::setw(length) << std::setfill(c) << "\n";
}

void SAD::sad_main()
{
	cout << "sad_main executing" << endl;
	// variables used for calculation of v
	unsigned int dataA;
	unsigned int dataB;

	for (block = 0; block < NUM_BLOCKS; block++)
	{
		sad = 0;
		for (i = 0; i < BLOCK_SIZE; i++)
		{
			// 10ns for comparison (i < BLOCK_SIZE)
			wait(10, SC_NS);

			// read first input into dataA
			if (!bus->Read((INPUT1_ADDR + (block * BLOCK_SIZE) + i), dataA))
			{
				cout << "Error: Invalid input 1 data!! \n";
			}
			cout << "INPUT 1 for SAD is: " << dataA << "\n";

			// wait 10ns before performing next Read operation
			wait(10, SC_NS);

			// read second input into dataB
			if (!bus->Read((INPUT2_ADDR + (block * BLOCK_SIZE) + i), dataB))
			{
				cout << "Error: Invalid input 2 data!! \n";
			}
			cout << "INPUT 2 for SAD is: " << dataB << "\n";

			// wait 10ns after comparison
			wait(10, SC_NS);

			// format command prompt
			cmd_separator(30, '-');

			// calculate sad
			v = dataA - dataB;

			// wait 10ns for v to be calculated
			wait(10, SC_NS);

			if (v < 0)
			{
				// 10ns delay for checking the value of v
				wait(10, SC_NS);

				v = -v;
				// 10ns delay for taking abs. value of v
				wait(10, SC_NS);
			}

			sad += v;
			// net delay of 30ns before sad is updated

			// end of loop, increment i
			wait(10, SC_NS);
		}

		// delay for last comparison of (i < BLOCK_SIZE)
		wait(10, SC_NS);

		// write sad to file
		bus->Write(SAD_OUTPUT_ADDR + block, sad);
		wait(10, SC_NS);

		cout << "SAD of block " << block << ": " << sad << endl;

		// end of loop iteration: increment and assign block
		//wait(20, SC_NS);

		//format command prompt
		cmd_separator(60, '/');
	}
}

#endif // SAD for PART_2
