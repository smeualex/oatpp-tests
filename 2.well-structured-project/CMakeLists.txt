cmake_minimum_required(VERSION 3.10)

set(project-name oatpp-well-structured-project)
message(" >>>>> project: ${project-name}")
project(${project-name} VERSION 1.0)
# mandatory for linux - VERSION Policy
cmake_policy(SET CMP0048 NEW)

set(CMAKE_CXX_STANDARD 11)

add_library(${project-name}-lib 
        src/AppComponent.hpp
        src/controller/HelloController.cpp
        src/controller/HelloController.hpp
        src/dto/Message.hpp
)


set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

# Control where the static and shared libraries are build so that on 
# Windows we don't need to change the path to run th executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY, "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY, "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY, "${PROJECT_BINARY_DIR}")


configure_file(${project-name}-Config.h.in ${project-name}-Config.h)

# Link libs
if(WIN32)
        list(APPEND CMAKE_PREFIX_PATH "d:\\Projects\\Tests\\C-C++\\lib")
endif()

find_package(oatpp 1.0.0 REQUIRED) 

target_link_libraries(${project-name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-test)

target_include_directories(${project-name}-lib 
        PUBLIC src)
        
# add executables
add_executable(${project-name}-exe
        src/App.cpp
        test/app/ApiTestClient.hpp)

target_link_libraries(${project-name}-exe 
        ${project-name}-lib)

add_dependencies(${project-name}-exe 
        ${project-name}-lib)

add_executable(${project-name}-test
        test/Tests.cpp
        test/app/TestComponent.hpp
        test/app/ApiTestClient.hpp
        test/HelloControllerTest.cpp
        test/HelloControllerTest.hpp
)

target_link_libraries(${project-name}-test 
        ${project-name}-lib)

add_dependencies(${project-name}-test 
        ${project-name}-lib)

set_target_properties(${project-name}-lib ${project-name}-exe ${project-name}-test PROPERTIES
        CXX_STANDARD 11
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

target_compile_options(${project-name}-lib INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)
target_compile_options(${project-name}-exe INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)
target_compile_options(${project-name}-test INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)


# Include the binary tree dir for TutorialConfig.h
# the configured file will be written into the binary tree
# we must add that directory to the list of paths to search for include files
# - add also the lib subdirectory to the include search path
# ===> to find TutorialConfig.h <===
target_include_directories(${project-name}-exe PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )


enable_testing()
add_test(project-tests ${project-name}-test)

# ###############################################################################
# ## INSTALL RULES
# ###############################################################################
#  set(CMAKE_INSTALL_PREFIX 
#      "d:/Projects/Tests/C-C++/bin")

# # install the windows runtime libraries
# set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)
# include(InstallRequiredSystemLibraries)
# # For the executable we want to install the executable and the header
# install(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}
#         DESTINATION bin)

# install(TARGETS ${project-name}
#         DESTINATION bin)

# install(FILES "${PROJECT_BINARY_DIR}/${project-name}Config.h" 
#         DESTINATION include)
