# ==============================================================================
# CMakeLists.txt
# ==============================================================================

# Minimum CMake version required.
cmake_minimum_required(VERSION 3.31)

# ------------------------------------------------------------------------------
# Generator: the C++ modules with dependency scanning (CXX_CAN_FOR_MODULES)
# inly work with the generators Ninja or "Ninja Multi-Config".
# If the project is run usign "cmake -B build", without specifying "-G Ninja",
# the default generator is Unix Makefiles, which will cause the build to fail.
# ------------------------------------------------------------------------------
if(NOT CMAKE_GENERATOR MATCHES "Ninja")
    message(FATAL_ERROR
        "This project requires Ninja generator for modules support.\n"
        "Use: cmake -G Ninja -B build")
endif()

# Wether the generator is "multi-config" or not detection.
# In this case, the build type (Debug/Release) is selected when compiling
# and not when configuring.
get_property(is_multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

# If the generator has just one config (like Ninja) and the user didn't specify
# CMAKE_BUILD_TYPE (neither using CLI or environment variable), the realease
# is set by default to not compile without optimization.
if(NOT is_multi_config AND NOT (CMAKE_BUILD_TYPE OR DEFINED ENV{CMAKE_BUILD_TYPE}))
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Release default")
endif()

# The automatic scanning of dependencies between modules in turned on.
# This allows CMake/Ninja understand what module imports what other module
# and which one. It also allows the compilation in the correct order (interfaces
# before their import).
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

# Declares the project.
project(rensy LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # No compiler extensions.

# ------------------------------------------------------------------------------
# Minimum compiler version checking.
# ------------------------------------------------------------------------------
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 14.0)
    message(FATAL_ERROR "GCC 14 o greater is required for supporting C++20 modules.")
endif()

# Analyzes wether the includes are correct/necessaries.
# It can be activated using `cmake -B build - Diwyu=ON`.
option(iwyu "Run include-what-you-use")

if(iwyu)
    # REQUIRED. It makes CMake fail if it doesn't found the executable.
    # Otherwise, it will continue silently.
    find_program(IWYU_EXE NAMES include-what-you-use REQUIRED)
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${IWYU_EXE})
endif()

# Extended warnings are turned on for the compiler that support them.
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU|Intel")
    add_compile_options(-Wall)
endif()

# Searchs for OpenMP (parallelism).
# It's not required! If it's not installed, the project can compile anyways.
find_package(OpenMP COMPONENTS CXX)

# ------------------------------------------------------------------------------
# Souce files automatic recolection.
#
# CONFIGURE_DEPENDS tells CMake to evaluate again this glob in each build and,
# if the list of files changes, to reconfigure itself. This avoids editing
# constantly the CMakeLists.txt file when a new .cpp or .cppm file is added.
# However, it sums up a little overhead.
#
# ${CMAKE_CURRENT_SOURCE_DIR} is used instead of a relative route to avoid
# problems in case this file was included in another project or was invocated
# from another directory.
# ------------------------------------------------------------------------------
# All the .cppm files are searched.
file(GLOB_RECURSE CPPM_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cppm")

# All the .cpp files are searched.
file(GLOB_RECURSE CPP_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

# The files are sorted.
# This ensured a deterministic order no matter the operating system or the
# filesystem. This is neccesary because file(GLOB) doesn't ensure a stable
# ordering.
list(SORT CPPM_FILES)
list(SORT CPP_FILES)

# In C++ there three types of modules files and CMake treats them differently.
# - Intergaces (export module A;): Generate a precompiled file that other can read.
# - Partitions (module A:B;): Generate a partition that the primary module can read.
# - Implementations units (module A;): They don't export anything nor provide dependencies for
#    other files. They just contain the code with the functions.

# Considering the previous explanation, the .cpp files are classified in two lists:
set(CPP_MODULE_FILES "")
set(REGULAR_CPP_FILES "")

# We look for those .cpp files which implement modules.
foreach(cpp_file ${CPP_FILES})
    # We search for the word 'module' followed by a name.
    file(STRINGS "${cpp_file}" module_line REGEX "^[ \t]*module[ \t]+[a-zA-Z0-9_]+:[a-zA-Z0-9_]+;" LIMIT_COUNT 1)

    if(module_line)
        list(APPEND CPP_MODULE_FILES "${cpp_file}")
    else()
        list(APPEND REGULAR_CPP_FILES "${cpp_file}")
    endif()
endforeach()

# ------------------------------------------------------------------------------
# Messages for debugging.
# ------------------------------------------------------------------------------
message(STATUS ".cpp files found: ${CPP_FILES}")
message(STATUS ".cppm files found: ${CPPM_FILES}")

if(NOT CPP_FILES AND NOT CPPM_FILES)
    message(FATAL_ERROR
        "No .cpp nor .cppm file found in "
        "'${CMAKE_CURRENT_SOURCE_DIR}/source/'. Verify that the folder "
        "'source/' exists alongside this CMakeLists.txt and contains the sources.")
endif()

# Creates the executable target without the sources (they are added later).
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    # Regular .cpp files: main, modules impleemntations (units with "module X;",
    # with no export) and any .cpp files that's not a module interface.
    PRIVATE
        ${REGULAR_CPP_FILES}

    # .cppm files: Module interfaces ("export module X;").
    # "PRIVATE" is used because Rensy is the final executable. No
    # other target will link it nor needs to see these modules.
    PRIVATE
        FILE_SET CXX_MODULES
        FILES
            ${CPPM_FILES}
            ${CPP_MODULE_FILES}
)

# Links OpenMP only if find_package found it.
# The operator $<BOOL:...> is a "generator expression": it's evaluated in
# build generation time and it becomes nothing if OpenMP_CXX_FOUND is false.
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        $<$<BOOL:${OpenMP_CXX_FOUND}>:OpenMP::OpenMP_CXX>
)

# Generates a .gitignore with "*" inside so everything in the directory is
# ignored by git automatically.
file(GENERATE OUTPUT .gitignore CONTENT "*")