cmake_minimum_required(VERSION 2.6)
PROJECT(dictbase)

SET(DICTBASE_SRC
dictbase.cpp
)

#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -g -ggdb")
INCLUDE_DIRECTORIES( . )
ADD_LIBRARY(dictbase STATIC ${DICTBASE_SRC})
