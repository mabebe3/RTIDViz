cmake_minimum_required(VERSION 3.22)
project(RTIDViz LANGUAGES C CXX CUDA)

set(CMAKE_CUDA_COMPILER "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.8/bin/nvcc.exe" CACHE FILEPATH "")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 14)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")


include("${CMAKE_BINARY_DIR}/conan_toolchain.cmake")
#("${CMAKE_BINARY_DIR}/conandeps_legacy.cmake")


file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/viz/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/data/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/compute/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/core/*.cpp"
)

file(GLOB_RECURSE CUDA_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/compute/*.cu"
)


find_package(arrow CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)
find_package(boost CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glad CONFIG REQUIRED)


set(IMGUI_LOCAL_BACKENDS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/external/imgui/backends")
set(IMGUI_BACKENDS "${IMGUI_LOCAL_BACKENDS_PATH}/imgui_impl_glfw.cpp" "${IMGUI_LOCAL_BACKENDS_PATH}/imgui_impl_opengl3.cpp")

add_executable(RTIDViz
    ${SRC_FILES}
    ${CUDA_FILES}
    ${IMGUI_BACKENDS}
)

#target_include_directories(RTIDViz PRIVATE "C:/Users/mkebe/.conan2/p/arrow52fe4f3e3977a/p/include")
#target_include_directories(RTIDViz PRIVATE "C:/Users/mkebe/.conan2/p/arrow52fe4f3e3977a/p/include")
#target_include_directories(RTIDViz PRIVATE "C:/Users/mkebe/.conan2/p/opensa26ab6857beb1/p/include")
#target_include_directories(RTIDViz PRIVATE "C:/Users/mkebe/.conan2/p/imgui889200aaca293/p/include")
#target_include_directories(RTIDViz PRIVATE "C:/Users/mkebe/.conan2/p/implo94d149d822de9/p/include")
#target_include_directories(RTIDViz PRIVATE "C:/Users/mkebe/.conan2/p/glfw5a2540817a296/p/include")


#get_target_property(IMGUI_INCLUDE_DIRS imgui::imgui INTERFACE_INCLUDE_DIRECTORIES)
#get_target_property(GLFW_INCLUDE_DIRS glfw INTERFACE_INCLUDE_DIRECTORIES)

target_include_directories(RTIDViz PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${IMGUI_LOCAL_BACKENDS_PATH}" 
    #${IMGUI_INCLUDE_DIRS}
    #${GLFW_INCLUDE_DIRS}
)


target_link_libraries(RTIDViz PUBLIC
    arrow::arrow
    imgui::imgui
    implot::implot
    Boost::boost
    glad::glad
    glfw
    OpenGL::GL
)
