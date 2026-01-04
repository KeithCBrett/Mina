#include "action.h"
#include <cstdint>


int
main ()
{
	// Print to stdout name of project, version number, etc
	int err_synopsis = action::DisplaySynopsis ();
	if (err_synopsis == -1)
	{
		std::cout << "Error in function DisplaySynopsis (returned -1)\n";
	}


	return 0;
}
