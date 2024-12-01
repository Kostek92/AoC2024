cmake_minimum_required(VERSION 3.16)

project(AoC LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(AoC main.cpp
	src/day1.h src/day1.cpp
	src/config.h)

include(GNUInstallDirs)
install(TARGETS AoC
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
