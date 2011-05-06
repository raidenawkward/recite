cmake_minimum_required(VERSION 2.6)
PROJECT(stardict)

SET(STARDICT_SRC
dict_info.c
dict_idx.c
stardict.cpp
)

INCLUDE_DIRECTORIES( "${stardict_SOURCE_DIR}/../dictbase/" )


#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -g -ggdb")

#ADD_LIBRARY(startdict SHARED ${STARDICT_SRC})i
ADD_EXECUTABLE(test ${STARDICT_SRC})

set(CMAKE_LIBRARY_PATH "${stardict_SOURCE_DIR}/../dictbase/")

#LINK_DIRECTORIES("${stardict_SOURCE_DIR}/../dictbase/")

FIND_LIBRARY(DICT_LIBS libdictbase.a)

TARGET_LINK_LIBRARIES(test ${DICT_LIBS})
