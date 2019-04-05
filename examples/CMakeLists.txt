
add_executable(
    TeeStreamExample
    main.cpp
)

target_include_directories(
    TeeStreamExample
    PUBLIC
)

set_target_properties(
    TeeStreamExample
    PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_link_libraries(
    TeeStreamExample
    TeeStream
)


# Installation

install(
    TARGETS TeeStreamExample
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
