rock_library(path2d_view
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(path2d_view_bin Main.cpp
    DEPS path2d_view)

