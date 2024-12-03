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
    
    set_target_properties(${PROJECT_NAME} PROPERTIES
		PREFIX ""
		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Binaries"
		LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/Binaries"
		LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/Binaries"
		LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/Binaries"
		LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/Binaries"
	)
endfunction()

CreateSoftcamTarget(softcam SHARED)
CreateSoftcamTarget(softcamStatic STATIC)
