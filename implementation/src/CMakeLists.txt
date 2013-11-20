cmake_minimum_required(VERSION 2.8)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
project(AlcoloBattle)

# Runtime
find_package(mlv_runtime REQUIRED)
include_directories(${MLV_RUNTIME_INCLUDE_DIRS})

# Listing the source files
set(LIBRARY_SOURCES
	Plugin.cpp
	ImplementationLibrary.h
	ImplementationLibrary.cpp
)
set(ACTION_SOURCES
	Component.cpp
	Component.h
	setEntityBooleanAction.h
	setEntityBooleanAction.cpp
)

set(SOURCES ${LIBRARY_SOURCES} ${ACTION_SOURCES} CMakeLists.txt)

# Project layout (for visual ide such as Visual Studio)
source_group(cmake FILES CMakeLists.txt)
source_group(sources\\actions FILES ${ACTION_SOURCES})
source_group(sources FILES ${LIBRARY_SOURCES})

# configuring the target
add_library(AlcoloBattle SHARED ${SOURCES})
target_link_libraries(AlcoloBattle
	mlv_allocator mlv_utils mlv_behavior
	mlv_simulation mlv_simulation_components mlv_simulation_configuration
	libprotobuf pthreads)
	
# Setting up the output
set_target_properties(AlcoloBattle PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/..
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR}/..
	DEBUG_POSTFIX _${PLATFORM_STR}-mt-gd
	RELEASE_POSTFIX _${PLATFORM_STR}-mt
)
	
	
	
