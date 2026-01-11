// Ebita is used to calculated earnings before interest, taxes, and
// amoritization which in turn is used to calculate NOPLAT

// Copyright (C) 2026  Keith C Brett (KeithCBrett@gmail.com)

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#include "calc.hpp"


namespace calc
{
	uint64_t Ebita
		(uint64_t inp_net_sales, uint64_t inp_cost_merch_sold,
		 uint64_t inp_selling_general_admin, uint64_t inp_depreciation);
}
