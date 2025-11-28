cmake_minimum_required(VERSION 3.20...4.0) # FetchContent is available in 3.11+

project(pinger LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(wxBUILD_SHARED OFF)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

# statically link MSVC runtime in thrift to being fully self-contained.
# this increases .exe size but guarantees working on all windows versions
# see https://cmake.org/cmake/help/latest/variable/CMAKE_MSVC_RUNTIME_LIBRARY.html
#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")


include(FetchContent)

FetchContent_Declare(
   wxWidgets
   GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
   GIT_SHALLOW ON
)
FetchContent_MakeAvailable(wxWidgets)

include_directories(${CPP_INCLUDE_DIRS}) #include file folder


set(
    source_list 
    
    
    src_base/main.cpp
    src_base/MyProjectBase.h
    src_base/MyProjectBase.cpp

    src_app/MainDialog.h
    src_app/MainDialog.cpp

    src_app/BG_ICMP.cpp
	src_app/BG_ICMP.h
    src_app/bungee.rc
	src_app/bungee.ico


    main.exe.manifest
)




#this organizes the VS project folder like the source tree folder
foreach(source IN LISTS source_list)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()




#================================================
 # the WIN32 is needed for Windows in order for it to look for WinMain
 # instead of the main function.

add_executable(${PROJECT_NAME} WIN32
  ${CPP_HEADER_FILES}
  ${CPP_SOURCE_FILES}
  ${source_list}
)
 

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME} )

target_include_directories(${PROJECT_NAME}  PUBLIC src_base)
target_include_directories(${PROJECT_NAME}  PUBLIC src_app)

target_link_libraries(${PROJECT_NAME} PUBLIC wxcore wxnet)



