cmake_minimum_required(VERSION 4.2)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(kcbfin_TEST_SRC
	EbitaInvalidInp.cpp
	EbitaValidInp.cpp
)

set(kcbfin_TEST_INC
	../include/unit_tests.hpp
)

PREPEND(kcbfin_TEST_SRC)

# Obtain GTest if it isn't already on the system
include(FetchContent)
FetchContent_Declare(googletest
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows based systems, prevents compiler/linker argument overide
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable GTest, create unit test exe, etc
enable_testing()
add_executable(unit_tests ${kcbfin_TEST_SRC} ${kcbfin_TEST_INC})
target_link_libraries(unit_tests
	GTest::gtest_main
	action
	calc
)
include(GoogleTest)
gtest_discover_tests(unit_tests)
