add_library(softcamcore STATIC
    DShowSoftcam.cpp
    DShowSoftcam.h
    FrameBuffer.cpp
    FrameBuffer.h
    Misc.cpp
    Misc.h
    SenderAPI.cpp
    SenderAPI.h
    Watchdog.cpp
    Watchdog.h
)

target_include_directories(softcamcore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/.
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../baseclasses
)