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
		return -1;
	}


	// Prompt user for net sales (used for EBITA calculation)
	uint64_t net_sales = action::GetNumberStdin ("Enter net sales below:\n");
	if (net_sales == -1)
	{
		std::cout << "Error in function GetNumberStdin (net_sales)\n";
		return -1;
	}


	// Prompt user for cost of merchandise sold (used in EBITA)
	uint64_t cost_merch_sold = action::GetNumberStdin ("Enter cost of merchandise sold below:\n");
	if (cost_merch_sold == -1)
	{
		std::cout << "Error in function GetNumberStdin (cost_merch_sold)\n";
		return -1;
	}
	return 0;
}
