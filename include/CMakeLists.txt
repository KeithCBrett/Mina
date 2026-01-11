# Below we create a list of all include files that are apart of the action
# library
set(kcbfin_action_INC
	ClearScreen.hpp
	DisplayResult.hpp
	DisplaySynopsis.hpp
	GetNumberStdin.hpp
	GetVersionNum.hpp
	action.hpp
)

# Do the same for library calc
set(kcbfin_calc_INC
	Ebita.hpp
)

# Use helper function to get full path string to include files
PREPEND(kcbfin_action_INC)
# Pass result to parent scope
set(kcbfin_action_INC ${kcbfin_action_INC} PARENT_SCOPE)

# Do the same for calc
PREPEND(kcbfin_calc_INC)
set(kcbfin_calc_INC ${kcbfin_calc_INC} PARENT_SCOPE)
