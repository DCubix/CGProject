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
CMAKE_BINARY_DIR = C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo

# Include any dependencies generated for this target.
include GUI/CMakeFiles/gui.dir/depend.make

# Include the progress variables for this target.
include GUI/CMakeFiles/gui.dir/progress.make

# Include the compile flags for this target's objects.
include GUI/CMakeFiles/gui.dir/flags.make

GUI/CMakeFiles/gui.dir/application.cpp.obj: GUI/CMakeFiles/gui.dir/flags.make
GUI/CMakeFiles/gui.dir/application.cpp.obj: GUI/CMakeFiles/gui.dir/includes_CXX.rsp
GUI/CMakeFiles/gui.dir/application.cpp.obj: ../GUI/application.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object GUI/CMakeFiles/gui.dir/application.cpp.obj"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gui.dir\application.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\GUI\application.cpp

GUI/CMakeFiles/gui.dir/application.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui.dir/application.cpp.i"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\GUI\application.cpp > CMakeFiles\gui.dir\application.cpp.i

GUI/CMakeFiles/gui.dir/application.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui.dir/application.cpp.s"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\GUI\application.cpp -o CMakeFiles\gui.dir\application.cpp.s

GUI/CMakeFiles/gui.dir/events.cpp.obj: GUI/CMakeFiles/gui.dir/flags.make
GUI/CMakeFiles/gui.dir/events.cpp.obj: GUI/CMakeFiles/gui.dir/includes_CXX.rsp
GUI/CMakeFiles/gui.dir/events.cpp.obj: ../GUI/events.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object GUI/CMakeFiles/gui.dir/events.cpp.obj"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gui.dir\events.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\GUI\events.cpp

GUI/CMakeFiles/gui.dir/events.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui.dir/events.cpp.i"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\GUI\events.cpp > CMakeFiles\gui.dir\events.cpp.i

GUI/CMakeFiles/gui.dir/events.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui.dir/events.cpp.s"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\GUI\events.cpp -o CMakeFiles\gui.dir\events.cpp.s

GUI/CMakeFiles/gui.dir/glad/glad.c.obj: GUI/CMakeFiles/gui.dir/flags.make
GUI/CMakeFiles/gui.dir/glad/glad.c.obj: GUI/CMakeFiles/gui.dir/includes_C.rsp
GUI/CMakeFiles/gui.dir/glad/glad.c.obj: ../GUI/glad/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object GUI/CMakeFiles/gui.dir/glad/glad.c.obj"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\gui.dir\glad\glad.c.obj   -c C:\Users\Twister\Projects\cpp\cgproject\GUI\glad\glad.c

GUI/CMakeFiles/gui.dir/glad/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gui.dir/glad/glad.c.i"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\GUI\glad\glad.c > CMakeFiles\gui.dir\glad\glad.c.i

GUI/CMakeFiles/gui.dir/glad/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gui.dir/glad/glad.c.s"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\GUI\glad\glad.c -o CMakeFiles\gui.dir\glad\glad.c.s

GUI/CMakeFiles/gui.dir/gui.cpp.obj: GUI/CMakeFiles/gui.dir/flags.make
GUI/CMakeFiles/gui.dir/gui.cpp.obj: GUI/CMakeFiles/gui.dir/includes_CXX.rsp
GUI/CMakeFiles/gui.dir/gui.cpp.obj: ../GUI/gui.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object GUI/CMakeFiles/gui.dir/gui.cpp.obj"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gui.dir\gui.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\GUI\gui.cpp

GUI/CMakeFiles/gui.dir/gui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui.dir/gui.cpp.i"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\GUI\gui.cpp > CMakeFiles\gui.dir\gui.cpp.i

GUI/CMakeFiles/gui.dir/gui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui.dir/gui.cpp.s"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\GUI\gui.cpp -o CMakeFiles\gui.dir\gui.cpp.s

GUI/CMakeFiles/gui.dir/image.cpp.obj: GUI/CMakeFiles/gui.dir/flags.make
GUI/CMakeFiles/gui.dir/image.cpp.obj: GUI/CMakeFiles/gui.dir/includes_CXX.rsp
GUI/CMakeFiles/gui.dir/image.cpp.obj: ../GUI/image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object GUI/CMakeFiles/gui.dir/image.cpp.obj"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gui.dir\image.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\GUI\image.cpp

