cmake_minimum_required(VERSION 2.6)
PROJECT(startdict)

SET(STARDICT_SRC
dict_info.c
dict_idx.c
stardict.cpp
)

INCLUDE_DIRECTORIES( "../dictbase/" )

#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -g -ggdb")

#ADD_LIBRARY(startdict SHARED ${STARDICT_SRC})
ADD_EXECUTABLE(test ${STARDICT_SRC})
