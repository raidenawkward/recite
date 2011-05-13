PROJECT(rcore)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set (RCORE_SOURCES
	src/rcore.cpp
	src/rrecord.cpp
	src/rhistfile.cpp
	src/rcoding.cpp
	src/rprop.cpp
	src/md5.c
)

INCLUDE_DIRECTORIES(
	${dictbase_SROUCE_DIR}
	${stardict_SOURCE_DIR}
)

#ADD_EXECUTABLE(dictcore ${RCORE_SOURCES})
ADD_LIBRARY(rcore STATIC ${RCORE_SOURCES})