GUI/CMakeFiles/gui.dir/image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui.dir/image.cpp.i"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\GUI\image.cpp > CMakeFiles\gui.dir\image.cpp.i

GUI/CMakeFiles/gui.dir/image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui.dir/image.cpp.s"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\GUI\image.cpp -o CMakeFiles\gui.dir\image.cpp.s

GUI/CMakeFiles/gui.dir/layout.cpp.obj: GUI/CMakeFiles/gui.dir/flags.make
GUI/CMakeFiles/gui.dir/layout.cpp.obj: GUI/CMakeFiles/gui.dir/includes_CXX.rsp
GUI/CMakeFiles/gui.dir/layout.cpp.obj: ../GUI/layout.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object GUI/CMakeFiles/gui.dir/layout.cpp.obj"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gui.dir\layout.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\GUI\layout.cpp

GUI/CMakeFiles/gui.dir/layout.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui.dir/layout.cpp.i"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\GUI\layout.cpp > CMakeFiles\gui.dir\layout.cpp.i

GUI/CMakeFiles/gui.dir/layout.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui.dir/layout.cpp.s"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\GUI\layout.cpp -o CMakeFiles\gui.dir\layout.cpp.s

GUI/CMakeFiles/gui.dir/localization.cpp.obj: GUI/CMakeFiles/gui.dir/flags.make
GUI/CMakeFiles/gui.dir/localization.cpp.obj: GUI/CMakeFiles/gui.dir/includes_CXX.rsp
GUI/CMakeFiles/gui.dir/localization.cpp.obj: ../GUI/localization.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object GUI/CMakeFiles/gui.dir/localization.cpp.obj"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gui.dir\localization.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\GUI\localization.cpp

GUI/CMakeFiles/gui.dir/localization.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui.dir/localization.cpp.i"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\GUI\localization.cpp > CMakeFiles\gui.dir\localization.cpp.i

GUI/CMakeFiles/gui.dir/localization.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui.dir/localization.cpp.s"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\GUI\localization.cpp -o CMakeFiles\gui.dir\localization.cpp.s

GUI/CMakeFiles/gui.dir/pugixml/pugixml.cpp.obj: GUI/CMakeFiles/gui.dir/flags.make
GUI/CMakeFiles/gui.dir/pugixml/pugixml.cpp.obj: GUI/CMakeFiles/gui.dir/includes_CXX.rsp
GUI/CMakeFiles/gui.dir/pugixml/pugixml.cpp.obj: ../GUI/pugixml/pugixml.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object GUI/CMakeFiles/gui.dir/pugixml/pugixml.cpp.obj"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gui.dir\pugixml\pugixml.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\GUI\pugixml\pugixml.cpp

GUI/CMakeFiles/gui.dir/pugixml/pugixml.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui.dir/pugixml/pugixml.cpp.i"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\GUI\pugixml\pugixml.cpp > CMakeFiles\gui.dir\pugixml\pugixml.cpp.i

GUI/CMakeFiles/gui.dir/pugixml/pugixml.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui.dir/pugixml/pugixml.cpp.s"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\GUI\pugixml\pugixml.cpp -o CMakeFiles\gui.dir\pugixml\pugixml.cpp.s

GUI/CMakeFiles/gui.dir/renderer.cpp.obj: GUI/CMakeFiles/gui.dir/flags.make
GUI/CMakeFiles/gui.dir/renderer.cpp.obj: GUI/CMakeFiles/gui.dir/includes_CXX.rsp
GUI/CMakeFiles/gui.dir/renderer.cpp.obj: ../GUI/renderer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object GUI/CMakeFiles/gui.dir/renderer.cpp.obj"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gui.dir\renderer.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\GUI\renderer.cpp

GUI/CMakeFiles/gui.dir/renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui.dir/renderer.cpp.i"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\GUI\renderer.cpp > CMakeFiles\gui.dir\renderer.cpp.i

