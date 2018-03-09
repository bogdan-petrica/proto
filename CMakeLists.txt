cmake_minimum_required(VERSION 3.8)
project(DesignProto)

add_executable(designProto
	src/typelist.h

	src/ctimeTree.h
    src/conv.h
	src/fsm.h
    src/hsm.h
	src/units.h

	src/ctimeTree.cpp
    src/conv.cpp
	src/fsm.cpp
    src/hsm.cpp
	src/units.cpp


	src/main.cpp)
