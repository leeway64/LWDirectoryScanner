cmake_minimum_required (VERSION 3.8)

project (
	"LWDirectoryScanner"
	LANGUAGES C
	VERSION "0.0.1"
	)



list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
	message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
	file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
			"${CMAKE_BINARY_DIR}/conan.cmake"
			TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

# conan_cmake_configures accepts the same arguments as conanfile.txt
conan_cmake_configure(REQUIRES	libcbor/0.9.0
		GENERATORS cmake_find_package)

conan_cmake_autodetect(settings)

# I can pass conan_cmake_install all the arguments that conan install supports
conan_cmake_install(PATH_OR_REFERENCE .
		BUILD missing
		REMOTE conancenter
		SETTINGS ${settings})

find_package(libcbor)

add_executable ("LWDirectoryScanner"
		"src/main.c"
		"src/scanner_helpers.h"
		"src/scanner_helpers.c")

target_link_libraries(
		"LWDirectoryScanner"
		PRIVATE
		libcbor::libcbor)
