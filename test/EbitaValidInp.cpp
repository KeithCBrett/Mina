// Valid input unit test for function Ebita () of module calc

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
#include "unit_tests.hpp"


TEST (EbitaValidInp, CalcTests)
{
	EXPECT_EQ (9790, calc::Ebita (90837, 61054, 18348, 1645));
	EXPECT_EQ (7251, calc::Ebita (77349, 51352, 17053, 1693));
	EXPECT_EQ (4359, calc::Ebita (71288, 47298, 17846, 1785));
}
