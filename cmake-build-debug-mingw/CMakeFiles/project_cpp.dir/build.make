# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = C:\Users\filip\AppData\Local\Programs\CLion\bin\cmake\win\x64\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\filip\AppData\Local\Programs\CLion\bin\cmake\win\x64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\filip\CLionProjects\Video-Editor-App

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\filip\CLionProjects\Video-Editor-App\cmake-build-debug-mingw

# Include any dependencies generated for this target.
include CMakeFiles/project_cpp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/project_cpp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/project_cpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/project_cpp.dir/flags.make

project_cpp_autogen/timestamp: D:/QT/6.7.2/mingw_64/./bin/moc.exe
project_cpp_autogen/timestamp: CMakeFiles/project_cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=C:\Users\filip\CLionProjects\Video-Editor-App\cmake-build-debug-mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC for target project_cpp"
	C:\Users\filip\AppData\Local\Programs\CLion\bin\cmake\win\x64\bin\cmake.exe -E cmake_autogen C:/Users/filip/CLionProjects/Video-Editor-App/cmake-build-debug-mingw/CMakeFiles/project_cpp_autogen.dir/AutogenInfo.json Debug
	C:\Users\filip\AppData\Local\Programs\CLion\bin\cmake\win\x64\bin\cmake.exe -E touch C:/Users/filip/CLionProjects/Video-Editor-App/cmake-build-debug-mingw/project_cpp_autogen/timestamp

CMakeFiles/project_cpp.dir/project_cpp_autogen/mocs_compilation.cpp.obj: CMakeFiles/project_cpp.dir/flags.make
CMakeFiles/project_cpp.dir/project_cpp_autogen/mocs_compilation.cpp.obj: CMakeFiles/project_cpp.dir/includes_CXX.rsp
CMakeFiles/project_cpp.dir/project_cpp_autogen/mocs_compilation.cpp.obj: project_cpp_autogen/mocs_compilation.cpp
CMakeFiles/project_cpp.dir/project_cpp_autogen/mocs_compilation.cpp.obj: CMakeFiles/project_cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\filip\CLionProjects\Video-Editor-App\cmake-build-debug-mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/project_cpp.dir/project_cpp_autogen/mocs_compilation.cpp.obj"
	C:\Users\filip\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project_cpp.dir/project_cpp_autogen/mocs_compilation.cpp.obj -MF CMakeFiles\project_cpp.dir\project_cpp_autogen\mocs_compilation.cpp.obj.d -o CMakeFiles\project_cpp.dir\project_cpp_autogen\mocs_compilation.cpp.obj -c C:\Users\filip\CLionProjects\Video-Editor-App\cmake-build-debug-mingw\project_cpp_autogen\mocs_compilation.cpp

CMakeFiles/project_cpp.dir/project_cpp_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/project_cpp.dir/project_cpp_autogen/mocs_compilation.cpp.i"
	C:\Users\filip\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\filip\CLionProjects\Video-Editor-App\cmake-build-debug-mingw\project_cpp_autogen\mocs_compilation.cpp > CMakeFiles\project_cpp.dir\project_cpp_autogen\mocs_compilation.cpp.i

CMakeFiles/project_cpp.dir/project_cpp_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/project_cpp.dir/project_cpp_autogen/mocs_compilation.cpp.s"
	C:\Users\filip\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\filip\CLionProjects\Video-Editor-App\cmake-build-debug-mingw\project_cpp_autogen\mocs_compilation.cpp -o CMakeFiles\project_cpp.dir\project_cpp_autogen\mocs_compilation.cpp.s

CMakeFiles/project_cpp.dir/src/main.cpp.obj: CMakeFiles/project_cpp.dir/flags.make
CMakeFiles/project_cpp.dir/src/main.cpp.obj: CMakeFiles/project_cpp.dir/includes_CXX.rsp
CMakeFiles/project_cpp.dir/src/main.cpp.obj: C:/Users/filip/CLionProjects/Video-Editor-App/src/main.cpp
CMakeFiles/project_cpp.dir/src/main.cpp.obj: CMakeFiles/project_cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\filip\CLionProjects\Video-Editor-App\cmake-build-debug-mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/project_cpp.dir/src/main.cpp.obj"
	C:\Users\filip\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project_cpp.dir/src/main.cpp.obj -MF CMakeFiles\project_cpp.dir\src\main.cpp.obj.d -o CMakeFiles\project_cpp.dir\src\main.cpp.obj -c C:\Users\filip\CLionProjects\Video-Editor-App\src\main.cpp

