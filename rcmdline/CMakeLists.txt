#PROJECT(recite)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(PROJECT_BUILD_NAME ggst)

INCLUDE_DIRECTORIES(
	${dictbase_SROUCE_DIR}
	${stardict_SOURCE_DIR}
)

SET (CMDLINE_SOURCES
    src/main.cpp
	src/cmds.cpp
	src/rcmd.cpp
	src/rconsole.cpp
	src/rui.cpp
	src/usercmd.cpp
	src/dictcmd.cpp
	src/checkcmd.cpp
)

ADD_EXECUTABLE(${PROJECT_BUILD_NAME} ${CMDLINE_SOURCES})


LINK_DIRECTORIES(
   ${dictbase_BINARY_DIR}
   ${stardict_BINARY_DIR}
   ${rcore_BINARY_DIR}
)

TARGET_LINK_LIBRARIES(${PROJECT_BUILD_NAME} rcore stardict dictbase)
