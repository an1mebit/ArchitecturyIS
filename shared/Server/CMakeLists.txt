project(robot)

set( HEADER_FILES "../Common/socketExchanger.h" "../Common/socketExchanger.cpp" "src/event.h" "src/event.cpp" "src/system.h" "src/system.cpp" "src/camera.h" "src/camera.cpp" "src/generator.h" "src/generator.cpp" )

add_executable( Server "src/main.cpp" ${HEADER_FILES})

target_include_directories( Server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}" )
target_link_libraries( Server ${OpenCV_LIBS} )