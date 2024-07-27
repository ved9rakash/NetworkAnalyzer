# src/CMakeLists.txt

# Collecting all executable files
file(GLOB_RECURSE SOURCES     "${PROJECT_DIR_SOURCES}/*.cpp")
file(GLOB_RECURSE SOURCES_GUI "${PROJECT_DIR_SOURCES}/gui/*.cpp")

# Collecting all the headers files
file(GLOB_RECURSE HEADERS     "${PROJECT_DIR_HEADERS}/*.h")
file(GLOB_RECURSE HEADERS_GUI "${PROJECT_DIR_HEADERS}/gui/*.h")

# Collecting all Qt5 UI files
file(GLOB_RECURSE UI_FILES "${PROJECT_DIR_SOURCES}/gui/*.ui")

# Manually add specific source files if needed
list(APPEND ${SOURCES}
  ${SOURCES_GUI}
)

list(APPEND ${SOURCES}
  ${UI_FILES}
)
# Manually add headers files
list(APPEND ${HEADERS} 
  ${HEADERS_GUI}
)

# Defining the executable
add_executable(${PROJECT_NAME}
${SOURCES}        # All .cpp files - src/ src/gui
${HEADERS}        # All .h files - include/ include/gui/
${PROJECT_DIR_UI_HEADERS}
)