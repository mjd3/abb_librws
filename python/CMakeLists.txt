cmake_minimum_required(VERSION 3.5)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Read version from the package.xml file.
file(READ ${CMAKE_CURRENT_SOURCE_DIR}/../package.xml package_xml_str)
if(NOT package_xml_str MATCHES "<version>([0-9]+.[0-9]+.[0-9]+)</version>")
  message(FATAL_ERROR "Could not parse project version from package.xml. Aborting.")
endif()

# At this point we either have a proper version string, or we've errored
# out with a FATAL_ERROR above. So assume CMAKE_MATCH_1 contains our
# package's version.
project(abb_librws VERSION ${CMAKE_MATCH_1} LANGUAGES CXX)

include(GNUInstallDirs)

list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/third_party")

if(WIN32)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

########################
## Find deps          ##
########################
# We need at least 1.4.3 because of WebSocket support.
find_package(Poco 1.4.3 REQUIRED COMPONENTS Foundation Net Util XML)

# Need Python_SITELIB for install
find_package(Python COMPONENTS Interpreter Development)

add_subdirectory(extern/pybind11)

###########
## Build ##
###########
file (GLOB SOURCE_FILES "../src/*.cpp")
file (GLOB HEADER_FILES "../include/abb_librws/*.h")
file (GLOB PYTHON_FILES "*.cpp" "*.hpp")

pybind11_add_module(${PROJECT_NAME} 
	${SOURCE_FILES}
	${HEADER_FILES}
	${PYTHON_FILES}
)

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include;${CMAKE_CURRENT_BINARY_DIR}>"
  $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>
  ${Poco_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  ${Poco_LIBRARIES}
)

install(TARGETS ${PROJECT_NAME}
  COMPONENT python
  LIBRARY DESTINATION "${Python_SITELIB}"
)
