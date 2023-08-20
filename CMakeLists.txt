cmake_minimum_required(VERSION 3.16)
project(ximea_opencv_quickstart)

set(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/
)

find_package(OpenCV 4.2 REQUIRED)

link_directories(
	/usr/local/lib
	/usr/lib
)

include_directories(
	include
	/usr/include/
    /opt/XIMEA/include
)

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC
    ${OpenCV_LIBS}
    m3api
)