GUI/CMakeFiles/gui.dir/renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui.dir/renderer.cpp.s"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\GUI\renderer.cpp -o CMakeFiles\gui.dir\renderer.cpp.s

GUI/CMakeFiles/gui.dir/stb.cpp.obj: GUI/CMakeFiles/gui.dir/flags.make
GUI/CMakeFiles/gui.dir/stb.cpp.obj: GUI/CMakeFiles/gui.dir/includes_CXX.rsp
GUI/CMakeFiles/gui.dir/stb.cpp.obj: ../GUI/stb.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object GUI/CMakeFiles/gui.dir/stb.cpp.obj"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gui.dir\stb.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\GUI\stb.cpp

GUI/CMakeFiles/gui.dir/stb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui.dir/stb.cpp.i"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\GUI\stb.cpp > CMakeFiles\gui.dir\stb.cpp.i

GUI/CMakeFiles/gui.dir/stb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui.dir/stb.cpp.s"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\GUI\stb.cpp -o CMakeFiles\gui.dir\stb.cpp.s

GUI/CMakeFiles/gui.dir/widgets/button.cpp.obj: GUI/CMakeFiles/gui.dir/flags.make
GUI/CMakeFiles/gui.dir/widgets/button.cpp.obj: GUI/CMakeFiles/gui.dir/includes_CXX.rsp
GUI/CMakeFiles/gui.dir/widgets/button.cpp.obj: ../GUI/widgets/button.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object GUI/CMakeFiles/gui.dir/widgets/button.cpp.obj"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gui.dir\widgets\button.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\button.cpp

GUI/CMakeFiles/gui.dir/widgets/button.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui.dir/widgets/button.cpp.i"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\button.cpp > CMakeFiles\gui.dir\widgets\button.cpp.i

GUI/CMakeFiles/gui.dir/widgets/button.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui.dir/widgets/button.cpp.s"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\button.cpp -o CMakeFiles\gui.dir\widgets\button.cpp.s

GUI/CMakeFiles/gui.dir/widgets/check.cpp.obj: GUI/CMakeFiles/gui.dir/flags.make
GUI/CMakeFiles/gui.dir/widgets/check.cpp.obj: GUI/CMakeFiles/gui.dir/includes_CXX.rsp
GUI/CMakeFiles/gui.dir/widgets/check.cpp.obj: ../GUI/widgets/check.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object GUI/CMakeFiles/gui.dir/widgets/check.cpp.obj"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gui.dir\widgets\check.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\check.cpp

GUI/CMakeFiles/gui.dir/widgets/check.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui.dir/widgets/check.cpp.i"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\check.cpp > CMakeFiles\gui.dir\widgets\check.cpp.i

GUI/CMakeFiles/gui.dir/widgets/check.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui.dir/widgets/check.cpp.s"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\check.cpp -o CMakeFiles\gui.dir\widgets\check.cpp.s

GUI/CMakeFiles/gui.dir/widgets/imageview.cpp.obj: GUI/CMakeFiles/gui.dir/flags.make
GUI/CMakeFiles/gui.dir/widgets/imageview.cpp.obj: GUI/CMakeFiles/gui.dir/includes_CXX.rsp
GUI/CMakeFiles/gui.dir/widgets/imageview.cpp.obj: ../GUI/widgets/imageview.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object GUI/CMakeFiles/gui.dir/widgets/imageview.cpp.obj"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gui.dir\widgets\imageview.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\imageview.cpp

GUI/CMakeFiles/gui.dir/widgets/imageview.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui.dir/widgets/imageview.cpp.i"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\imageview.cpp > CMakeFiles\gui.dir\widgets\imageview.cpp.i

GUI/CMakeFiles/gui.dir/widgets/imageview.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui.dir/widgets/imageview.cpp.s"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\imageview.cpp -o CMakeFiles\gui.dir\widgets\imageview.cpp.s

GUI/CMakeFiles/gui.dir/widgets/label.cpp.obj: GUI/CMakeFiles/gui.dir/flags.make
GUI/CMakeFiles/gui.dir/widgets/label.cpp.obj: GUI/CMakeFiles/gui.dir/includes_CXX.rsp
GUI/CMakeFiles/gui.dir/widgets/label.cpp.obj: ../GUI/widgets/label.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object GUI/CMakeFiles/gui.dir/widgets/label.cpp.obj"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gui.dir\widgets\label.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\label.cpp

