# This CMakeLists.txt defines which source files are apart of which libraries

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

# Below we create a list of all include files that are apart of the action
# library
set(mina_action_INC
	GetVersionNum.hpp
	action.hpp
)

# Do the same for library calc
set(mina_calc_INC
	Ebita.hpp
)

# Use helper function to get full path string to include files
PREPEND(mina_action_INC)
# Pass result to parent scope
set(mina_action_INC ${mina_action_INC} PARENT_SCOPE)

# Do the same for calc
PREPEND(mina_calc_INC)
set(mina_calc_INC ${mina_calc_INC} PARENT_SCOPE)
