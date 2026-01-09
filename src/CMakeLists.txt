# Minimum required version of cmake needed to build project
cmake_minimum_required(VERSION 4.2)

# Name of project for future reference
project(kcbfin)

# Since we are using Gtest, we need >= C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# We need FetchContent to pull in Gtest dependency
include(FetchContent)

# Declare Gtest as dependency and pull it if missing
FetchContent_Declare(googletest
	URL https://github.com/google/googletest/archive/9156d4caac880b513264ecbe0aa4746a3fead3d7.zip
)

# For Windows based systems, prevents compiler/linker argument overide
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Allow main build to access dependency
FetchContent_MakeAvailable(googletest)

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
configure_file(get_version_num.cpp.in
	${CMAKE_CURRENT_SOURCE_DIR}/get_version_num.cpp @ONLY
)
add_library(kcbfin_version STATIC ${CMAKE_CURRENT_SOURCE_DIR}/get_version_num.cpp)

# Name of executable generated
add_executable(kcbfin)

# Associate source files with project
target_sources(kcbfin
	PRIVATE
		main.cpp
)

# Name of action library
add_library(action)

# Associate source files with library
target_sources(action
	PRIVATE
		action.cpp

	PUBLIC
		FILE_SET HEADERS
		FILES
			action.h
)

# Name of calc library
add_library(calc)

# Associate source files with library
target_sources(calc
	PRIVATE
		calc.cpp
	PUBLIC
		FILE_SET HEADERS
		FILES
			calc.h
)

target_link_libraries(action
	PRIVATE
		kcbfin_version
)

# Link action library to main
target_link_libraries(kcbfin
	PRIVATE
		kcbfin_version
		action
		calc
)

# The following snippet enables Gtest, adds unit test exe, etc
enable_testing()
add_executable(unit_tests
	unit_tests.cpp
)
target_link_libraries(unit_tests
	GTest::gtest_main
	action
	calc
	kcbfin_version
)
include(GoogleTest)
gtest_discover_tests(unit_tests)
