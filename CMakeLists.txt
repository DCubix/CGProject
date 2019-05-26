cmake_minimum_required(VERSION 3.10)
project(imgstudio VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

file(GLOB SRC
	"src/*.h"
	"src/*.c"
	"src/*.cpp"
	"src/*.hpp"

	"src/nodes/*.h"
	"src/nodes/*.cpp"
	"src/nodes/*.hpp"
)

find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GUI)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} PRIVATE gui)

if (CMAKE_DL_LIBS)
	target_link_libraries(${PROJECT_NAME} PRIVATE 
		${CMAKE_DL_LIBS}
	)
endif()