CMakeFiles/project_cpp.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/project_cpp.dir/src/main.cpp.i"
	C:\Users\filip\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\filip\CLionProjects\Video-Editor-App\src\main.cpp > CMakeFiles\project_cpp.dir\src\main.cpp.i

CMakeFiles/project_cpp.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/project_cpp.dir/src/main.cpp.s"
	C:\Users\filip\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\filip\CLionProjects\Video-Editor-App\src\main.cpp -o CMakeFiles\project_cpp.dir\src\main.cpp.s

CMakeFiles/project_cpp.dir/src/MainWindow.cpp.obj: CMakeFiles/project_cpp.dir/flags.make
CMakeFiles/project_cpp.dir/src/MainWindow.cpp.obj: CMakeFiles/project_cpp.dir/includes_CXX.rsp
CMakeFiles/project_cpp.dir/src/MainWindow.cpp.obj: C:/Users/filip/CLionProjects/Video-Editor-App/src/MainWindow.cpp
CMakeFiles/project_cpp.dir/src/MainWindow.cpp.obj: CMakeFiles/project_cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\filip\CLionProjects\Video-Editor-App\cmake-build-debug-mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/project_cpp.dir/src/MainWindow.cpp.obj"
	C:\Users\filip\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project_cpp.dir/src/MainWindow.cpp.obj -MF CMakeFiles\project_cpp.dir\src\MainWindow.cpp.obj.d -o CMakeFiles\project_cpp.dir\src\MainWindow.cpp.obj -c C:\Users\filip\CLionProjects\Video-Editor-App\src\MainWindow.cpp

CMakeFiles/project_cpp.dir/src/MainWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/project_cpp.dir/src/MainWindow.cpp.i"
	C:\Users\filip\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\filip\CLionProjects\Video-Editor-App\src\MainWindow.cpp > CMakeFiles\project_cpp.dir\src\MainWindow.cpp.i

CMakeFiles/project_cpp.dir/src/MainWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/project_cpp.dir/src/MainWindow.cpp.s"
	C:\Users\filip\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\filip\CLionProjects\Video-Editor-App\src\MainWindow.cpp -o CMakeFiles\project_cpp.dir\src\MainWindow.cpp.s

CMakeFiles/project_cpp.dir/src/VideoPlayerWidget.cpp.obj: CMakeFiles/project_cpp.dir/flags.make
CMakeFiles/project_cpp.dir/src/VideoPlayerWidget.cpp.obj: CMakeFiles/project_cpp.dir/includes_CXX.rsp
CMakeFiles/project_cpp.dir/src/VideoPlayerWidget.cpp.obj: C:/Users/filip/CLionProjects/Video-Editor-App/src/VideoPlayerWidget.cpp
CMakeFiles/project_cpp.dir/src/VideoPlayerWidget.cpp.obj: CMakeFiles/project_cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\filip\CLionProjects\Video-Editor-App\cmake-build-debug-mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/project_cpp.dir/src/VideoPlayerWidget.cpp.obj"
	C:\Users\filip\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project_cpp.dir/src/VideoPlayerWidget.cpp.obj -MF CMakeFiles\project_cpp.dir\src\VideoPlayerWidget.cpp.obj.d -o CMakeFiles\project_cpp.dir\src\VideoPlayerWidget.cpp.obj -c C:\Users\filip\CLionProjects\Video-Editor-App\src\VideoPlayerWidget.cpp

CMakeFiles/project_cpp.dir/src/VideoPlayerWidget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/project_cpp.dir/src/VideoPlayerWidget.cpp.i"
	C:\Users\filip\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\filip\CLionProjects\Video-Editor-App\src\VideoPlayerWidget.cpp > CMakeFiles\project_cpp.dir\src\VideoPlayerWidget.cpp.i

CMakeFiles/project_cpp.dir/src/VideoPlayerWidget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/project_cpp.dir/src/VideoPlayerWidget.cpp.s"
	C:\Users\filip\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\filip\CLionProjects\Video-Editor-App\src\VideoPlayerWidget.cpp -o CMakeFiles\project_cpp.dir\src\VideoPlayerWidget.cpp.s

