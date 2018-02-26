cmake_minimum_required(VERSION 3.8)
project(DesignProto)

add_executable(designProto
	src/ctimeTree.h
	src/fsm.h
	src/units.h

	src/ctimeTree.cpp
	src/fsm.cpp
	src/units.cpp

	src/main.cpp)
