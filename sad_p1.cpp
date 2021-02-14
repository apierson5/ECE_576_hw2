#include "sad.h"

#ifdef PART_1 // see assignment_part.h

// this function performs a simple manipulation of the command line
void cmd_separator(int length, char c)
{
	cout << std::setw(length) << std::setfill(c) << "\n";
}

void SAD::sad_main()
{
	// variables used for calculation of v
	unsigned int temp1;
	unsigned int temp2;

	for (block = 0; block < NUM_BLOCKS; block++)
	{
		sad = 0;
		for (i = 0; i < BLOCK_SIZE; i++)
		{
			// read first input into temp1
			if (!bus->Read((INPUT1_ADDR + (block * BLOCK_SIZE) + i), temp1))
			{
				cout << "Error: Invalid input 1 data!! \n";
				sc_stop();
			}
			cout << "INPUT 1 for SAD is: " << temp1 << "\n";

			// read second input into temp2
			if (!bus->Read((INPUT2_ADDR + (block * BLOCK_SIZE) + i), temp2))
			{
				cout << "Error: Invalid input 2 data!! \n";
				sc_stop();
			}
			cout << "INPUT 2 for SAD is: " << temp2 << "\n";

			// format command prompt
			cmd_separator(30, '-');

			// calculate sad
			v = temp1 - temp2;
			if (v < 0) v = -v;
			sad += v;
		}
		// write sad to file
		bus->Write(SAD_OUTPUT_ADDR + block, sad);

		cout << "SAD of block " << block << ": " << sad << endl;

		//format command prompt
		cmd_separator(60, '/');
	}
}

#endif // SAD for PART_1
