# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /home/jessieeisenberg/Documents/GitHub/Comms/Spoofing/UAVMessage

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jessieeisenberg/Documents/GitHub/Comms/Spoofing/UAVMessage/build

# Include any dependencies generated for this target.
include CMakeFiles/UAVtest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/UAVtest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/UAVtest.dir/flags.make

CMakeFiles/UAVtest.dir/UAVMessage/fromGCS.cpp.o: CMakeFiles/UAVtest.dir/flags.make
CMakeFiles/UAVtest.dir/UAVMessage/fromGCS.cpp.o: ../UAVMessage/fromGCS.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jessieeisenberg/Documents/GitHub/Comms/Spoofing/UAVMessage/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/UAVtest.dir/UAVMessage/fromGCS.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/UAVtest.dir/UAVMessage/fromGCS.cpp.o -c /home/jessieeisenberg/Documents/GitHub/Comms/Spoofing/UAVMessage/UAVMessage/fromGCS.cpp

CMakeFiles/UAVtest.dir/UAVMessage/fromGCS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/UAVtest.dir/UAVMessage/fromGCS.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jessieeisenberg/Documents/GitHub/Comms/Spoofing/UAVMessage/UAVMessage/fromGCS.cpp > CMakeFiles/UAVtest.dir/UAVMessage/fromGCS.cpp.i

CMakeFiles/UAVtest.dir/UAVMessage/fromGCS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/UAVtest.dir/UAVMessage/fromGCS.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jessieeisenberg/Documents/GitHub/Comms/Spoofing/UAVMessage/UAVMessage/fromGCS.cpp -o CMakeFiles/UAVtest.dir/UAVMessage/fromGCS.cpp.s

CMakeFiles/UAVtest.dir/UAVMessage/fromGCS.cpp.o.requires:
.PHONY : CMakeFiles/UAVtest.dir/UAVMessage/fromGCS.cpp.o.requires

CMakeFiles/UAVtest.dir/UAVMessage/fromGCS.cpp.o.provides: CMakeFiles/UAVtest.dir/UAVMessage/fromGCS.cpp.o.requires
	$(MAKE) -f CMakeFiles/UAVtest.dir/build.make CMakeFiles/UAVtest.dir/UAVMessage/fromGCS.cpp.o.provides.build
.PHONY : CMakeFiles/UAVtest.dir/UAVMessage/fromGCS.cpp.o.provides

CMakeFiles/UAVtest.dir/UAVMessage/fromGCS.cpp.o.provides.build: CMakeFiles/UAVtest.dir/UAVMessage/fromGCS.cpp.o

CMakeFiles/UAVtest.dir/UAVMessage/main.cpp.o: CMakeFiles/UAVtest.dir/flags.make
CMakeFiles/UAVtest.dir/UAVMessage/main.cpp.o: ../UAVMessage/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jessieeisenberg/Documents/GitHub/Comms/Spoofing/UAVMessage/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/UAVtest.dir/UAVMessage/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/UAVtest.dir/UAVMessage/main.cpp.o -c /home/jessieeisenberg/Documents/GitHub/Comms/Spoofing/UAVMessage/UAVMessage/main.cpp

CMakeFiles/UAVtest.dir/UAVMessage/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/UAVtest.dir/UAVMessage/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jessieeisenberg/Documents/GitHub/Comms/Spoofing/UAVMessage/UAVMessage/main.cpp > CMakeFiles/UAVtest.dir/UAVMessage/main.cpp.i

CMakeFiles/UAVtest.dir/UAVMessage/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/UAVtest.dir/UAVMessage/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jessieeisenberg/Documents/GitHub/Comms/Spoofing/UAVMessage/UAVMessage/main.cpp -o CMakeFiles/UAVtest.dir/UAVMessage/main.cpp.s

CMakeFiles/UAVtest.dir/UAVMessage/main.cpp.o.requires:
.PHONY : CMakeFiles/UAVtest.dir/UAVMessage/main.cpp.o.requires

CMakeFiles/UAVtest.dir/UAVMessage/main.cpp.o.provides: CMakeFiles/UAVtest.dir/UAVMessage/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/UAVtest.dir/build.make CMakeFiles/UAVtest.dir/UAVMessage/main.cpp.o.provides.build
.PHONY : CMakeFiles/UAVtest.dir/UAVMessage/main.cpp.o.provides

CMakeFiles/UAVtest.dir/UAVMessage/main.cpp.o.provides.build: CMakeFiles/UAVtest.dir/UAVMessage/main.cpp.o

# Object files for target UAVtest
UAVtest_OBJECTS = \
"CMakeFiles/UAVtest.dir/UAVMessage/fromGCS.cpp.o" \
"CMakeFiles/UAVtest.dir/UAVMessage/main.cpp.o"

# External object files for target UAVtest
UAVtest_EXTERNAL_OBJECTS =

UAVtest: CMakeFiles/UAVtest.dir/UAVMessage/fromGCS.cpp.o
UAVtest: CMakeFiles/UAVtest.dir/UAVMessage/main.cpp.o
UAVtest: CMakeFiles/UAVtest.dir/build.make
UAVtest: ../../../build/linux/libNGCP_COM.a
UAVtest: ../../../cryptopp563/linux/libcryptopp.a
UAVtest: ../../../libxbee3-3.0.11/linux/libxbee.so
UAVtest: CMakeFiles/UAVtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable UAVtest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/UAVtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/UAVtest.dir/build: UAVtest
.PHONY : CMakeFiles/UAVtest.dir/build

CMakeFiles/UAVtest.dir/requires: CMakeFiles/UAVtest.dir/UAVMessage/fromGCS.cpp.o.requires
CMakeFiles/UAVtest.dir/requires: CMakeFiles/UAVtest.dir/UAVMessage/main.cpp.o.requires
.PHONY : CMakeFiles/UAVtest.dir/requires

CMakeFiles/UAVtest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/UAVtest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/UAVtest.dir/clean

CMakeFiles/UAVtest.dir/depend:
	cd /home/jessieeisenberg/Documents/GitHub/Comms/Spoofing/UAVMessage/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jessieeisenberg/Documents/GitHub/Comms/Spoofing/UAVMessage /home/jessieeisenberg/Documents/GitHub/Comms/Spoofing/UAVMessage /home/jessieeisenberg/Documents/GitHub/Comms/Spoofing/UAVMessage/build /home/jessieeisenberg/Documents/GitHub/Comms/Spoofing/UAVMessage/build /home/jessieeisenberg/Documents/GitHub/Comms/Spoofing/UAVMessage/build/CMakeFiles/UAVtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/UAVtest.dir/depend

