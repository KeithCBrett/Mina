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

# Link action library to main
target_link_libraries(kcbfin
	PRIVATE
		action
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
)
include(GoogleTest)
gtest_discover_tests(unit_tests)
