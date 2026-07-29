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

FILES ?= resources/obj/diablo3_pose/diablo3_pose.obj resources/obj/floor.obj

git-uncache: ## "Descachea" los archivos.
	@git rm -r --cached .

compile:
	@cmake -B build -G Ninja -DCMAKE_CXX_COMPILER=clang++
	@cmake --build build -j

run: compile
	@./build/crasty $(FILES) 

timed-run: compile ## The program is executed using all optimizations (-O3) and then executed, measuring its runtime.
	@time ./build/crasty $(FILES)

see-imports:
	@grep -R "^import " source/*.cppm