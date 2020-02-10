cmake_minimum_required(VERSION 3.10)

set(project-name oatpp-simple-project)
message(" >>>>> project: ${project-name}")
project(${project-name} VERSION 1.0)
# mandatory for linux - VERSION Policy
cmake_policy(SET CMP0048 NEW)

#add_library(${project-name} INTERFACE)

add_executable(${project-name}  
        src/main.cpp 
)

target_compile_features(${project-name} INTERFACE cxx_std_11)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(${project-name} INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

# Control where the static and shared libraries are build so that on 
# Windows we don't need to change the path to run th executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY, "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY, "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY, "${PROJECT_BINARY_DIR}")


configure_file(${project-name}-Config.h.in ${project-name}-Config.h)

# Find oat++ dependency
# add custom search paths for libraries
if(WIN32)
        list(APPEND CMAKE_PREFIX_PATH "d:\\Projects\\Tests\\C-C++\\lib")
endif()

find_package(oatpp 1.0.0 REQUIRED) 
target_link_libraries(${project-name} PUBLIC oatpp::oatpp)

# Include the binary tree dir for TutorialConfig.h
# the configured file will be written into the binary tree
# we must add that directory to the list of paths to search for include files
# - add also the lib subdirectory to the include search path
# ===> to find TutorialConfig.h <===
target_include_directories(${project-name} PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )


###############################################################################
## INSTALL RULES
###############################################################################
 set(CMAKE_INSTALL_PREFIX 
     "d:/Projects/Tests/C-C++/bin")

# install the windows runtime libraries
set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)
include(InstallRequiredSystemLibraries)
# For the executable we want to install the executable and the header
install(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}
        DESTINATION bin)

install(TARGETS ${project-name}
        DESTINATION bin)

install(FILES "${PROJECT_BINARY_DIR}/${project-name}Config.h" 
        DESTINATION include)
