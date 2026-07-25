# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/iroumec/Documents/Crasty/source

git-uncache: ## "Descachea" los archivos.
	@git rm -r --cached .

compile:
	@cmake -B build -G Ninja -DCMAKE_CXX_COMPILER=clang++
	@cmake --build build -j

run: compile
	@./build/crasty obj/diablo3_pose/diablo3_pose.obj obj/floor.obj

timed-run: compile ## The program is executed using all optimizations (-O3) and then executed, measuring its runtime.
	@time ./build/crasty obj/diablo3_pose/diablo3_pose.obj obj/floor.obj