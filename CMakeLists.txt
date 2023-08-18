cmake_minimum_required(VERSION 3.0)

project(myapp)

# Get a list of all the .cpp files in the current directory
file(GLOB SOURCES *.cpp)

# Add each file to the project
foreach(SOURCE ${SOURCES})
    add_executable(${PROJECT_NAME} ${SOURCE})
endforeach()

