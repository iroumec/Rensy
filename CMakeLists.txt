# ==============================================================================
# CMakeLists.txt — proyecto "crasty"
# ==============================================================================

# Versión mínima de CMake requerida. 3.31 es necesaria porque el soporte
# "estable" de módulos C++20 (FILE_SET CXX_MODULES) se consolidó recién en
# versiones recientes de CMake.
cmake_minimum_required(VERSION 3.31)

# ------------------------------------------------------------------------------
# Generador: los módulos C++ con escaneo de dependencias (CXX_SCAN_FOR_MODULES)
# SOLO funcionan con los generadores Ninja o "Ninja Multi-Config".
# Si alguien corre "cmake -B build" sin especificar -G Ninja y su generador
# por defecto es Unix Makefiles, el build fallará de forma confusa más
# adelante. Lo detectamos acá y cortamos con un mensaje claro.
# ------------------------------------------------------------------------------
if(NOT CMAKE_GENERATOR MATCHES "Ninja")
    message(FATAL_ERROR
        "Este proyecto requiere el generador Ninja para soporte de módulos C++20.\n"
        "Configurá con: cmake -G Ninja -B build")
endif()

# Detecta si el generador es "multi-config" (como Visual Studio o Ninja
# Multi-Config), donde el tipo de build (Debug/Release) se elige al compilar
# y no al configurar.
get_property(is_multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

# Si el generador es de un solo config (como Ninja normal) y el usuario no
# especificó CMAKE_BUILD_TYPE (ni por CLI ni por variable de entorno),
# fijamos Release por defecto para no compilar sin optimizaciones sin querer.
if(NOT is_multi_config AND NOT (CMAKE_BUILD_TYPE OR DEFINED ENV{CMAKE_BUILD_TYPE}))
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Release default")
endif()

# Habilita el escaneo automático de dependencias entre módulos C++.
# Esto es lo que le permite a CMake/Ninja entender qué módulo importa a
# cuál, y compilarlos en el orden correcto (las interfaces antes que
# quienes las importan).
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

# Declara el proyecto. Debe ir después de la configuración de generador
# porque algunas de las variables de arriba deben fijarse antes de project().
project(crasty LANGUAGES CXX)

# Requerimos C++20 (necesario para módulos) de forma estricta, sin
# extensiones propietarias del compilador (gnu++20 en vez de c++20).
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------------------------------------------------------------------
# Chequeo de versión mínima de compilador.
# El soporte de módulos en GCC es frágil/incompleto antes de la versión 14.
# Si alguien clona el repo con un GCC viejo, preferimos fallar acá con un
# mensaje claro en vez de los errores crípticos de "failed to read compiled
# module" que aparecen más adelante en el proceso de build.
# ------------------------------------------------------------------------------
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 14.0)
    message(FATAL_ERROR "Se requiere GCC 14 o superior para soporte de módulos C++20.")
endif()

# Opción para correr include-what-you-use (analiza si los #include son
# correctos/necesarios). Se activa con: cmake -B build -Diwyu=ON
option(iwyu "Run include-what-you-use")

if(iwyu)
    # REQUIRED hace que CMake falle si no encuentra el ejecutable, en vez de
    # seguir silenciosamente sin la herramienta.
    find_program(IWYU_EXE NAMES include-what-you-use REQUIRED)
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${IWYU_EXE})
endif()

# Habilita warnings extendidos en los compiladores que lo soportan.
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU|Intel")
    add_compile_options(-Wall)
endif()

# Busca OpenMP (paralelismo). No es REQUIRED: si no está instalado, el
# proyecto igual compila, simplemente sin paralelismo (ver target_link_libraries).
find_package(OpenMP COMPONENTS CXX)

# ------------------------------------------------------------------------------
# Recolección automática de archivos fuente.
#
# CONFIGURE_DEPENDS le indica a CMake que vuelva a evaluar este glob en cada
# build, y si la lista de archivos cambió, se reconfigura sola. Esto evita
# tener que editar el CMakeLists.txt a mano cada vez que agregás un .cpp o
# .cppm nuevo (a costa de un pequeño overhead de chequeo en cada build).
#
# Usamos ${CMAKE_CURRENT_SOURCE_DIR} en vez de una ruta relativa ("source/")
# para evitar ambigüedades si este CMakeLists.txt llegara a incluirse desde
# otro proyecto o se invocara desde un directorio distinto.
# ------------------------------------------------------------------------------
file(GLOB_RECURSE MODULE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cppm")
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

# list(SORT ...) asegura un orden determinístico entre distintos sistemas
# operativos/filesystems, ya que file(GLOB) no garantiza orden estable.
list(SORT MODULE_FILES)
list(SORT SOURCE_FILES)

# ------------------------------------------------------------------------------
# Diagnóstico: si en algún momento el build falla con "No SOURCES given to
# target", este mensaje te va a mostrar inmediatamente si el problema es que
# el glob no encontró nada (carpeta "source/" vacía, mal ubicada, o mal
# nombrada).
# ------------------------------------------------------------------------------
message(STATUS "Archivos .cpp encontrados: ${SOURCE_FILES}")
message(STATUS "Archivos .cppm encontrados: ${MODULE_FILES}")

if(NOT SOURCE_FILES AND NOT MODULE_FILES)
    message(FATAL_ERROR
        "No se encontró ningún archivo .cpp ni .cppm en "
        "'${CMAKE_CURRENT_SOURCE_DIR}/source/'. Verificá que la carpeta "
        "'source/' exista junto a este CMakeLists.txt y contenga tus fuentes.")
endif()

# Crea el target ejecutable SIN fuentes todavía (se las agregamos en el
# siguiente bloque). Esto es válido siempre y cuando target_sources() se
# llame antes de que termine la configuración (lo cual hacemos).
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    # Archivos .cpp "normales": el main, implementaciones de módulos
    # (unidades "module X;" sin export), y cualquier .cpp que no sea una
    # interfaz de módulo.
    PRIVATE
        ${SOURCE_FILES}

    # Archivos .cppm: interfaces de módulo (contienen "export module X;").
    # Se usa PRIVATE (no PUBLIC) porque "crasty" es un ejecutable final:
    # ningún otro target lo va a linkear ni necesita ver estos módulos.
    PRIVATE
        FILE_SET CXX_MODULES
        FILES
            ${MODULE_FILES}
)

# Linkea OpenMP solo si find_package lo encontró. El operador $<BOOL:...>
# es un "generator expression": se evalúa en tiempo de generación de build
# y se convierte en nada si OpenMP_CXX_FOUND es falso.
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        $<$<BOOL:${OpenMP_CXX_FOUND}>:OpenMP::OpenMP_CXX>
)

# Genera un .gitignore con "*" dentro del directorio de build, para que todo
# lo generado ahí quede ignorado por git automáticamente.
file(GENERATE OUTPUT .gitignore CONTENT "*")