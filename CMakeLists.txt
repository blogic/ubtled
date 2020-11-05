cmake_minimum_required(VERSION 2.6)

PROJECT(ubtled C)
INCLUDE(GNUInstallDirs)
ADD_DEFINITIONS(-Os -ggdb -Wall -Werror -Wmissing-declarations --pedantic)

SET(LIBS ubox ubus bluetooth)

ADD_EXECUTABLE(ubtled main.c 6lowpan.c ubus.c)
TARGET_LINK_LIBRARIES(ubtled ${LIBS})
INSTALL(TARGETS ubtled
	RUNTIME DESTINATION ${CMAKE_INSTALL_SBINDIR}
)
