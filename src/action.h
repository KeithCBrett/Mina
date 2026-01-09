#include <cstdint>
#include <iostream>


namespace action
{
	// Used for displaying name of project and version number
	int DisplaySynopsis ();

	// Used for getting security data from user
	uint64_t GetNumberStdin (std::string);

	// Used for clearing the screen of user inputs
	int ClearScreen ();

	// Used for displaying the results of calculations
	int DisplayResult (uint64_t inp_EBITA);
}
