# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Briana\CLionProjects\UDP_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Briana\CLionProjects\UDP_server\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/UDP_server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/UDP_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/UDP_server.dir/flags.make

CMakeFiles/UDP_server.dir/main.cpp.obj: CMakeFiles/UDP_server.dir/flags.make
CMakeFiles/UDP_server.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Briana\CLionProjects\UDP_server\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/UDP_server.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\UDP_server.dir\main.cpp.obj -c C:\Users\Briana\CLionProjects\UDP_server\main.cpp

CMakeFiles/UDP_server.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/UDP_server.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Briana\CLionProjects\UDP_server\main.cpp > CMakeFiles\UDP_server.dir\main.cpp.i

CMakeFiles/UDP_server.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/UDP_server.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Briana\CLionProjects\UDP_server\main.cpp -o CMakeFiles\UDP_server.dir\main.cpp.s

# Object files for target UDP_server
UDP_server_OBJECTS = \
"CMakeFiles/UDP_server.dir/main.cpp.obj"

# External object files for target UDP_server
UDP_server_EXTERNAL_OBJECTS =

UDP_server.exe: CMakeFiles/UDP_server.dir/main.cpp.obj
UDP_server.exe: CMakeFiles/UDP_server.dir/build.make
UDP_server.exe: CMakeFiles/UDP_server.dir/linklibs.rsp
UDP_server.exe: CMakeFiles/UDP_server.dir/objects1.rsp
UDP_server.exe: CMakeFiles/UDP_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Briana\CLionProjects\UDP_server\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable UDP_server.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\UDP_server.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/UDP_server.dir/build: UDP_server.exe

.PHONY : CMakeFiles/UDP_server.dir/build

CMakeFiles/UDP_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\UDP_server.dir\cmake_clean.cmake
.PHONY : CMakeFiles/UDP_server.dir/clean

CMakeFiles/UDP_server.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Briana\CLionProjects\UDP_server C:\Users\Briana\CLionProjects\UDP_server C:\Users\Briana\CLionProjects\UDP_server\cmake-build-debug C:\Users\Briana\CLionProjects\UDP_server\cmake-build-debug C:\Users\Briana\CLionProjects\UDP_server\cmake-build-debug\CMakeFiles\UDP_server.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/UDP_server.dir/depend
