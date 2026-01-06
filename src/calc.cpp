#include "calc.h"


namespace calc {
	uint64_t Ebita (uint64_t inp_net_sales, uint64_t inp_cost_merch_sold,
			uint64_t inp_selling_general_admin,
			uint64_t inp_depreciation)
	{
		// None of our inputs should be zero. Return error if this is
		// the case
		if (inp_net_sales == 0 || inp_cost_merch_sold == 0
				|| inp_selling_general_admin == 0
				|| inp_depreciation == 0)
		{
			return -1;
		}


		return (inp_net_sales - inp_cost_merch_sold
				- inp_selling_general_admin - inp_depreciation);
	}
}
