# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/debian/embedded/desktop/vim/wxWidgetsModbusLib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/build/Win

# Include any dependencies generated for this target.
include CMakeFiles/wxModbus.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/wxModbus.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wxModbus.dir/flags.make

CMakeFiles/wxModbus.dir/src/dialog.cpp.o: CMakeFiles/wxModbus.dir/flags.make
CMakeFiles/wxModbus.dir/src/dialog.cpp.o: ../../src/dialog.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/debian/embedded/desktop/vim/wxWidgetsModbusLib/build/Win/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/wxModbus.dir/src/dialog.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wxModbus.dir/src/dialog.cpp.o -c /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/src/dialog.cpp

CMakeFiles/wxModbus.dir/src/dialog.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wxModbus.dir/src/dialog.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/src/dialog.cpp > CMakeFiles/wxModbus.dir/src/dialog.cpp.i

CMakeFiles/wxModbus.dir/src/dialog.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wxModbus.dir/src/dialog.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/src/dialog.cpp -o CMakeFiles/wxModbus.dir/src/dialog.cpp.s

CMakeFiles/wxModbus.dir/src/main.cpp.o: CMakeFiles/wxModbus.dir/flags.make
CMakeFiles/wxModbus.dir/src/main.cpp.o: ../../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/debian/embedded/desktop/vim/wxWidgetsModbusLib/build/Win/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/wxModbus.dir/src/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wxModbus.dir/src/main.cpp.o -c /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/src/main.cpp

CMakeFiles/wxModbus.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wxModbus.dir/src/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/src/main.cpp > CMakeFiles/wxModbus.dir/src/main.cpp.i

CMakeFiles/wxModbus.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wxModbus.dir/src/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/src/main.cpp -o CMakeFiles/wxModbus.dir/src/main.cpp.s

CMakeFiles/wxModbus.dir/src/mainframe.cpp.o: CMakeFiles/wxModbus.dir/flags.make
CMakeFiles/wxModbus.dir/src/mainframe.cpp.o: ../../src/mainframe.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/debian/embedded/desktop/vim/wxWidgetsModbusLib/build/Win/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/wxModbus.dir/src/mainframe.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wxModbus.dir/src/mainframe.cpp.o -c /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/src/mainframe.cpp

CMakeFiles/wxModbus.dir/src/mainframe.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wxModbus.dir/src/mainframe.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/src/mainframe.cpp > CMakeFiles/wxModbus.dir/src/mainframe.cpp.i

CMakeFiles/wxModbus.dir/src/mainframe.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wxModbus.dir/src/mainframe.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/src/mainframe.cpp -o CMakeFiles/wxModbus.dir/src/mainframe.cpp.s

CMakeFiles/wxModbus.dir/src/modbus-data.c.o: CMakeFiles/wxModbus.dir/flags.make
CMakeFiles/wxModbus.dir/src/modbus-data.c.o: ../../src/modbus-data.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/debian/embedded/desktop/vim/wxWidgetsModbusLib/build/Win/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/wxModbus.dir/src/modbus-data.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wxModbus.dir/src/modbus-data.c.o -c /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/src/modbus-data.c

CMakeFiles/wxModbus.dir/src/modbus-data.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wxModbus.dir/src/modbus-data.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/src/modbus-data.c > CMakeFiles/wxModbus.dir/src/modbus-data.c.i

CMakeFiles/wxModbus.dir/src/modbus-data.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wxModbus.dir/src/modbus-data.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/src/modbus-data.c -o CMakeFiles/wxModbus.dir/src/modbus-data.c.s

CMakeFiles/wxModbus.dir/src/modbus-rtu.c.o: CMakeFiles/wxModbus.dir/flags.make
CMakeFiles/wxModbus.dir/src/modbus-rtu.c.o: ../../src/modbus-rtu.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/debian/embedded/desktop/vim/wxWidgetsModbusLib/build/Win/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/wxModbus.dir/src/modbus-rtu.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wxModbus.dir/src/modbus-rtu.c.o -c /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/src/modbus-rtu.c

CMakeFiles/wxModbus.dir/src/modbus-rtu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wxModbus.dir/src/modbus-rtu.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/src/modbus-rtu.c > CMakeFiles/wxModbus.dir/src/modbus-rtu.c.i

CMakeFiles/wxModbus.dir/src/modbus-rtu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wxModbus.dir/src/modbus-rtu.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/src/modbus-rtu.c -o CMakeFiles/wxModbus.dir/src/modbus-rtu.c.s

CMakeFiles/wxModbus.dir/src/modbus.c.o: CMakeFiles/wxModbus.dir/flags.make
CMakeFiles/wxModbus.dir/src/modbus.c.o: ../../src/modbus.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/debian/embedded/desktop/vim/wxWidgetsModbusLib/build/Win/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/wxModbus.dir/src/modbus.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wxModbus.dir/src/modbus.c.o -c /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/src/modbus.c

CMakeFiles/wxModbus.dir/src/modbus.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wxModbus.dir/src/modbus.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/src/modbus.c > CMakeFiles/wxModbus.dir/src/modbus.c.i

CMakeFiles/wxModbus.dir/src/modbus.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wxModbus.dir/src/modbus.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/src/modbus.c -o CMakeFiles/wxModbus.dir/src/modbus.c.s

# Object files for target wxModbus
wxModbus_OBJECTS = \
"CMakeFiles/wxModbus.dir/src/dialog.cpp.o" \
"CMakeFiles/wxModbus.dir/src/main.cpp.o" \
"CMakeFiles/wxModbus.dir/src/mainframe.cpp.o" \
"CMakeFiles/wxModbus.dir/src/modbus-data.c.o" \
"CMakeFiles/wxModbus.dir/src/modbus-rtu.c.o" \
"CMakeFiles/wxModbus.dir/src/modbus.c.o"

# External object files for target wxModbus
wxModbus_EXTERNAL_OBJECTS =

wxModbus: CMakeFiles/wxModbus.dir/src/dialog.cpp.o
wxModbus: CMakeFiles/wxModbus.dir/src/main.cpp.o
wxModbus: CMakeFiles/wxModbus.dir/src/mainframe.cpp.o
wxModbus: CMakeFiles/wxModbus.dir/src/modbus-data.c.o
wxModbus: CMakeFiles/wxModbus.dir/src/modbus-rtu.c.o
wxModbus: CMakeFiles/wxModbus.dir/src/modbus.c.o
wxModbus: CMakeFiles/wxModbus.dir/build.make
wxModbus: CMakeFiles/wxModbus.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/debian/embedded/desktop/vim/wxWidgetsModbusLib/build/Win/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable wxModbus"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wxModbus.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wxModbus.dir/build: wxModbus

.PHONY : CMakeFiles/wxModbus.dir/build

CMakeFiles/wxModbus.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/wxModbus.dir/cmake_clean.cmake
.PHONY : CMakeFiles/wxModbus.dir/clean

CMakeFiles/wxModbus.dir/depend:
	cd /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/build/Win && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/debian/embedded/desktop/vim/wxWidgetsModbusLib /home/debian/embedded/desktop/vim/wxWidgetsModbusLib /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/build/Win /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/build/Win /home/debian/embedded/desktop/vim/wxWidgetsModbusLib/build/Win/CMakeFiles/wxModbus.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/wxModbus.dir/depend

