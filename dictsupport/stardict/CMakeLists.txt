cmake_minimum_required(VERSION 2.6)
PROJECT(stardict)

SET(STARDICT_SRC
dict_info.c
dict_idx.c
stardict.cpp
)

ADD_LIBRARY(stardict STATIC ${STARDICT_SRC})
