project(dumplog)

add_executable(dumplog main.cpp)

add_definitions(-std=c++11)

install(TARGETS dumplog RUNTIME DESTINATION bin)
