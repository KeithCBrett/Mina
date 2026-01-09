#include "action.h"
#include "calc.h"
#include <cstdint>


int
main ()
{
	int error = 0;
	error = action::ClearScreen ();
	if (error == -1)
	{
		std::cout << "Error in function C";
		std::cout <<"learScreen (returned " << error <<")\n";
	}


	// Storage for financial calculations
	// Earnings before interest, taxes, and amoritization
	int ebita = 0;


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


	// Display result so far, clear screen, etc
	error = action::DisplayResult (ebita);


	// Prompt user for cost of merchandise sold (used in EBITA)
	uint64_t cost_merch_sold = action::GetNumberStdin
		("Enter cost of merchandise sold below:\n");
	if (cost_merch_sold == -1)
	{
		std::cout << "Error in function GetNumbe";
		std::cout << "rStdin (cost_merch_sold)\n";
		return -1;
	}


	error = action::DisplayResult (ebita);


	// Prompt user for selling, general, administrative cost (used in EBITA)
	uint64_t selling_general_admin = action::GetNumberStdin
		("Enter cost of selling, general, administrative below:\n");
	if (selling_general_admin == -1)
	{
		std::cout << "Error in function GetNumb";
		std::cout << "erStdin (cost_merch_sold)\n";
		return -1;
	}


	error = action::DisplayResult (ebita);


	// Prompt user for depreciation (used in EBITA)
	uint64_t depreciation = action::GetNumberStdin
		("Enter cost of depreciation below:\n");
	if (depreciation == -1)
	{
		std::cout << "Error in function GetNumb";
		std::cout << "erStdin (depreciation)\n";
		return -1;
	}


	error = action::DisplayResult (ebita);


	// Calculate earnings before taxes, interest, and amoritization. This
	// metric is good to know, but is also used in our NOPLAT calculation
	ebita = calc::Ebita
		(net_sales, cost_merch_sold,
		 selling_general_admin, depreciation);
	error = action::DisplayResult (ebita);
	if (error == -1)
	{
		std::cout << "Error in function Displa";
		std::cout << "yResult (returned " << error << ")\n";
		return -1;
	}
	return 0;
}