GUI/CMakeFiles/gui.dir/widgets/label.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui.dir/widgets/label.cpp.i"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\label.cpp > CMakeFiles\gui.dir\widgets\label.cpp.i

GUI/CMakeFiles/gui.dir/widgets/label.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui.dir/widgets/label.cpp.s"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\label.cpp -o CMakeFiles\gui.dir\widgets\label.cpp.s

GUI/CMakeFiles/gui.dir/widgets/list.cpp.obj: GUI/CMakeFiles/gui.dir/flags.make
GUI/CMakeFiles/gui.dir/widgets/list.cpp.obj: GUI/CMakeFiles/gui.dir/includes_CXX.rsp
GUI/CMakeFiles/gui.dir/widgets/list.cpp.obj: ../GUI/widgets/list.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object GUI/CMakeFiles/gui.dir/widgets/list.cpp.obj"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gui.dir\widgets\list.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\list.cpp

GUI/CMakeFiles/gui.dir/widgets/list.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui.dir/widgets/list.cpp.i"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\list.cpp > CMakeFiles\gui.dir\widgets\list.cpp.i

GUI/CMakeFiles/gui.dir/widgets/list.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui.dir/widgets/list.cpp.s"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\list.cpp -o CMakeFiles\gui.dir\widgets\list.cpp.s

GUI/CMakeFiles/gui.dir/widgets/panel.cpp.obj: GUI/CMakeFiles/gui.dir/flags.make
GUI/CMakeFiles/gui.dir/widgets/panel.cpp.obj: GUI/CMakeFiles/gui.dir/includes_CXX.rsp
GUI/CMakeFiles/gui.dir/widgets/panel.cpp.obj: ../GUI/widgets/panel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object GUI/CMakeFiles/gui.dir/widgets/panel.cpp.obj"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gui.dir\widgets\panel.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\panel.cpp

GUI/CMakeFiles/gui.dir/widgets/panel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui.dir/widgets/panel.cpp.i"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\panel.cpp > CMakeFiles\gui.dir\widgets\panel.cpp.i

GUI/CMakeFiles/gui.dir/widgets/panel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui.dir/widgets/panel.cpp.s"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\panel.cpp -o CMakeFiles\gui.dir\widgets\panel.cpp.s

GUI/CMakeFiles/gui.dir/widgets/scroll.cpp.obj: GUI/CMakeFiles/gui.dir/flags.make
GUI/CMakeFiles/gui.dir/widgets/scroll.cpp.obj: GUI/CMakeFiles/gui.dir/includes_CXX.rsp
GUI/CMakeFiles/gui.dir/widgets/scroll.cpp.obj: ../GUI/widgets/scroll.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object GUI/CMakeFiles/gui.dir/widgets/scroll.cpp.obj"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gui.dir\widgets\scroll.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\scroll.cpp

GUI/CMakeFiles/gui.dir/widgets/scroll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui.dir/widgets/scroll.cpp.i"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\scroll.cpp > CMakeFiles\gui.dir\widgets\scroll.cpp.i

GUI/CMakeFiles/gui.dir/widgets/scroll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui.dir/widgets/scroll.cpp.s"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\scroll.cpp -o CMakeFiles\gui.dir\widgets\scroll.cpp.s

GUI/CMakeFiles/gui.dir/widgets/scrollview.cpp.obj: GUI/CMakeFiles/gui.dir/flags.make
GUI/CMakeFiles/gui.dir/widgets/scrollview.cpp.obj: GUI/CMakeFiles/gui.dir/includes_CXX.rsp
GUI/CMakeFiles/gui.dir/widgets/scrollview.cpp.obj: ../GUI/widgets/scrollview.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building CXX object GUI/CMakeFiles/gui.dir/widgets/scrollview.cpp.obj"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gui.dir\widgets\scrollview.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\scrollview.cpp

