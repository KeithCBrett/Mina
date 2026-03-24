# Minimum required version of cmake needed to build project
cmake_minimum_required(VERSION 4.1.2)

# Name of project for future reference
project(mina LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
)
set(CMAKE_AUTORCC ON)

# Declare a QML (Qt) module
qt_add_qml_module(mina
	URI mina
	QML_FILES
		src/QML/Main.qml
		src/QML/DropdownMenu.qml
		src/QML/AppearanceButton.qml
		src/QML/HelpButton.qml
		src/QML/HelpMenu.qml
		src/QML/AppearanceMenu.qml
		src/QML/HomeButton.qml
		src/QML/AboutButton.qml
		src/QML/AboutMenu.qml
		src/QML/BrowseButton.qml
		src/QML/BrowsePage.qml
	RESOURCES
		src/QML/images/pallete.png
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
		Qt6::Charts
		Qt6::Widgets
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
