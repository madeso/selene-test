cmake_minimum_required(VERSION 3.1.0)
set_property(GLOBAL PROPERTY USE_FOLDERS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(selene-test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(${APPLE})
	# disabling http://stackoverflow.com/questions/32626171/xcode-7-how-to-suppress-warning-overrides-a-member-function-but-is-not-marked
	# that apple-clang spews out for wx headers
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-inconsistent-missing-override")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
endif()

# compiler flags
if(${MSVC})
	ADD_DEFINITIONS(/D _CRT_SECURE_NO_WARNINGS)

	# character set to Not Set=ASCII/SBCS http://public.kitware.com/Bug/view.php?id=12189
	ADD_DEFINITIONS(/D _SBCS)
endif()

# force visual studio and the like to only have debug and release builds
if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES Debug Release)
	set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING "Reset the configurations to what we need" FORCE)
endif()

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

FILE(GLOB app_src_glob *.cc;*.h;*.inl)

FILE(GLOB lua_src_glob ${CMAKE_SOURCE_DIR}/external/lua-5.3.2/*.c)
FILE(GLOB lua_hdr_glob ${CMAKE_SOURCE_DIR}/external/lua-5.3.2/*.h)
set(lua_src ${lua_src_glob} ${lua_hdr_glob})

include_directories(${CMAKE_SOURCE_DIR}/external/lua-5.3.2/)
include_directories(${CMAKE_SOURCE_DIR}/external/selene/)

set(app_src ${app_src_glob} )

source_group("" FILES ${app_src})
source_group("lua" FILES ${lua_src})

add_executable(selene-test ${app_src} ${lua_src})
