# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dohyeon/servingbot

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dohyeon/servingbot/build

# Include any dependencies generated for this target.
include CMakeFiles/serial_reader.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/serial_reader.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/serial_reader.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/serial_reader.dir/flags.make

CMakeFiles/serial_reader.dir/read.cpp.o: CMakeFiles/serial_reader.dir/flags.make
CMakeFiles/serial_reader.dir/read.cpp.o: ../read.cpp
CMakeFiles/serial_reader.dir/read.cpp.o: CMakeFiles/serial_reader.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dohyeon/servingbot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/serial_reader.dir/read.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/serial_reader.dir/read.cpp.o -MF CMakeFiles/serial_reader.dir/read.cpp.o.d -o CMakeFiles/serial_reader.dir/read.cpp.o -c /home/dohyeon/servingbot/read.cpp

CMakeFiles/serial_reader.dir/read.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serial_reader.dir/read.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dohyeon/servingbot/read.cpp > CMakeFiles/serial_reader.dir/read.cpp.i

CMakeFiles/serial_reader.dir/read.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serial_reader.dir/read.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dohyeon/servingbot/read.cpp -o CMakeFiles/serial_reader.dir/read.cpp.s

# Object files for target serial_reader
serial_reader_OBJECTS = \
"CMakeFiles/serial_reader.dir/read.cpp.o"

# External object files for target serial_reader
serial_reader_EXTERNAL_OBJECTS =

serial_reader: CMakeFiles/serial_reader.dir/read.cpp.o
serial_reader: CMakeFiles/serial_reader.dir/build.make
serial_reader: /home/dohyeon/anaconda3/lib/libboost_system.so.1.82.0
serial_reader: /home/dohyeon/anaconda3/lib/libboost_thread.so.1.82.0
serial_reader: /home/dohyeon/anaconda3/lib/libboost_chrono.so.1.82.0
serial_reader: ../libtorch/lib/libtorch.so
serial_reader: ../libtorch/lib/libc10.so
serial_reader: ../libtorch/lib/libkineto.a
serial_reader: ../libtorch/lib/libc10.so
serial_reader: CMakeFiles/serial_reader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dohyeon/servingbot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable serial_reader"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serial_reader.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/serial_reader.dir/build: serial_reader
.PHONY : CMakeFiles/serial_reader.dir/build

CMakeFiles/serial_reader.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/serial_reader.dir/cmake_clean.cmake
.PHONY : CMakeFiles/serial_reader.dir/clean

CMakeFiles/serial_reader.dir/depend:
	cd /home/dohyeon/servingbot/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dohyeon/servingbot /home/dohyeon/servingbot /home/dohyeon/servingbot/build /home/dohyeon/servingbot/build /home/dohyeon/servingbot/build/CMakeFiles/serial_reader.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/serial_reader.dir/depend