GUI/CMakeFiles/gui.dir/widgets/scrollview.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui.dir/widgets/scrollview.cpp.i"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\scrollview.cpp > CMakeFiles\gui.dir\widgets\scrollview.cpp.i

GUI/CMakeFiles/gui.dir/widgets/scrollview.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui.dir/widgets/scrollview.cpp.s"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\scrollview.cpp -o CMakeFiles\gui.dir\widgets\scrollview.cpp.s

GUI/CMakeFiles/gui.dir/widgets/spinner.cpp.obj: GUI/CMakeFiles/gui.dir/flags.make
GUI/CMakeFiles/gui.dir/widgets/spinner.cpp.obj: GUI/CMakeFiles/gui.dir/includes_CXX.rsp
GUI/CMakeFiles/gui.dir/widgets/spinner.cpp.obj: ../GUI/widgets/spinner.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Building CXX object GUI/CMakeFiles/gui.dir/widgets/spinner.cpp.obj"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gui.dir\widgets\spinner.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\spinner.cpp

GUI/CMakeFiles/gui.dir/widgets/spinner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui.dir/widgets/spinner.cpp.i"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\spinner.cpp > CMakeFiles\gui.dir\widgets\spinner.cpp.i

GUI/CMakeFiles/gui.dir/widgets/spinner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui.dir/widgets/spinner.cpp.s"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\spinner.cpp -o CMakeFiles\gui.dir\widgets\spinner.cpp.s

GUI/CMakeFiles/gui.dir/widgets/splitview.cpp.obj: GUI/CMakeFiles/gui.dir/flags.make
GUI/CMakeFiles/gui.dir/widgets/splitview.cpp.obj: GUI/CMakeFiles/gui.dir/includes_CXX.rsp
GUI/CMakeFiles/gui.dir/widgets/splitview.cpp.obj: ../GUI/widgets/splitview.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_20) "Building CXX object GUI/CMakeFiles/gui.dir/widgets/splitview.cpp.obj"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gui.dir\widgets\splitview.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\splitview.cpp

GUI/CMakeFiles/gui.dir/widgets/splitview.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui.dir/widgets/splitview.cpp.i"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\splitview.cpp > CMakeFiles\gui.dir\widgets\splitview.cpp.i

GUI/CMakeFiles/gui.dir/widgets/splitview.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui.dir/widgets/splitview.cpp.s"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\splitview.cpp -o CMakeFiles\gui.dir\widgets\splitview.cpp.s

GUI/CMakeFiles/gui.dir/widgets/widget.cpp.obj: GUI/CMakeFiles/gui.dir/flags.make
GUI/CMakeFiles/gui.dir/widgets/widget.cpp.obj: GUI/CMakeFiles/gui.dir/includes_CXX.rsp
GUI/CMakeFiles/gui.dir/widgets/widget.cpp.obj: ../GUI/widgets/widget.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_21) "Building CXX object GUI/CMakeFiles/gui.dir/widgets/widget.cpp.obj"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gui.dir\widgets\widget.cpp.obj -c C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\widget.cpp

GUI/CMakeFiles/gui.dir/widgets/widget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui.dir/widgets/widget.cpp.i"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\widget.cpp > CMakeFiles\gui.dir\widgets\widget.cpp.i

GUI/CMakeFiles/gui.dir/widgets/widget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui.dir/widgets/widget.cpp.s"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Twister\Projects\cpp\cgproject\GUI\widgets\widget.cpp -o CMakeFiles\gui.dir\widgets\widget.cpp.s

