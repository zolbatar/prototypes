cmake_minimum_required(VERSION 3.20)
project(Dork)

EXECUTE_PROCESS(COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE)
message(STATUS "Architecture: ${ARCHITECTURE}")
set(CMAKE_OSX_ARCHITECTURES ${ARCHITECTURE})

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# LLVM
if (${ARCHITECTURE} STREQUAL "arm64")
    set(CORE_LLVM_DIR /opt/homebrew/Cellar/llvm/14.0.6_1/)
else ()
    set(CORE_LLVM_DIR /usr/local/Cellar/llvm/14.0.6_1/)
endif ()
set(LLVM_DIR "${CORE_LLVM_DIR}lib/cmake/llvm")
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})
llvm_map_components_to_libnames(LLVM_LIBS core support AArch64 X86 Coroutines OrcJIT)

add_executable(Dork
        Source/main.cpp
        Source/Compiler/Compiler.cpp
        Source/Compiler/CompilerCore.cpp Source/Compiler/CompilerStatement.cpp Source/Compiler/CompilerExpression.cpp Source/Compiler/CompilerLiteral.cpp
        Source/Compiler/CompilerAssign.cpp Source/Compiler/CompilerMethodCall.cpp

        Source/Compiler/Grammar/DorkBaseVisitor.cpp Source/Compiler/Grammar/DorkLexer.cpp Source/Compiler/Grammar/DorkParser.cpp Source/Compiler/Grammar/DorkVisitor.cpp

        Source/VM/VM.cpp Source/VM/Object.cpp)

target_link_libraries(${PROJECT_NAME} ${LIBS} ${LLVM_LIBS} ${ANTLR4_LIB} ${CONAN_LIBS})
