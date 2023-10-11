include(CMakeParseArguments)

function(ds_build_package)
    set(oneValueArgs PACKAGE TARGET)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(_config "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_custom_target(${_config_PACKAGE}_package ALL
        SOURCES ${_config_SOURCES}
    )
    set(package_dirs ${PROJECT_BINARY_DIR}/packages/${_config_PACKAGE}/)
    set(copy_files ${_config_SOURCES})
    add_custom_command(TARGET ${_config_PACKAGE}_package
        COMMAND ${CMAKE_COMMAND} -E make_directory ${package_dirs}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${copy_files} ${package_dirs}
    )

    if (DEFINED _config_TARGET)
        set_target_properties(${_config_TARGET} PROPERTIES
            PREFIX ""
            OUTPUT_NAME ${_config_PACKAGE}
            LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/plugins/
        )
    endif()
endfunction()
