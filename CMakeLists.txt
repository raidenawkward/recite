PROJECT(recite)
cmake_minimum_required(VERSION 2.6)


MESSAGE("building raiden project ${PROJECT}")


INCLUDE_DIRECTORIES(
		dictsupport/dictbase
		distsupport/stardict
		rcore/src
)

ADD_SUBDIRECTORY(dictsupport/dictbase)
ADD_SUBDIRECTORY(dictsupport/stardict)
ADD_SUBDIRECTORY(rcore)

#build cmd line project
ADD_SUBDIRECTORY(rcmdline)
