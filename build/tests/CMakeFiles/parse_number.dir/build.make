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
include tests/CMakeFiles/parse_number.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/parse_number.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/parse_number.dir/flags.make

tests/CMakeFiles/parse_number.dir/parse_number.c.o: tests/CMakeFiles/parse_number.dir/flags.make
tests/CMakeFiles/parse_number.dir/parse_number.c.o: /workspaces/CEW-OEL/cJSON/tests/parse_number.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/CEW-OEL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/parse_number.dir/parse_number.c.o"
	cd /workspaces/CEW-OEL/build/tests && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/parse_number.dir/parse_number.c.o   -c /workspaces/CEW-OEL/cJSON/tests/parse_number.c

tests/CMakeFiles/parse_number.dir/parse_number.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/parse_number.dir/parse_number.c.i"
	cd /workspaces/CEW-OEL/build/tests && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspaces/CEW-OEL/cJSON/tests/parse_number.c > CMakeFiles/parse_number.dir/parse_number.c.i

tests/CMakeFiles/parse_number.dir/parse_number.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/parse_number.dir/parse_number.c.s"
	cd /workspaces/CEW-OEL/build/tests && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspaces/CEW-OEL/cJSON/tests/parse_number.c -o CMakeFiles/parse_number.dir/parse_number.c.s

# Object files for target parse_number
parse_number_OBJECTS = \
"CMakeFiles/parse_number.dir/parse_number.c.o"

# External object files for target parse_number
parse_number_EXTERNAL_OBJECTS =

tests/parse_number: tests/CMakeFiles/parse_number.dir/parse_number.c.o
tests/parse_number: tests/CMakeFiles/parse_number.dir/build.make
tests/parse_number: libcjson.so.1.7.17
tests/parse_number: tests/libunity.a
tests/parse_number: tests/CMakeFiles/parse_number.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/CEW-OEL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable parse_number"
	cd /workspaces/CEW-OEL/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/parse_number.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/parse_number.dir/build: tests/parse_number

.PHONY : tests/CMakeFiles/parse_number.dir/build

tests/CMakeFiles/parse_number.dir/clean:
	cd /workspaces/CEW-OEL/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/parse_number.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/parse_number.dir/clean

tests/CMakeFiles/parse_number.dir/depend:
	cd /workspaces/CEW-OEL/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/CEW-OEL/cJSON /workspaces/CEW-OEL/cJSON/tests /workspaces/CEW-OEL/build /workspaces/CEW-OEL/build/tests /workspaces/CEW-OEL/build/tests/CMakeFiles/parse_number.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/parse_number.dir/depend
