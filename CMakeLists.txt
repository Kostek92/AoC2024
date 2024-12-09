cmake_minimum_required(VERSION 3.16)

project(AoC LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(AoC main.cpp
	src/day1.h src/day1.cpp
	src/day2.h src/day2.cpp
	src/day3.h src/day3.cpp
	src/day4.h src/day4.cpp
	src/day5.h src/day5.cpp
	src/day6.h src/day6.cpp
	src/day7.h src/day7.cpp
	src/day8.h src/day8.cpp
	src/config.h)

include(GNUInstallDirs)
install(TARGETS AoC
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
