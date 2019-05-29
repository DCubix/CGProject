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

if(APPLE AND USE_OpenMP)
	if(CMAKE_C_COMPILER_ID MATCHES "Clang")
		set(OpenMP_C "${CMAKE_C_COMPILER}")
		set(OpenMP_C_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
		set(OpenMP_C_LIB_NAMES "libomp" "libgomp" "libiomp5")
		set(OpenMP_libomp_LIBRARY ${OpenMP_C_LIB_NAMES})
		set(OpenMP_libgomp_LIBRARY ${OpenMP_C_LIB_NAMES})
		set(OpenMP_libiomp5_LIBRARY ${OpenMP_C_LIB_NAMES})
	endif()
	if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	  set(OpenMP_CXX "${CMAKE_CXX_COMPILER}")
	  set(OpenMP_CXX_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
	  set(OpenMP_CXX_LIB_NAMES "libomp" "libgomp" "libiomp5")
	  set(OpenMP_libomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
	  set(OpenMP_libgomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
	  set(OpenMP_libiomp5_LIBRARY ${OpenMP_CXX_LIB_NAMES})
	endif()
endif()

# find_package(OpenCL REQUIRED OpenCL)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GUI)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/openpnp-capture)

add_executable(${PROJECT_NAME} ${SRC})
# OpenCL::OpenCL
target_link_libraries(${PROJECT_NAME} PRIVATE gui openpnp-capture)

if (CMAKE_DL_LIBS)
	target_link_libraries(${PROJECT_NAME} PRIVATE 
		${CMAKE_DL_LIBS}
	)
endif()
