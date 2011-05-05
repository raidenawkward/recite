PROJECT(startdict)

SET(STARDICT_SRC
dict_info.c
dict_idx.c
test_dict_info.c
)

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -g -ggdb")

#ADD_LIBRARY(startdict SHARED ${STARDICT_SRC})
ADD_EXECUTABLE(test ${STARDICT_SRC})
