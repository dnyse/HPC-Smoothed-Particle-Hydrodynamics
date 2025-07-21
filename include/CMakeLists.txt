# Make an explicit list of all header files in `SPH_INCLUDE`.
set(SPH_INCLUDE
    tmp.h # Add other header files here
)

# Form the full path to the header files by prepending the current directory.
# This assumes the header files are directly in the 'include' directory.
foreach(file_name IN LISTS SPH_INCLUDE)
    list(APPEND SPH_INCLUDE_FULL "${CMAKE_CURRENT_SOURCE_DIR}/${file_name}")
endforeach()

# Pass the variable to the parent scope.
set(SPH_INCLUDE ${SPH_INCLUDE_FULL} PARENT_SCOPE)

# Add the include directory to the parent's include paths.
# This ensures that files in 'src' can find headers in 'include'.
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
