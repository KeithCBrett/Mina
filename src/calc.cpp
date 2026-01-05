#include "calc.h"


namespace calc {
	uint64_t Ebita (uint64_t inp_net_sales, uint64_t inp_cost_merch_sold,
			uint64_t inp_selling_general_admin,
			uint64_t inp_depreciation)
	{
		return (inp_net_sales - inp_cost_merch_sold
				- inp_selling_general_admin - inp_depreciation);
	}
}
