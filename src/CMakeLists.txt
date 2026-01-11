# Below we create a list of all source files that are apart of the action
# library
set(kcbfin_action_SRC
	ClearScreen.cpp
	DisplayResult.cpp
	DisplaySynopsis.cpp
	GetNumberStdin.cpp
	GetVersionNum.cpp
)

# We also create a list for our calc library
set(kcbfin_calc_SRC
	Ebita.cpp
)

# Use helper function to get full path string to source files
PREPEND(kcbfin_action_SRC)
# Pass result to parent scope
set(kcbfin_action_SRC ${kcbfin_action_SRC} PARENT_SCOPE)

# Do the same for library calc
PREPEND(kcbfin_calc_SRC)
set(kcbfin_calc_SRC ${kcbfin_calc_SRC} PARENT_SCOPE)
