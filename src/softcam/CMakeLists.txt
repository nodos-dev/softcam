function(CreateSoftcamTarget PROJECT_NAME LIBRARY_TYPE)
    add_library(${PROJECT_NAME} ${LIBRARY_TYPE}
        softcam.cpp
        softcam.def
        softcam.h
    )

    target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/.
        ${CMAKE_CURRENT_SOURCE_DIR}/..
        ${CMAKE_CURRENT_SOURCE_DIR}/../baseclasses
    )

    target_link_libraries(${PROJECT_NAME} PUBLIC
        BaseClasses
        softcamcore
    )
endfunction()

CreateSoftcamTarget(softcam SHARED)
CreateSoftcamTarget(softcamStatic STATIC)
