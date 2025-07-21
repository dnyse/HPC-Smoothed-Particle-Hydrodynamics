cmake_minimum_required(VERSION 3.16)
project(sph CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
add_compile_definitions(_Alignof=__alignof)

# Set different flags for different build types
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    message(STATUS "Configuring Debug build")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wall -Wextra")
elseif(CMAKE_BUILD_TYPE STREQUAL "RELEASE")
    message(STATUS "Configuring Release build")
endif()

# --- Eigen Dependency Handling ---
find_package(Eigen3 CONFIG QUIET)
if(NOT Eigen3_FOUND)
    message(STATUS "Eigen3 not found on system. Fetching with FetchContent...")
    include(FetchContent)

    # Declare Eigen as a remote content
    # You can choose a specific tag/version, e.g., 3.4.0, or 'master' for latest.
    # It's generally good practice to pin to a specific version for reproducibility.
    FetchContent_Declare(
        Eigen
        GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
        GIT_TAG        3.4.0 # Or 'master' for the latest development version
        # You might want to add EXCLUDE_FROM_ALL to prevent Eigen's own tests/examples
        # from being built by default, especially if they are not needed.
        # EXCLUDE_FROM_ALL TRUE
    )

    # Populate the content (downloads and makes it available)
    FetchContent_MakeAvailable(Eigen)

    # After FetchContent_MakeAvailable, Eigen's targets like Eigen3::Eigen should be available.
    # We explicitly add the include directory from the fetched content.
    # For Eigen 3.4.0+, the CMake integration is robust, and target_link_libraries
    # should pull in the necessary include paths automatically.
    # However, for older versions or explicit clarity, you could do:
    # include_directories(${eigen_SOURCE_DIR}) # This adds the root of the Eigen source as an include path
                                             # This is typically where the 'Eigen' and 'unsupported' folders are.
    # Or, to be more specific (though Eigen's config does this):
    # target_include_directories(${PROJECT_NAME} PRIVATE ${eigen_SOURCE_DIR})

    # You can also set some Eigen specific options if you fetched it
    # set(BUILD_TESTING OFF CACHE BOOL "Disable Eigen's tests" FORCE) # Example: turn off Eigen's tests

else()
    message(STATUS "Found Eigen3: ${Eigen3_VERSION}")
endif()

# Add subdirectories for source and include files
# These will set SPH_SRC and SPH_INCLUDE in the parent scope
add_subdirectory(src)
add_subdirectory(include)

# Create executable using collected sources and headers
add_executable(${PROJECT_NAME} ${SPH_SRC} ${SPH_INCLUDE})

# Link include directories (if needed, though often handled by the include subdirectory)
target_link_libraries(${PROJECT_NAME} PRIVATE Eigen3::Eigen)
