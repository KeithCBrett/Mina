#include "action.h"
#include <cstdint>


int
main ()
{
	// Print to stdout name of project, version number, etc
	int err_synopsis = action::DisplaySynopsis ();
	if (err_synopsis == -1)
	{
		std::cout << "Error in function Di";
		std::cout << "splaySynopsis (returned -1)\n";
		return -1;
	}


	// Prompt user for net sales (used for EBITA calculation)
	uint64_t net_sales = action::GetNumberStdin
		("Enter net sales below:\n");
	if (net_sales == -1)
	{
		std::cout << "Error in function GetNumberStdin (net_sales)\n";
		return -1;
	}


	// Prompt user for cost of merchandise sold (used in EBITA)
	uint64_t cost_merch_sold = action::GetNumberStdin
		("Enter cost of merchandise sold below:\n");
	if (cost_merch_sold == -1)
	{
		std::cout << "Error in function GetNumbe";
		std::cout << "rStdin (cost_merch_sold)\n";
		return -1;
	}


	// Prompt user for selling, general, administrative cost (used in EBITA)
	uint64_t selling_general_admin = action::GetNumberStdin
		("Enter cost of selling, general, administrative below:\n");
	if (selling_general_admin == -1)
	{
		std::cout << "Error in function GetNumb";
		std::cout << "erStdin (cost_merch_sold)\n";
		return -1;
	}


	// Prompt user for depreciation (used in EBITA)
	uint64_t depreciation = action::GetNumberStdin
		("Enter cost of depreciation below:\n");
	if (depreciation == -1)
	{
		std::cout << "Error in function GetNumb";
		std::cout << "erStdin (depreciation)\n";
		return -1;
	}
	return 0;
}
