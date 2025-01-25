cmake_minimum_required(VERSION 3.10)

# Set the project name
project(FiniteStateMachine)

# Add the header files
file(GLOB_RECURSE HEADER_FILES
    FiniteStateMachine/*.h
)

# Add the source files
file(GLOB_RECURSE SOURCE_FILES
    FiniteStateMachine/*.cpp
)

#find_library(EXCEPTIONS_LIB Exceptions PATHS ../Exceptions/build)

# Add the library
add_library(FiniteStateMachine STATIC ${SOURCE_FILES} ${HEADER_FILES})

# Add definitions
target_compile_definitions(FiniteStateMachine PRIVATE EXCEPTIONS_LIBRARY FINITE_STATE_MACHINE_LIBRARY ENGLISH)

# Link libraries
target_link_libraries(FiniteStateMachine PRIVATE Exceptions)

# Set include path for the library
target_include_directories(FiniteStateMachine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
