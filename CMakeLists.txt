# This CMakeLists.txt generates a make/ninja file to build our program. This
# file is responsible for generating a build system that links in gtest, curl,
# Qt/Qml, as well as our source files. We store most source code as a qt module
# and import it in Main.qml.

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

# Minimum required version of cmake needed to build project
cmake_minimum_required(VERSION 4.1.2)


# Name of project for future reference
project(mina LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# We need to import the Qt API for our GUI
find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Charts Widgets)
qt_standard_project_setup(REQUIRES 6.5)


# We also need to import curl for getting stock data from Alpaca API
find_package(CURL)


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
add_library(action STATIC ${mina_action_SRC} ${mina_action_INC})
add_library(calc STATIC ${mina_calc_SRC} ${mina_calc_INC})


# Tells CMake that action and calc need files located in include/
target_include_directories(action PUBLIC include/)
target_include_directories(calc PUBLIC include/)


# Name of executable generated
qt_add_executable(mina
	src/CPP/main.cpp
	src/CPP/CandlestickChart.cpp include/CandlestickChart.hpp
	src/CPP/YAxis.cpp            include/YAxis.hpp
	src/CPP/Crosshair.cpp        include/Crosshair.hpp
)

# C++ QML module stuff
set_target_properties(mina PROPERTIES
	WIN32_EXECUTABLE TRUE
	MACOSX_BUNDLE TRUE
)

set(CMAKE_AUTORCC ON)


# We will now declare a QML singleton to act as a global variable.
# https://doc.qt.io/qt-6/qml-singleton.html#accessing-singletons
set_source_files_properties(src/QML/ConstSingleton.qml
	PROPERTIES QT_QML_SINGLETON_TYPE TRUE
)

# We will also use a singleton to store the colors for our default color
# scheme.
set_source_files_properties(src/QML/ColorScheme.qml
	PROPERTIES QT_QML_SINGLETON_TYPE TRUE
)

# Declare a QML (Qt) module
qt_add_qml_module(mina
	URI mina_module
	QML_FILES
		src/QML/Main.qml
		src/QML/AboutButton.qml
		src/QML/AboutMenu.qml
		src/QML/AppearanceMenu.qml
		src/QML/BrowseButton.qml
		src/QML/BrowsePage.qml
		src/QML/ConstSingleton.qml
		src/QML/ColorScheme.qml
		src/QML/Cogwheel.qml
		src/QML/DropdownMenu.qml
		src/QML/DropdownButtonColumn.qml
		src/QML/HelpMenu.qml
		src/QML/HelpButton.qml
		src/QML/HomeButton.qml
		src/QML/HomePage.qml
		src/QML/ManualButton.qml
		src/QML/ManualPage.qml
		src/QML/StockList.qml
	RESOURCES
		src/QML/images/manual.png
		src/QML/images/setting.png
		src/QML/images/question.png
		src/QML/images/info.png
		src/QML/images/home.png
	SOURCES
		include/VersionNumberInfo.hpp
		src/CPP/VersionNumberInfo.cpp
)


target_link_libraries(mina
	PRIVATE
		action
		calc
		Qt6::Quick
		Qt6::Widgets
		Qt6::Core
		Qt6::Gui
		Qt6::Qml
		CURL::libcurl
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
configure_file(src/CPP/GetVersionNum.cpp.in
	${CMAKE_CURRENT_SOURCE_DIR}/src/CPP/GetVersionNum.cpp @ONLY
)
