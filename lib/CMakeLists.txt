
add_library(
    TeeStream
    INTERFACE
)

target_include_directories(
    TeeStream
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)


# Installation

install(
    TARGETS TeeStream EXPORT TeeStreamConfig
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}  # This is for Windows
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT TeeStreamConfig DESTINATION share/teestream/cmake)

# This makes the project importable from the build directory
export(TARGETS TeeStream FILE TeeStreamConfig.cmake)
