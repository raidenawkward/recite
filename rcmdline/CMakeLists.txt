#PROJECT(recite)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

INCLUDE_DIRECTORIES(
	${dictbase_SROUCE_DIR}
	${stardict_SOURCE_DIR}
)

set (CMDLINE_SOURCES
    src/main.cpp
)

ADD_EXECUTABLE(recite ${CMDLINE_SOURCES})


LINK_DIRECTORIES(
   ${dictbase_BINARY_DIR}
   ${stardict_BINARY_DIR}
   ${rcore_BINARY_DIR}
)

TARGET_LINK_LIBRARIES(recite rcore stardict dictbase)