# Object files for target gui
gui_OBJECTS = \
"CMakeFiles/gui.dir/application.cpp.obj" \
"CMakeFiles/gui.dir/events.cpp.obj" \
"CMakeFiles/gui.dir/glad/glad.c.obj" \
"CMakeFiles/gui.dir/gui.cpp.obj" \
"CMakeFiles/gui.dir/image.cpp.obj" \
"CMakeFiles/gui.dir/layout.cpp.obj" \
"CMakeFiles/gui.dir/localization.cpp.obj" \
"CMakeFiles/gui.dir/pugixml/pugixml.cpp.obj" \
"CMakeFiles/gui.dir/renderer.cpp.obj" \
"CMakeFiles/gui.dir/stb.cpp.obj" \
"CMakeFiles/gui.dir/widgets/button.cpp.obj" \
"CMakeFiles/gui.dir/widgets/check.cpp.obj" \
"CMakeFiles/gui.dir/widgets/imageview.cpp.obj" \
"CMakeFiles/gui.dir/widgets/label.cpp.obj" \
"CMakeFiles/gui.dir/widgets/list.cpp.obj" \
"CMakeFiles/gui.dir/widgets/panel.cpp.obj" \
"CMakeFiles/gui.dir/widgets/scroll.cpp.obj" \
"CMakeFiles/gui.dir/widgets/scrollview.cpp.obj" \
"CMakeFiles/gui.dir/widgets/spinner.cpp.obj" \
"CMakeFiles/gui.dir/widgets/splitview.cpp.obj" \
"CMakeFiles/gui.dir/widgets/widget.cpp.obj"

# External object files for target gui
gui_EXTERNAL_OBJECTS =

GUI/libgui.a: GUI/CMakeFiles/gui.dir/application.cpp.obj
GUI/libgui.a: GUI/CMakeFiles/gui.dir/events.cpp.obj
GUI/libgui.a: GUI/CMakeFiles/gui.dir/glad/glad.c.obj
GUI/libgui.a: GUI/CMakeFiles/gui.dir/gui.cpp.obj
GUI/libgui.a: GUI/CMakeFiles/gui.dir/image.cpp.obj
GUI/libgui.a: GUI/CMakeFiles/gui.dir/layout.cpp.obj
GUI/libgui.a: GUI/CMakeFiles/gui.dir/localization.cpp.obj
GUI/libgui.a: GUI/CMakeFiles/gui.dir/pugixml/pugixml.cpp.obj
GUI/libgui.a: GUI/CMakeFiles/gui.dir/renderer.cpp.obj
GUI/libgui.a: GUI/CMakeFiles/gui.dir/stb.cpp.obj
GUI/libgui.a: GUI/CMakeFiles/gui.dir/widgets/button.cpp.obj
GUI/libgui.a: GUI/CMakeFiles/gui.dir/widgets/check.cpp.obj
GUI/libgui.a: GUI/CMakeFiles/gui.dir/widgets/imageview.cpp.obj
GUI/libgui.a: GUI/CMakeFiles/gui.dir/widgets/label.cpp.obj
GUI/libgui.a: GUI/CMakeFiles/gui.dir/widgets/list.cpp.obj
GUI/libgui.a: GUI/CMakeFiles/gui.dir/widgets/panel.cpp.obj
GUI/libgui.a: GUI/CMakeFiles/gui.dir/widgets/scroll.cpp.obj
GUI/libgui.a: GUI/CMakeFiles/gui.dir/widgets/scrollview.cpp.obj
GUI/libgui.a: GUI/CMakeFiles/gui.dir/widgets/spinner.cpp.obj
GUI/libgui.a: GUI/CMakeFiles/gui.dir/widgets/splitview.cpp.obj
GUI/libgui.a: GUI/CMakeFiles/gui.dir/widgets/widget.cpp.obj
GUI/libgui.a: GUI/CMakeFiles/gui.dir/build.make
GUI/libgui.a: GUI/CMakeFiles/gui.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_22) "Linking CXX static library libgui.a"
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && $(CMAKE_COMMAND) -P CMakeFiles\gui.dir\cmake_clean_target.cmake
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\gui.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
GUI/CMakeFiles/gui.dir/build: GUI/libgui.a

.PHONY : GUI/CMakeFiles/gui.dir/build

GUI/CMakeFiles/gui.dir/clean:
	cd /d C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI && $(CMAKE_COMMAND) -P CMakeFiles\gui.dir\cmake_clean.cmake
.PHONY : GUI/CMakeFiles/gui.dir/clean

GUI/CMakeFiles/gui.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Twister\Projects\cpp\cgproject C:\Users\Twister\Projects\cpp\cgproject\GUI C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI C:\Users\Twister\Projects\cpp\cgproject\RelWithDebInfo\GUI\CMakeFiles\gui.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : GUI/CMakeFiles/gui.dir/depend

