# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /workspaces/CEW-OEL/cJSON

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/CEW-OEL/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/print_array.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/print_array.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/print_array.dir/flags.make

tests/CMakeFiles/print_array.dir/print_array.c.o: tests/CMakeFiles/print_array.dir/flags.make
tests/CMakeFiles/print_array.dir/print_array.c.o: /workspaces/CEW-OEL/cJSON/tests/print_array.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/CEW-OEL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/print_array.dir/print_array.c.o"
	cd /workspaces/CEW-OEL/build/tests && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/print_array.dir/print_array.c.o   -c /workspaces/CEW-OEL/cJSON/tests/print_array.c

tests/CMakeFiles/print_array.dir/print_array.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/print_array.dir/print_array.c.i"
	cd /workspaces/CEW-OEL/build/tests && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspaces/CEW-OEL/cJSON/tests/print_array.c > CMakeFiles/print_array.dir/print_array.c.i

tests/CMakeFiles/print_array.dir/print_array.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/print_array.dir/print_array.c.s"
	cd /workspaces/CEW-OEL/build/tests && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspaces/CEW-OEL/cJSON/tests/print_array.c -o CMakeFiles/print_array.dir/print_array.c.s

# Object files for target print_array
print_array_OBJECTS = \
"CMakeFiles/print_array.dir/print_array.c.o"

# External object files for target print_array
print_array_EXTERNAL_OBJECTS =

tests/print_array: tests/CMakeFiles/print_array.dir/print_array.c.o
tests/print_array: tests/CMakeFiles/print_array.dir/build.make
tests/print_array: libcjson.so.1.7.17
tests/print_array: tests/libunity.a
tests/print_array: tests/CMakeFiles/print_array.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/CEW-OEL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable print_array"
	cd /workspaces/CEW-OEL/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/print_array.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/print_array.dir/build: tests/print_array

.PHONY : tests/CMakeFiles/print_array.dir/build

tests/CMakeFiles/print_array.dir/clean:
	cd /workspaces/CEW-OEL/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/print_array.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/print_array.dir/clean

tests/CMakeFiles/print_array.dir/depend:
	cd /workspaces/CEW-OEL/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/CEW-OEL/cJSON /workspaces/CEW-OEL/cJSON/tests /workspaces/CEW-OEL/build /workspaces/CEW-OEL/build/tests /workspaces/CEW-OEL/build/tests/CMakeFiles/print_array.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/print_array.dir/depend

