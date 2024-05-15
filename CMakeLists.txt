cmake_minimum_required(VERSION 3.26)
project(VisualSorter)

set(CMAKE_CXX_STANDARD 23)
cmake_minimum_required(VERSION 3.0)
project(VisualSorter)

# Find GLEW
find_package(GLEW 2.2 REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

# Find GLFW
find_package(glfw3 3.4 REQUIRED)

file(GLOB_RECURSE CSources VisualSorter/src/**.cpp)
file(GLOB_RECURSE HSources VisualSorter/src/**.h)

# Add your source files
set(SOURCES main.cpp
        Shader/Shader.cpp)

add_executable(VisualSorter
        ${CSources}
        ${HSources}
)

target_include_directories(VisualSorter PRIVATE
        "/Users/marcelo.colonia/Documents/dev/VisualSorter/VisualSorter/src"
        "/Users/marcelo.colonia/Documents/dev/VisualSorter/VisualSorter/vendor/glm"
        ${GLEW_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
)
# Link GLEW and GLFW
target_link_libraries(VisualSorter ${GLEW_LIBRARIES} glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(VisualSorter ${OPENGL_gl_LIBRARY})



