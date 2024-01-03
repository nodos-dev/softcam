function(CreateSoftcamTarget PROJECT_NAME LIBRARY_TYPE)

    ################################################################################
    # Source groups
    ################################################################################
    set(src
        "softcam.cpp"
        "softcam.def"
        "softcam.h"
    )
    source_group("src" FILES ${src})

    set(ALL_FILES
        ${src}
    )

    ################################################################################
    # Target
    ################################################################################
    add_library(${PROJECT_NAME} ${LIBRARY_TYPE} ${ALL_FILES})

    # use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
    set(ROOT_NAMESPACE softcam)

    set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_GLOBAL_KEYWORD "Win32Proj"
    )
    ################################################################################
    # Target name
    ################################################################################
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        set_target_properties(${PROJECT_NAME} PROPERTIES
            TARGET_NAME_DEBUG   ${PROJECT_NAME}d
            TARGET_NAME_RELEASE ${PROJECT_NAME}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        set_target_properties(${PROJECT_NAME} PROPERTIES
            TARGET_NAME_DEBUG   ${PROJECT_NAME}d
            TARGET_NAME_RELEASE ${PROJECT_NAME}
        )
    endif()
    # ################################################################################
    # # Output directory
    # ################################################################################
    # if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    #     set_target_properties(${PROJECT_NAME} PROPERTIES
    #         OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    #         OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    #     )
    # endif()
    ################################################################################
    # MSVC runtime library
    ################################################################################
    # get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
    # if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    #     string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
    #         $<$<CONFIG:Debug>:
    #             MultiThreadedDebugDLL
    #         >
    #         $<$<NOT:$<OR:$<CONFIG:Debug>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
    #     )
    # elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    #     string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
    #         $<$<CONFIG:Debug>:
    #             MultiThreadedDebugDLL
    #         >
    #         $<$<NOT:$<OR:$<CONFIG:Debug>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
    #     )
    # endif()
    # set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

    ################################################################################
    # Include directories
    ################################################################################
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_include_directories(${PROJECT_NAME} PUBLIC
            "${CMAKE_CURRENT_SOURCE_DIR}/.;"
            "${CMAKE_CURRENT_SOURCE_DIR}/..;"
            "${CMAKE_CURRENT_SOURCE_DIR}/../baseclasses"
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_include_directories(${PROJECT_NAME} PUBLIC
            "${CMAKE_CURRENT_SOURCE_DIR}/.;"
            "${CMAKE_CURRENT_SOURCE_DIR}/..;"
            "${CMAKE_CURRENT_SOURCE_DIR}/../baseclasses"
        )
    endif()

    ################################################################################
    # Compile definitions
    ################################################################################
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_compile_definitions(${PROJECT_NAME} PRIVATE
            "$<$<CONFIG:Debug>:"
                "_DEBUG"
            ">"
            "$<$<CONFIG:Release>:"
                "NDEBUG"
            ">"
            "WIN32;"
            "_CRT_SECURE_NO_WARNINGS;"
            "UNICODE;"
            "_UNICODE"
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_definitions(${PROJECT_NAME} PRIVATE
            "$<$<CONFIG:Debug>:"
                "_DEBUG"
            ">"
            "$<$<CONFIG:Release>:"
                "NDEBUG"
            ">"
            "WIN32;"
            "_CRT_SECURE_NO_WARNINGS;"
            "UNICODE;"
            "_UNICODE"
        )
    endif()

    ################################################################################
    # Compile and link options
    ################################################################################
    if(MSVC)
        if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
            target_compile_options(${PROJECT_NAME} PRIVATE
                $<$<CONFIG:Debug>:
                    /Od
                >
                $<$<CONFIG:Release>:
                    /Gy
                >
                # /permissive-;
                /MP;
                /sdl;
                /W4;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
                ${DEFAULT_CXX_EXCEPTION_HANDLING}
            )
        elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
            target_compile_options(${PROJECT_NAME} PRIVATE
                $<$<CONFIG:Debug>:
                    /Od
                >
                $<$<CONFIG:Release>:
                    /Gy
                >
                # /permissive-;
                /MP;
                /sdl;
                /W4;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
                ${DEFAULT_CXX_EXCEPTION_HANDLING}
            )
        endif()
        if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
            target_link_options(${PROJECT_NAME} PRIVATE
                $<$<CONFIG:Release>:
                    /OPT:REF;
                    /OPT:ICF
                >
                /DEBUG;
                /SUBSYSTEM:CONSOLE
            )
        elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
            target_link_options(${PROJECT_NAME} PRIVATE
                $<$<CONFIG:Release>:
                    /OPT:REF;
                    /OPT:ICF
                >
                /DEBUG;
                /SUBSYSTEM:CONSOLE
            )
        endif()
    endif()

    # ################################################################################
    # # Post build events
    # ################################################################################
    # if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    #     add_custom_command_if(
    #         TARGET ${PROJECT_NAME}
    #         POST_BUILD
    #         COMMANDS
    #         COMMAND   $<CONFIG:Debug> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist
    #         COMMAND   $<CONFIG:Debug> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\include mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\include
    #         COMMAND   $<CONFIG:Debug> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\include\\softcam mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\include\\softcam
    #         COMMAND   $<CONFIG:Debug> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\lib mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\lib
    #         COMMAND   $<CONFIG:Debug> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\lib\\${CMAKE_VS_PLATFORM_NAME} mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\lib\\${CMAKE_VS_PLATFORM_NAME}
    #         COMMAND   $<CONFIG:Debug> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\bin mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\bin
    #         COMMAND   $<CONFIG:Debug> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\bin\\${CMAKE_VS_PLATFORM_NAME} mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\bin\\${CMAKE_VS_PLATFORM_NAME}
    #         COMMAND   $<CONFIG:Debug> @echo softcam.h -^> ...dist\\include\\softcam\\
    #         COMMAND   $<CONFIG:Debug> @copy /y $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/>softcam.h $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\include\\softcam
    #         COMMAND   $<CONFIG:Debug> @echo ${TARGET_NAME}.lib -^> ...dist\\lib\\${CMAKE_VS_PLATFORM_NAME}\\
    #         COMMAND   $<CONFIG:Debug> @copy /y ${OUTPUT_DIRECTORY}${TARGET_NAME}.lib $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\lib\\${CMAKE_VS_PLATFORM_NAME}
    #         COMMAND   $<CONFIG:Debug> @echo ${TARGET_NAME}.dll -^> ...dist\\bin\\${CMAKE_VS_PLATFORM_NAME}\\
    #         COMMAND   $<CONFIG:Debug> @copy /y ${OUTPUT_DIRECTORY}${TARGET_NAME}.dll $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\bin\\${CMAKE_VS_PLATFORM_NAME}
    #         COMMAND $<CONFIG:Release> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist
    #         COMMAND $<CONFIG:Release> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\include mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\include
    #         COMMAND $<CONFIG:Release> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\include\\softcam mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\include\\softcam
    #         COMMAND $<CONFIG:Release> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\lib mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\lib
    #         COMMAND $<CONFIG:Release> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\lib\\${CMAKE_VS_PLATFORM_NAME} mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\lib\\${CMAKE_VS_PLATFORM_NAME}
    #         COMMAND $<CONFIG:Release> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\bin mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\bin
    #         COMMAND $<CONFIG:Release> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\bin\\${CMAKE_VS_PLATFORM_NAME} mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\bin\\${CMAKE_VS_PLATFORM_NAME}
    #         COMMAND $<CONFIG:Release> @echo softcam.h -^> ...dist\\include\\softcam\\
    #         COMMAND $<CONFIG:Release> @copy /y $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/>softcam.h $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\include\\softcam
    #         COMMAND $<CONFIG:Release> @echo ${TARGET_NAME}.lib -^> ...dist\\lib\\${CMAKE_VS_PLATFORM_NAME}\\
    #         COMMAND $<CONFIG:Release> @copy /y ${OUTPUT_DIRECTORY}${TARGET_NAME}.lib $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\lib\\${CMAKE_VS_PLATFORM_NAME}
    #         COMMAND $<CONFIG:Release> @echo ${TARGET_NAME}.dll -^> ...dist\\bin\\${CMAKE_VS_PLATFORM_NAME}\\
    #         COMMAND $<CONFIG:Release> @copy /y ${OUTPUT_DIRECTORY}${TARGET_NAME}.dll $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\bin\\${CMAKE_VS_PLATFORM_NAME}
    #         COMMENT "Creating dist directory and copying the header and binaries into it."
    #     )
    # elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    #     add_custom_command_if(
    #         TARGET ${PROJECT_NAME}
    #         POST_BUILD
    #         COMMANDS
    #         COMMAND   $<CONFIG:Debug> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist
    #         COMMAND   $<CONFIG:Debug> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\include mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\include
    #         COMMAND   $<CONFIG:Debug> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\include\\softcam mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\include\\softcam
    #         COMMAND   $<CONFIG:Debug> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\lib mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\lib
    #         COMMAND   $<CONFIG:Debug> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\lib\\${CMAKE_VS_PLATFORM_NAME} mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\lib\\${CMAKE_VS_PLATFORM_NAME}
    #         COMMAND   $<CONFIG:Debug> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\bin mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\bin
    #         COMMAND   $<CONFIG:Debug> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\bin\\${CMAKE_VS_PLATFORM_NAME} mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\bin\\${CMAKE_VS_PLATFORM_NAME}
    #         COMMAND   $<CONFIG:Debug> @echo softcam.h -^> ...dist\\include\\softcam\\
    #         COMMAND   $<CONFIG:Debug> @copy /y $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/>softcam.h $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\include\\softcam
    #         COMMAND   $<CONFIG:Debug> @echo ${TARGET_NAME}.lib -^> ...dist\\lib\\${CMAKE_VS_PLATFORM_NAME}\\
    #         COMMAND   $<CONFIG:Debug> @copy /y ${OUTPUT_DIRECTORY}${TARGET_NAME}.lib $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\lib\\${CMAKE_VS_PLATFORM_NAME}
    #         COMMAND   $<CONFIG:Debug> @echo ${TARGET_NAME}.dll -^> ...dist\\bin\\${CMAKE_VS_PLATFORM_NAME}\\
    #         COMMAND   $<CONFIG:Debug> @copy /y ${OUTPUT_DIRECTORY}${TARGET_NAME}.dll $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\bin\\${CMAKE_VS_PLATFORM_NAME}
    #         COMMAND $<CONFIG:Release> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist
    #         COMMAND $<CONFIG:Release> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\include mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\include
    #         COMMAND $<CONFIG:Release> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\include\\softcam mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\include\\softcam
    #         COMMAND $<CONFIG:Release> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\lib mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\lib
    #         COMMAND $<CONFIG:Release> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\lib\\${CMAKE_VS_PLATFORM_NAME} mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\lib\\${CMAKE_VS_PLATFORM_NAME}
    #         COMMAND $<CONFIG:Release> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\bin mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\bin
    #         COMMAND $<CONFIG:Release> @if not exist $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\bin\\${CMAKE_VS_PLATFORM_NAME} mkdir $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\bin\\${CMAKE_VS_PLATFORM_NAME}
    #         COMMAND $<CONFIG:Release> @echo softcam.h -^> ...dist\\include\\softcam\\
    #         COMMAND $<CONFIG:Release> @copy /y $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/>softcam.h $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\include\\softcam
    #         COMMAND $<CONFIG:Release> @echo ${TARGET_NAME}.lib -^> ...dist\\lib\\${CMAKE_VS_PLATFORM_NAME}\\
    #         COMMAND $<CONFIG:Release> @copy /y ${OUTPUT_DIRECTORY}${TARGET_NAME}.lib $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\lib\\${CMAKE_VS_PLATFORM_NAME}
    #         COMMAND $<CONFIG:Release> @echo ${TARGET_NAME}.dll -^> ...dist\\bin\\${CMAKE_VS_PLATFORM_NAME}\\
    #         COMMAND $<CONFIG:Release> @copy /y ${OUTPUT_DIRECTORY}${TARGET_NAME}.dll $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>dist\\bin\\${CMAKE_VS_PLATFORM_NAME}
    #         COMMENT "Creating dist directory and copying the header and binaries into it."
    #     )
    # endif()

    ################################################################################
    # Dependencies
    ################################################################################
    # Link with other targets.
    target_link_libraries(${PROJECT_NAME} PUBLIC
        BaseClasses
        softcamcore
    )

    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        set(ADDITIONAL_LIBRARY_DEPENDENCIES
            "$<$<CONFIG:Debug>:"
                "msvcrtd"
            ">"
            "$<$<CONFIG:Release>:"
                "msvcrt"
            ">"
            "winmm;"
            "kernel32;"
            "user32;"
            "gdi32;"
            "winspool;"
            "comdlg32;"
            "advapi32;"
            "shell32;"
            "ole32;"
            "oleaut32;"
            "uuid;"
            "odbc32;"
            "odbccp32"
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        set(ADDITIONAL_LIBRARY_DEPENDENCIES
            "$<$<CONFIG:Debug>:"
                "msvcrtd"
            ">"
            "$<$<CONFIG:Release>:"
                "msvcrt"
            ">"
            "winmm;"
            "kernel32;"
            "user32;"
            "gdi32;"
            "winspool;"
            "comdlg32;"
            "advapi32;"
            "shell32;"
            "ole32;"
            "oleaut32;"
            "uuid;"
            "odbc32;"
            "odbccp32"
        )
    endif()
    target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

endfunction()

CreateSoftcamTarget(softcam SHARED)
CreateSoftcamTarget(softcamStatic STATIC)
