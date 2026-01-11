# Minimum required version of cmake needed to build project
cmake_minimum_required(VERSION 4.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Name of project for future reference
project(kcbfin)

# Prepends subdirectory to files in a list
function(PREPEND var)
	# Declare empty storage list
	set(listVar "")
	foreach(f ${${var}})
		list(APPEND listVar "${CMAKE_CURRENT_SOURCE_DIR}/${f}")
	endforeach(f)
	set(${var} "${listVar}" PARENT_SCOPE)
endfunction(PREPEND)

# When build is finished; we will store executables in bin/ and libraries in
# lib/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/lib")

# The following will execute the CMakeLists.txt in each of the below directories
add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(test)

# Here we declare our libraries and their source files
add_library(action STATIC ${kcbfin_action_SRC} ${kcbfin_action_INC})
add_library(calc STATIC ${kcbfin_calc_SRC} ${kcbfin_calc_INC})

# Tells CMake that action and calc need files located in include/
target_include_directories(action PUBLIC include/)
target_include_directories(calc PUBLIC include/)

# Name of executable generated
add_executable(kcbfin)

# Link action library to main
target_link_libraries(kcbfin
	PRIVATE
		action
		calc
)

# Associate source files with project
target_sources(kcbfin
	PRIVATE
		src/main.cpp
)

# Below allows us to automate versioning via number of git commits
find_package(Git REQUIRED)
execute_process(
	COMMAND ${GIT_EXECUTABLE} rev-list --count main
	RESULT_VARIABLE result
	OUTPUT_VARIABLE num_commits
	ERROR_VARIABLE num_commits
)
if (result)
	message(FATAL_ERROR "Failed to get number of commits")
endif()
set(kcbfin_NUM_COMMITS ${num_commits})
configure_file(src/GetVersionNum.cpp.in
	${CMAKE_CURRENT_SOURCE_DIR}/src/GetVersionNum.cpp @ONLY
)
