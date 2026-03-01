# This CMakeLists.txt is responsible for defining which source files are
# apart of each library

# Copyright (C) 2026  Keith C Brett (KeithCBrett@gmail.com)

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

# Below we create a list of all source files that are apart of the action
# library
set(mina_action_SRC
	CPP/GetVersionNum.cpp
	CPP/CurlInit.cpp
	CPP/CurlWriter.cpp
)

# We also create a list for our calc library
set(mina_calc_SRC
	CPP/Ebita.cpp
)

# Use helper function to get full path string to source files
PREPEND(mina_action_SRC)
# Pass result to parent scope
set(mina_action_SRC ${mina_action_SRC} PARENT_SCOPE)

# Do the same for library calc
PREPEND(mina_calc_SRC)
set(mina_calc_SRC ${mina_calc_SRC} PARENT_SCOPE)
