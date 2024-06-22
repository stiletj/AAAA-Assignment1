cmake_minimum_required(VERSION "3.27.4")

project("AAAGameEngine" VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(COPY ${CMAKE_SOURCE_DIR}/scripts DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/resources/fonts DESTINATION ${CMAKE_BINARY_DIR}/resources)
file(COPY ${CMAKE_SOURCE_DIR}/resources/materials DESTINATION ${CMAKE_BINARY_DIR}/resources)
file(COPY ${CMAKE_SOURCE_DIR}/resources/models DESTINATION ${CMAKE_BINARY_DIR}/resources)
file(COPY ${CMAKE_SOURCE_DIR}/resources/shaders DESTINATION ${CMAKE_BINARY_DIR}/resources)
file(COPY ${CMAKE_SOURCE_DIR}/resources/textures DESTINATION ${CMAKE_BINARY_DIR}/resources)
file(COPY ${CMAKE_SOURCE_DIR}/resources/heightmaps DESTINATION ${CMAKE_BINARY_DIR}/resources)
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "src/*.h")

add_subdirectory("lib/glfw")
add_subdirectory("lib/reactphysics3d")
add_subdirectory("lib/glew-cmake")
add_subdirectory("lib/glm")
add_subdirectory("lib/entt")
add_subdirectory("lib/lua")
add_subdirectory("lib/sol")

add_executable(${PROJECT_NAME}
	${SOURCES}
	${HEADERS}
	"src/vendor/imgui/imgui.cpp"
	"src/vendor/imgui/imgui.h"
	"src/vendor/imgui/imgui_impl_glfw.cpp"
	"src/vendor/imgui/imgui_impl_glfw.h"
	"src/vendor/imgui/imgui_impl_opengl3.cpp"
	"src/vendor/imgui/imgui_impl_opengl3.h"
	"src/vendor/imgui/imgui_draw.cpp"
	"src/vendor/imgui/imgui_widgets.cpp"
	"src/vendor/imgui/imgui_demo.cpp"
	"src/vendor/imgui/imgui_tables.cpp"
	"src/vendor/stb_image/stb_image.cpp"
	"src/vendor/stb_image/stb_image.h"
	)

# Link against dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC reactphysics3d)
target_link_libraries(${PROJECT_NAME} PUBLIC libglew_static)
target_link_libraries(${PROJECT_NAME} PUBLIC glm)
target_link_libraries(${PROJECT_NAME} PUBLIC EnTT)
target_link_libraries(${PROJECT_NAME} PUBLIC lua_static)
target_link_libraries(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/lib/assimp/assimp-vc143-mt.lib")
target_link_libraries(${PROJECT_NAME} PUBLIC sol2)


# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC 
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}/lib/glfw/include"
	"${PROJECT_SOURCE_DIR}/lib/reactphysics3d/include"
	"${PROJECT_SOURCE_DIR}/lib/glew-cmake/include"
	"${PROJECT_SOURCE_DIR}/lib/glm"
	"${PROJECT_SOURCE_DIR}/lib/entt"
	"${PROJECT_SOURCE_DIR}/lib/assimp/include"
	"${PROJECT_SOURCE_DIR}/lib/lua/include"
	"${PROJECT_SOURCE_DIR}/lib/sol/include"
	"${PROJECT_SOURCE_DIR}/src")


# Specify the source file
set(SOURCE_FILE "${PROJECT_SOURCE_DIR}/lib/assimp/bin/assimp-vc143-mt.dll")

# Specify the destination directories
set(DEST_DIR_1 "${PROJECT_SOURCE_DIR}/Build/Debug")
set(DEST_DIR_2 "${PROJECT_SOURCE_DIR}/Build/Release")

# Create the destination directories if they don't exist
file(MAKE_DIRECTORY ${DEST_DIR_1})
file(MAKE_DIRECTORY ${DEST_DIR_2})

# Copy the file to the destination directories
configure_file(${SOURCE_FILE} ${DEST_DIR_1}/assimp-vc143-mt.dll COPYONLY)
configure_file(${SOURCE_FILE} ${DEST_DIR_2}/assimp-vc143-mt.dll COPYONLY)


