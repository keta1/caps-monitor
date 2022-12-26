cmake_minimum_required(VERSION 3.24)
project(caps-monitor C)

set(CMAKE_C_STANDARD 17)

find_library(X11_LIBRARY X11 REQUIRED)

add_executable(caps-monitor main.c)
target_link_libraries(caps-monitor ${X11_LIBRARY} ${DBUS_LDFLAGS})
