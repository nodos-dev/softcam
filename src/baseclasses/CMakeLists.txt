add_library(BaseClasses STATIC
    amfilter.cpp
    amfilter.h
    amvideo.cpp
    combase.cpp
    combase.h
    dllentry.cpp
    dllsetup.cpp
    dllsetup.h
    fourcc.h
    measure.h
    mtype.cpp
    mtype.h
    refclock.h
    reftime.h
    renbase.h
    schedule.h
    source.cpp
    source.h
    streams.h
    winutil.cpp
    winutil.h
    wxdebug.cpp
    wxdebug.h
    wxlist.cpp
    wxlist.h
    wxutil.cpp
    wxutil.h
)

target_include_directories(BaseClasses PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/.)

target_link_libraries(BaseClasses PUBLIC
    strmiids
    winmm
)
