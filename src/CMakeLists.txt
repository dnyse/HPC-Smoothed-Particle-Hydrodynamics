# Make an explicit list of all source files in `SPH_SRC`.
set(SPH_SRC
    main.cc
)

# Form the full path to the source files by prepending the current directory.
# This assumes the source files are directly in the 'src' directory.
foreach(file_name IN LISTS SPH_SRC)
    list(APPEND SPH_SRC_FULL "${CMAKE_CURRENT_SOURCE_DIR}/${file_name}")
endforeach()

# Pass the variable to the parent scope.
set(SPH_SRC ${SPH_SRC_FULL} PARENT_SCOPE)
