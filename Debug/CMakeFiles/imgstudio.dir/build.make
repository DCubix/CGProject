# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\CMake\bin\cmake.exe

# The command to remove a file.
RM = C:\CMake\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Twister\Projects\cpp\cgproject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Twister\Projects\cpp\cgproject\Debug

# Include any dependencies generated for this target.
include CMakeFiles/imgstudio.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/imgstudio.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/imgstudio.dir/flags.make

CMakeFiles/imgstudio.dir/src/filter.cpp.obj: CMakeFiles/imgstudio.dir/flags.make
CMakeFiles/imgstudio.dir/src/filter.cpp.obj: CMakeFiles/imgstudio.dir/includes_CXX.rsp
CMakeFiles/imgstudio.dir/src/filter.cpp.obj: ../src/filter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/imgstudio.dir/src/filter.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\imgstudio.dir\src\filter.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\src\filter.cpp

CMakeFiles/imgstudio.dir/src/filter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgstudio.dir/src/filter.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\src\filter.cpp > CMakeFiles\imgstudio.dir\src\filter.cpp.i

CMakeFiles/imgstudio.dir/src/filter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgstudio.dir/src/filter.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\src\filter.cpp -o CMakeFiles\imgstudio.dir\src\filter.cpp.s

CMakeFiles/imgstudio.dir/src/kernel.cpp.obj: CMakeFiles/imgstudio.dir/flags.make
CMakeFiles/imgstudio.dir/src/kernel.cpp.obj: CMakeFiles/imgstudio.dir/includes_CXX.rsp
CMakeFiles/imgstudio.dir/src/kernel.cpp.obj: ../src/kernel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/imgstudio.dir/src/kernel.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\imgstudio.dir\src\kernel.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\src\kernel.cpp

CMakeFiles/imgstudio.dir/src/kernel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgstudio.dir/src/kernel.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\src\kernel.cpp > CMakeFiles\imgstudio.dir\src\kernel.cpp.i

CMakeFiles/imgstudio.dir/src/kernel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgstudio.dir/src/kernel.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\src\kernel.cpp -o CMakeFiles\imgstudio.dir\src\kernel.cpp.s

CMakeFiles/imgstudio.dir/src/main.cpp.obj: CMakeFiles/imgstudio.dir/flags.make
CMakeFiles/imgstudio.dir/src/main.cpp.obj: CMakeFiles/imgstudio.dir/includes_CXX.rsp
CMakeFiles/imgstudio.dir/src/main.cpp.obj: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/imgstudio.dir/src/main.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\imgstudio.dir\src\main.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\src\main.cpp

CMakeFiles/imgstudio.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgstudio.dir/src/main.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\src\main.cpp > CMakeFiles\imgstudio.dir\src\main.cpp.i

CMakeFiles/imgstudio.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgstudio.dir/src/main.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\src\main.cpp -o CMakeFiles\imgstudio.dir\src\main.cpp.s

CMakeFiles/imgstudio.dir/src/stb.c.obj: CMakeFiles/imgstudio.dir/flags.make
CMakeFiles/imgstudio.dir/src/stb.c.obj: CMakeFiles/imgstudio.dir/includes_C.rsp
CMakeFiles/imgstudio.dir/src/stb.c.obj: ../src/stb.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/imgstudio.dir/src/stb.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\imgstudio.dir\src\stb.c.obj   -c C:\Users\Twister\Projects\cpp\cgproject\src\stb.c

CMakeFiles/imgstudio.dir/src/stb.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/imgstudio.dir/src/stb.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\src\stb.c > CMakeFiles\imgstudio.dir\src\stb.c.i

CMakeFiles/imgstudio.dir/src/stb.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/imgstudio.dir/src/stb.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\src\stb.c -o CMakeFiles\imgstudio.dir\src\stb.c.s

# Object files for target imgstudio
imgstudio_OBJECTS = \
"CMakeFiles/imgstudio.dir/src/filter.cpp.obj" \
"CMakeFiles/imgstudio.dir/src/kernel.cpp.obj" \
"CMakeFiles/imgstudio.dir/src/main.cpp.obj" \
"CMakeFiles/imgstudio.dir/src/stb.c.obj"

# External object files for target imgstudio
imgstudio_EXTERNAL_OBJECTS =

imgstudio.exe: CMakeFiles/imgstudio.dir/src/filter.cpp.obj
imgstudio.exe: CMakeFiles/imgstudio.dir/src/kernel.cpp.obj
imgstudio.exe: CMakeFiles/imgstudio.dir/src/main.cpp.obj
imgstudio.exe: CMakeFiles/imgstudio.dir/src/stb.c.obj
imgstudio.exe: CMakeFiles/imgstudio.dir/build.make
imgstudio.exe: GUI/libgui.a
imgstudio.exe: GUI/nanovg/libnanovg.a
imgstudio.exe: GUI/osdialog/libosdialog.a
imgstudio.exe: CMakeFiles/imgstudio.dir/linklibs.rsp
imgstudio.exe: CMakeFiles/imgstudio.dir/objects1.rsp
imgstudio.exe: CMakeFiles/imgstudio.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable imgstudio.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\imgstudio.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/imgstudio.dir/build: imgstudio.exe

.PHONY : CMakeFiles/imgstudio.dir/build

CMakeFiles/imgstudio.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\imgstudio.dir\cmake_clean.cmake
.PHONY : CMakeFiles/imgstudio.dir/clean

CMakeFiles/imgstudio.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Twister\Projects\cpp\cgproject C:\Users\Twister\Projects\cpp\cgproject C:\Users\Twister\Projects\cpp\cgproject\Debug C:\Users\Twister\Projects\cpp\cgproject\Debug C:\Users\Twister\Projects\cpp\cgproject\Debug\CMakeFiles\imgstudio.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/imgstudio.dir/depend

