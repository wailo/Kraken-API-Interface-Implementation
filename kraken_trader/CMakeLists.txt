cmake_minimum_required (VERSION 2.6)
project (KRAKEN_TRADER)

#-------------------------------------------------------------------------------
IF (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
	add_definitions("-Wno-tautological-compare" -stdlib=libc++)

ENDIF()

#-------------------------------------------------------------------------------
IF (APPLE)
	set (CMAKE_MODULE_LINKER_FLAGS "-Wl,-flat_namespace -Wl,-undefined -Wl,suppress")
ENDIF (APPLE)

#-------------------------------------------------------------------------------
IF (POLICY CMP0043)
	cmake_policy(SET CMP0043 OLD)
ENDIF()

#-------------------------------------------------------------------------------
# Control CMAKE_BUILD_TYPE, default: Debug
#-------------------------------------------------------------------------------
if (NOT CMAKE_BUILD_TYPE)
	set (CMAKE_BUILD_TYPE "Debug" CACHE string "Build type" FORCE)
endif (NOT CMAKE_BUILD_TYPE)
message (STATUS "Build type: " ${CMAKE_BUILD_TYPE})


#-------------------------------------------------------------------------------
# Find ncurses
#-------------------------------------------------------------------------------
find_package(Curses REQUIRED)

#-------------------------------------------------------------------------------
# Add the executable 'main'
#-------------------------------------------------------------------------------
FILE(GLOB SRCFILES src/*.cpp)
add_executable (${PROJECT_NAME} ${SRCFILES})
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS_DEBUG "JSON_DEBUG;JSON_SAFE;JSON_ISO_STRICT")
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS_RELEASE "NDEBUG;JSON_SAFE;JSON_ISO_STRICT")
target_link_libraries (${PROJECT_NAME} ${LIBS} kapi ${CURSES_LIBRARIES})

#Prep ourselves for compiling boost
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories (${Boost_INCLUDE_DIRS})

SET (TEST_SRCS test/order_test.cpp)
# Note: test/api_test.cpp, containts test that talks to the api, should never be enabled by default

# Run through each source
foreach(testsrc ${TEST_SRCS})
  #extract the filename without an extension (name_we)
  get_filename_component(testname ${testsrc} NAME_WE)

  #add compile target
  add_executable(${testname} ${testsrc} src/order.cpp src/kraken_interface.cpp)

  #link to boost libraries and your targets and dependencies
  target_link_libraries(${testname} PRIVATE ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${libs} kapi)

  # add it to test execution -
  add_test(NAME ${testname}
    COMMAND ${testname} --log_level=all )

endforeach(testsrc)
