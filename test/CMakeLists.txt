# This CMakeLists.txt represents the CMake build directions for our unit testing
# apparatus. It links in librarys that the unit tests needs, namely Qt and curl
# which are required by some of the functions we test.

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


cmake_minimum_required(VERSION 4.1.2)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(kcbfin_TEST_SRC
  test_ebita.cpp
  test_stepSize.cpp
  test_firstYAxisNumber.cpp
  test_candleYPoint.cpp
  test_candleLength.cpp
  test_offsetStep.cpp
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
  Qt6::Core
  CURL::libcurl
  mina_lib
)
include(GoogleTest)
gtest_discover_tests(unit_tests)
