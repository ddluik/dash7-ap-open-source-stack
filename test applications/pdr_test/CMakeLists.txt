INCLUDE_DIRECTORIES(${D7AOSS_SOURCE_DIR}/d7aoss/)
INCLUDE_DIRECTORIES(${D7AOSS_SOURCE_DIR}/d7aoss/hal)
INCLUDE_DIRECTORIES(${D7AOSS_SOURCE_DIR}/d7aoss/dll)

ADD_EXECUTABLE(pdr_test main.c)
TARGET_LINK_LIBRARIES(pdr_test D7AOSS TRANS)