CMakeFiles/project_cpp.dir/src/TimelineWidget.cpp.obj: CMakeFiles/project_cpp.dir/flags.make
CMakeFiles/project_cpp.dir/src/TimelineWidget.cpp.obj: CMakeFiles/project_cpp.dir/includes_CXX.rsp
CMakeFiles/project_cpp.dir/src/TimelineWidget.cpp.obj: C:/Users/filip/CLionProjects/Video-Editor-App/src/TimelineWidget.cpp
CMakeFiles/project_cpp.dir/src/TimelineWidget.cpp.obj: CMakeFiles/project_cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\filip\CLionProjects\Video-Editor-App\cmake-build-debug-mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/project_cpp.dir/src/TimelineWidget.cpp.obj"
	C:\Users\filip\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project_cpp.dir/src/TimelineWidget.cpp.obj -MF CMakeFiles\project_cpp.dir\src\TimelineWidget.cpp.obj.d -o CMakeFiles\project_cpp.dir\src\TimelineWidget.cpp.obj -c C:\Users\filip\CLionProjects\Video-Editor-App\src\TimelineWidget.cpp

CMakeFiles/project_cpp.dir/src/TimelineWidget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/project_cpp.dir/src/TimelineWidget.cpp.i"
	C:\Users\filip\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\filip\CLionProjects\Video-Editor-App\src\TimelineWidget.cpp > CMakeFiles\project_cpp.dir\src\TimelineWidget.cpp.i

CMakeFiles/project_cpp.dir/src/TimelineWidget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/project_cpp.dir/src/TimelineWidget.cpp.s"
	C:\Users\filip\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\filip\CLionProjects\Video-Editor-App\src\TimelineWidget.cpp -o CMakeFiles\project_cpp.dir\src\TimelineWidget.cpp.s

CMakeFiles/project_cpp.dir/src/TextOverlayWidget.cpp.obj: CMakeFiles/project_cpp.dir/flags.make
CMakeFiles/project_cpp.dir/src/TextOverlayWidget.cpp.obj: CMakeFiles/project_cpp.dir/includes_CXX.rsp
CMakeFiles/project_cpp.dir/src/TextOverlayWidget.cpp.obj: C:/Users/filip/CLionProjects/Video-Editor-App/src/TextOverlayWidget.cpp
CMakeFiles/project_cpp.dir/src/TextOverlayWidget.cpp.obj: CMakeFiles/project_cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\filip\CLionProjects\Video-Editor-App\cmake-build-debug-mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/project_cpp.dir/src/TextOverlayWidget.cpp.obj"
	C:\Users\filip\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project_cpp.dir/src/TextOverlayWidget.cpp.obj -MF CMakeFiles\project_cpp.dir\src\TextOverlayWidget.cpp.obj.d -o CMakeFiles\project_cpp.dir\src\TextOverlayWidget.cpp.obj -c C:\Users\filip\CLionProjects\Video-Editor-App\src\TextOverlayWidget.cpp

CMakeFiles/project_cpp.dir/src/TextOverlayWidget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/project_cpp.dir/src/TextOverlayWidget.cpp.i"
	C:\Users\filip\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\filip\CLionProjects\Video-Editor-App\src\TextOverlayWidget.cpp > CMakeFiles\project_cpp.dir\src\TextOverlayWidget.cpp.i

CMakeFiles/project_cpp.dir/src/TextOverlayWidget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/project_cpp.dir/src/TextOverlayWidget.cpp.s"
	C:\Users\filip\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\filip\CLionProjects\Video-Editor-App\src\TextOverlayWidget.cpp -o CMakeFiles\project_cpp.dir\src\TextOverlayWidget.cpp.s

CMakeFiles/project_cpp.dir/src/FFmpegHandler.cpp.obj: CMakeFiles/project_cpp.dir/flags.make
CMakeFiles/project_cpp.dir/src/FFmpegHandler.cpp.obj: CMakeFiles/project_cpp.dir/includes_CXX.rsp
CMakeFiles/project_cpp.dir/src/FFmpegHandler.cpp.obj: C:/Users/filip/CLionProjects/Video-Editor-App/src/FFmpegHandler.cpp
CMakeFiles/project_cpp.dir/src/FFmpegHandler.cpp.obj: CMakeFiles/project_cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\filip\CLionProjects\Video-Editor-App\cmake-build-debug-mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/project_cpp.dir/src/FFmpegHandler.cpp.obj"
	C:\Users\filip\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project_cpp.dir/src/FFmpegHandler.cpp.obj -MF CMakeFiles\project_cpp.dir\src\FFmpegHandler.cpp.obj.d -o CMakeFiles\project_cpp.dir\src\FFmpegHandler.cpp.obj -c C:\Users\filip\CLionProjects\Video-Editor-App\src\FFmpegHandler.cpp

