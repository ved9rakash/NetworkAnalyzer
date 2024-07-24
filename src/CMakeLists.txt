set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Collecting all executable files
file(GLOB_RECURSE SOURCES  "${PROJECT_DIR_SOURCES}/*.cpp")
file(GLOB_RECURSE SOURCES_GUI "${PROJECT_DIR_SOURCES}/gui/*.cpp")

# Collecting all the headers files
file(GLOB_RECURSE HEADERS "${PROJECT_DIR_HEADERS}/*.h")
file(GLOB_RECURSE HEADERS_GUI "${PROJECT_DIR_HEADERS}/gui/*.h")

# Collecting all Qt5 UI files
file(GLOB_RECURSE UI_FILES "${PROJECT_DIR_SOURCES}/gui/*.ui")

# Manually add specific source files if needed
list(APPEND SOURCES
  ${SOURCES_GUI}
)
# Manually add headers files
list(APPEND HEADERS 
  ${HEADERS_GUI}
)

# Including directories
include_directories(${PROJECT_DIR_HEADERS})
include_directories(${PROJECT_DIR_HEADERS}/gui)

# Defining the executable
add_executable(${PROJECT_NAME}
${SOURCES}        # All .cpp files - src/ src/gui
${UI_FILES}       # All .ui files - src/gui
${HEADERS}        # All .h files - include/ include/gui/
)