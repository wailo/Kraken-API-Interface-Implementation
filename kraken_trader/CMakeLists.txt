cmake_minimum_required (VERSION 2.6)
project (KRAKEN_TRADER)

add_definitions("-std=c++14" -stdlib=libc++)

#-------------------------------------------------------------------------------
IF (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
	add_definitions("-Wno-tautological-compare")

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
# Find boost
#-------------------------------------------------------------------------------
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories (${BOOST_INCLUDE_DIRS} KRAKENAPI)
#list(APPEND LIBS ${BOOST_LIBRARIES}) 


#-------------------------------------------------------------------------------
# Add the executable 'main'
#-------------------------------------------------------------------------------
FILE(GLOB SRCFILES src/*.cpp)
add_executable (${PROJECT_NAME} ${SRCFILES})
set_target_properties (${PROJECT_NAME} PROPERTIES 
  COMPILE_DEFINITIONS_DEBUG "JSON_DEBUG;JSON_SAFE;JSON_ISO_STRICT")
target_link_libraries (${PROJECT_NAME} ${LIBS} kapi)


#Prep ourselves for compiling boost
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories (${Boost_INCLUDE_DIRS})

# #I like to keep test files in a separate source directory called test
# file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*.cpp)

SET (TEST_SRCS test/order_test.cpp
               test/api_test.cpp)

#Run through each source
foreach(testSrc ${TEST_SRCS})
  #Extract the filename without an extension (NAME_WE)
  get_filename_component(testName ${testSrc} NAME_WE)

  #Add compile target
  add_executable(${testName} ${testSrc} src/order.cpp src/kraken_interface.cpp)

  #link to Boost libraries AND your targets and dependencies
  target_link_libraries(${testName} ${Boost_LIBRARIES} ${LIBS} kapi)

  #I like to move testing binaries into a testBin directory
  set_target_properties(${testName} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/testBin)

  #Finally add it to test execution -
  #Notice the WORKING_DIRECTORY and COMMAND
  
  add_test(NAME ${testName}
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/testBin/${testName} )

   # add_custom_command(
   #   TARGET ${testName}
   #   COMMENT "Run tests"
   #   POST_BUILD 
   #   #WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin
   #   COMMAND ${CMAKE_CTEST_COMMAND}  --output-on-failure
   #   )
endforeach(testSrc)