CMakeFiles/project_cpp.dir/src/FFmpegHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/project_cpp.dir/src/FFmpegHandler.cpp.i"
	C:\Users\filip\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\filip\CLionProjects\Video-Editor-App\src\FFmpegHandler.cpp > CMakeFiles\project_cpp.dir\src\FFmpegHandler.cpp.i

CMakeFiles/project_cpp.dir/src/FFmpegHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/project_cpp.dir/src/FFmpegHandler.cpp.s"
	C:\Users\filip\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\filip\CLionProjects\Video-Editor-App\src\FFmpegHandler.cpp -o CMakeFiles\project_cpp.dir\src\FFmpegHandler.cpp.s

# Object files for target project_cpp
project_cpp_OBJECTS = \
"CMakeFiles/project_cpp.dir/project_cpp_autogen/mocs_compilation.cpp.obj" \
"CMakeFiles/project_cpp.dir/src/main.cpp.obj" \
"CMakeFiles/project_cpp.dir/src/MainWindow.cpp.obj" \
"CMakeFiles/project_cpp.dir/src/VideoPlayerWidget.cpp.obj" \
"CMakeFiles/project_cpp.dir/src/TimelineWidget.cpp.obj" \
"CMakeFiles/project_cpp.dir/src/TextOverlayWidget.cpp.obj" \
"CMakeFiles/project_cpp.dir/src/FFmpegHandler.cpp.obj"

# External object files for target project_cpp
project_cpp_EXTERNAL_OBJECTS =

project_cpp.exe: CMakeFiles/project_cpp.dir/project_cpp_autogen/mocs_compilation.cpp.obj
project_cpp.exe: CMakeFiles/project_cpp.dir/src/main.cpp.obj
project_cpp.exe: CMakeFiles/project_cpp.dir/src/MainWindow.cpp.obj
project_cpp.exe: CMakeFiles/project_cpp.dir/src/VideoPlayerWidget.cpp.obj
project_cpp.exe: CMakeFiles/project_cpp.dir/src/TimelineWidget.cpp.obj
project_cpp.exe: CMakeFiles/project_cpp.dir/src/TextOverlayWidget.cpp.obj
project_cpp.exe: CMakeFiles/project_cpp.dir/src/FFmpegHandler.cpp.obj
project_cpp.exe: CMakeFiles/project_cpp.dir/build.make
project_cpp.exe: D:/QT/6.7.2/mingw_64/lib/libQt6MultimediaWidgets.a
project_cpp.exe: D:/QT/6.7.2/mingw_64/lib/libQt6Multimedia.a
project_cpp.exe: D:/QT/6.7.2/mingw_64/lib/libQt6Network.a
project_cpp.exe: D:/QT/6.7.2/mingw_64/lib/libQt6Widgets.a
project_cpp.exe: D:/QT/6.7.2/mingw_64/lib/libQt6Gui.a
project_cpp.exe: D:/QT/6.7.2/mingw_64/lib/libQt6Core.a
project_cpp.exe: CMakeFiles/project_cpp.dir/linkLibs.rsp
project_cpp.exe: CMakeFiles/project_cpp.dir/objects1.rsp
project_cpp.exe: CMakeFiles/project_cpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\filip\CLionProjects\Video-Editor-App\cmake-build-debug-mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable project_cpp.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\project_cpp.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/project_cpp.dir/build: project_cpp.exe
.PHONY : CMakeFiles/project_cpp.dir/build

CMakeFiles/project_cpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\project_cpp.dir\cmake_clean.cmake
.PHONY : CMakeFiles/project_cpp.dir/clean

CMakeFiles/project_cpp.dir/depend: project_cpp_autogen/timestamp
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\filip\CLionProjects\Video-Editor-App C:\Users\filip\CLionProjects\Video-Editor-App C:\Users\filip\CLionProjects\Video-Editor-App\cmake-build-debug-mingw C:\Users\filip\CLionProjects\Video-Editor-App\cmake-build-debug-mingw C:\Users\filip\CLionProjects\Video-Editor-App\cmake-build-debug-mingw\CMakeFiles\project_cpp.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/project_cpp.dir/depend

