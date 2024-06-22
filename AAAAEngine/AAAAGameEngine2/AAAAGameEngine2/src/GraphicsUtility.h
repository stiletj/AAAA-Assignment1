#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <unordered_map>
#include <functional>

/**
 * @brief Enumeration of keyboard keys.
 */
enum GUKey {
    KEY_UNKNOWN = GLFW_KEY_UNKNOWN,
    KEY_SPACE = GLFW_KEY_SPACE,
    KEY_APOSTROPHE = GLFW_KEY_APOSTROPHE,
    KEY_COMMA = GLFW_KEY_COMMA,
    KEY_MINUS = GLFW_KEY_MINUS,
    KEY_PERIOD = GLFW_KEY_PERIOD,
    KEY_SLASH = GLFW_KEY_SLASH,
    KEY_0 = GLFW_KEY_0,
    KEY_1 = GLFW_KEY_1,
    KEY_2 = GLFW_KEY_2,
    KEY_3 = GLFW_KEY_3,
    KEY_4 = GLFW_KEY_4,
    KEY_5 = GLFW_KEY_5,
    KEY_6 = GLFW_KEY_6,
    KEY_7 = GLFW_KEY_7,
    KEY_8 = GLFW_KEY_8,
    KEY_9 = GLFW_KEY_9,
    KEY_SEMICOLON = GLFW_KEY_SEMICOLON,
    KEY_EQUAL = GLFW_KEY_EQUAL,
    KEY_A = GLFW_KEY_A,
    KEY_B = GLFW_KEY_B,
    KEY_C = GLFW_KEY_C,
    KEY_D = GLFW_KEY_D,
    KEY_E = GLFW_KEY_E,
    KEY_F = GLFW_KEY_F,
    KEY_G = GLFW_KEY_G,
    KEY_H = GLFW_KEY_H,
    KEY_I = GLFW_KEY_I,
    KEY_J = GLFW_KEY_J,
    KEY_K = GLFW_KEY_K,
    KEY_L = GLFW_KEY_L,
    KEY_M = GLFW_KEY_M,
    KEY_N = GLFW_KEY_N,
    KEY_O = GLFW_KEY_O,
    KEY_P = GLFW_KEY_P,
    KEY_Q = GLFW_KEY_Q,
    KEY_R = GLFW_KEY_R,
    KEY_S = GLFW_KEY_S,
    KEY_T = GLFW_KEY_T,
    KEY_U = GLFW_KEY_U,
    KEY_V = GLFW_KEY_V,
    KEY_W = GLFW_KEY_W,
    KEY_X = GLFW_KEY_X,
    KEY_Y = GLFW_KEY_Y,
    KEY_Z = GLFW_KEY_Z,
    KEY_LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,
    KEY_BACKSLASH = GLFW_KEY_BACKSLASH,
    KEY_RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,
    KEY_GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,
    KEY_WORLD_1 = GLFW_KEY_WORLD_1,
    KEY_WORLD_2 = GLFW_KEY_WORLD_2,
    KEY_ESCAPE = GLFW_KEY_ESCAPE,
    KEY_ENTER = GLFW_KEY_ENTER,
    //KEY_TAB = GLFW_KEY_TAB,
    KEY_BACKSPACE = GLFW_KEY_BACKSPACE,
    KEY_INSERT = GLFW_KEY_INSERT,
    KEY_DELETE = GLFW_KEY_DELETE,
    KEY_RIGHT = GLFW_KEY_RIGHT,
    KEY_LEFT = GLFW_KEY_LEFT,
    KEY_DOWN = GLFW_KEY_DOWN,
    KEY_UP = GLFW_KEY_UP,
    KEY_PAGE_UP = GLFW_KEY_PAGE_UP,
    KEY_PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
    KEY_HOME = GLFW_KEY_HOME,
    KEY_END = GLFW_KEY_END,
    KEY_CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
    KEY_SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
    KEY_NUM_LOCK = GLFW_KEY_NUM_LOCK,
    KEY_PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
    KEY_PAUSE = GLFW_KEY_PAUSE,
    KEY_F1 = GLFW_KEY_F1,
    KEY_F2 = GLFW_KEY_F2,
    KEY_F3 = GLFW_KEY_F3,
    KEY_F4 = GLFW_KEY_F4,
    KEY_F5 = GLFW_KEY_F5,
    KEY_F6 = GLFW_KEY_F6,
    KEY_F7 = GLFW_KEY_F7,
    KEY_F8 = GLFW_KEY_F8,
    KEY_F9 = GLFW_KEY_F9,
    KEY_F10 = GLFW_KEY_F10,
    KEY_F11 = GLFW_KEY_F11,
    KEY_F12 = GLFW_KEY_F12,
    KEY_KP_DECIMAL = GLFW_KEY_KP_DECIMAL,
    KEY_KP_DIVIDE = GLFW_KEY_KP_DIVIDE,
    KEY_KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
    KEY_KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
    KEY_KP_ADD = GLFW_KEY_KP_ADD,
    KEY_KP_ENTER = GLFW_KEY_KP_ENTER,
    KEY_KP_EQUAL = GLFW_KEY_KP_EQUAL,
    KEY_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
    KEY_LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
    //KEY_LEFT_ALT = GLFW_KEY_LEFT_ALT,
    KEY_LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
    KEY_RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
    KEY_RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
    //KEY_RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
    KEY_RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
    KEY_MENU = GLFW_KEY_MENU
};

/**
 * @brief Enumeration of mouse buttons.
 */
enum GUMouseButton {
    MOUSE_BUTTON_1 = GLFW_MOUSE_BUTTON_1,
    MOUSE_BUTTON_2 = GLFW_MOUSE_BUTTON_2,
    MOUSE_BUTTON_3 = GLFW_MOUSE_BUTTON_3,
    MOUSE_BUTTON_4 = GLFW_MOUSE_BUTTON_4,
    MOUSE_BUTTON_5 = GLFW_MOUSE_BUTTON_5,
    MOUSE_BUTTON_6 = GLFW_MOUSE_BUTTON_6,
    MOUSE_BUTTON_7 = GLFW_MOUSE_BUTTON_7,
    MOUSE_BUTTON_8 = GLFW_MOUSE_BUTTON_8,
    MOUSE_BUTTON_LAST = GLFW_MOUSE_BUTTON_LAST,
    MOUSE_BUTTON_LEFT = GLFW_MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE
};

/**
 * @brief Enumeration of OpenGL constants.
 */
enum GraphicsEnum {
    FLOAT = GL_FLOAT,
    UNSIGNED_INT = GL_UNSIGNED_INT,
    UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
    DOUBLE = GL_DOUBLE,
    FALSE = GL_FALSE,
    TRUE = GL_TRUE,
    REPEAT = GL_REPEAT,
    TEXTURE_WRAP_R = GL_TEXTURE_WRAP_R,
    TEXTURE_WRAP_T = GL_TEXTURE_WRAP_T,
    TEXTURE_WRAP_S = GL_TEXTURE_WRAP_S,
    TEXTURE_2D = GL_TEXTURE_2D,
    TEXTURE_MAG_FILTER = GL_TEXTURE_MAG_FILTER,
    TEXTURE_MIN_FILTER = GL_TEXTURE_MIN_FILTER,
    LINEAR = GL_LINEAR,
    STATIC_DRAW = GL_STATIC_DRAW,
    COLOR_BUFFER_BIT = GL_COLOR_BUFFER_BIT,
    DEPTH_BUFFER_BIT = GL_DEPTH_BUFFER_BIT,
    DEPTH_TEST = GL_DEPTH_TEST,
    BLEND = GL_BLEND,
    QUADS = GL_QUADS,
    TRIANGLES = GL_TRIANGLES,
    POLYGON = GL_POLYGON,
    TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
    ARRAY_BUFFER = GL_ARRAY_BUFFER,
    ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
    COMPILE_STATUS = GL_COMPILE_STATUS,
    INFO_LOG_LENGTH = GL_INFO_LOG_LENGTH,
    VERTEX_SHADER = GL_VERTEX_SHADER,
    FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
    RGBA8 = GL_RGBA8,
    RGBA = GL_RGBA,
    RGB = GL_RGB,
    CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
    LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
    TEXTURE_CUBE_MAP_POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
    TEXTURE_CUBE_MAP_NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
    TEXTURE_CUBE_MAP_POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
    TEXTURE_CUBE_MAP_NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
    TEXTURE_CUBE_MAP_POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
    TEXTURE_CUBE_MAP_NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
    TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,

};

/**
 * @brief Utility class for graphics-related operations.
 */
class GraphicsUtility
{
public:
    using Window = GLFWwindow*; 
    // Define a type for key callback functions
    using KeyCallback = std::function<void(GLFWwindow*, int, int, int, int)>;
    // Define a type for cursor position callback functions
    using CursorPosCallback = std::function<void(GLFWwindow*, double, double)>;

    /**
     * @brief Initializes GLFW.
     * @return 0 if successful, -1 otherwise.
     */
    static int Initialise();

    /**
     * @brief Initializes OpenGL extensions using GLEW.
     * @return 0 if successful, -1 otherwise.
     */
    static int initialiseOpenGLExtensions();

    /**
     * @brief Terminates GLFW.
     */
    static void Terminate();

    /**
     * @brief Destroys a window.
     * @param window The window to destroy.
     */
    static void destroyWindow(Window window);

    /**
     * @brief Creates a GLFW window.
     * @param title Title of the window.
     * @return Pointer to the created window.
     */
    static GLFWwindow* CreateWindow(const char* title);

    /**
     * @brief Creates a GLFW window with specified dimensions.
     * @param title Title of the window.
     * @param width Width of the window.
     * @param height Height of the window.
     * @return Pointer to the created window.
     */
    static GLFWwindow* CreateWindow(const char* title, int width, int height);

    /**
     * @brief Sets the current OpenGL context.
     * @param window The window with the desired context.
     */
    static void makeContextCurrent(GLFWwindow* window);

    /**
     * @brief Sets the framebuffer size callback for a window.
     * @param window The window to set the callback for.
     */
    static void setFramebufferSizeCallback(GLFWwindow* window);

    /**
     * @brief Checks if a window should close.
     * @param window The window to check.
     * @return True if the window should close, false otherwise.
     */
    static bool shouldClose(GLFWwindow* window);

    /**
     * @brief Swaps the front and back buffers of a window.
     * @param window The window whose buffers to swap.
     */
    static void swapBuffers(GLFWwindow* window);

    /**
     * @brief Polls for events.
     */
    static void pollEvents();

    /**
     * @brief Sets the should close flag for a window.
     * @param window The window to set the flag for.
     * @param value The value to set.
     */
    static void setWindowShouldClose(GLFWwindow* window, bool value);

    /**
     * @brief Adds a key callback function.
     * @param callback The callback function to add.
     */
    static void AddKeyCallback(KeyCallback callback);

    /**
     * @brief Adds a cursor position callback function.
     * @param callback The callback function to add.
     */
    static void AddCursorPosCallback(CursorPosCallback callback);

    /**
     * @brief Sets the clear color for the color buffer.
     * @param red Red component of the color.
     * @param green Green component of the color.
     * @param blue Blue component of the color.
     * @param alpha Alpha component of the color.
     */
    static void SetClearColor(float red, float green, float blue, float alpha);

    /**
     * @brief Clears buffers to preset values.
     * @param buffers Bitwise OR of buffer bits indicating the buffers to be cleared.
     */
    static void Clear(int buffers);

    /**
     * @brief Enables a specific OpenGL capability.
     * @param cap The capability to enable.
     */
    static void Enable(GLenum cap);

    /**
     * @brief Disables a specific OpenGL capability.
     * @param cap The capability to disable.
     */
    static void Disable(GLenum cap);

    /**
     * @brief Marks the beginning of vertex data definition.
     * @param mode The primitive type to begin drawing.
     */
    static void Begin(GLenum mode);

    /**
     * @brief Marks the end of vertex data definition.
     */
    static void End();

    /**
     * @brief Sets the current color.
     * @param red Red component of the color.
     * @param green Green component of the color.
     * @param blue Blue component of the color.
     */
    static void Color3f(float red, float green, float blue);

    /**
     * @brief Sets the current texture coordinates.
     * @param s The s-coordinate of the texture.
     * @param t The t-coordinate of the texture.
     */
    static void TexCoord2f(float s, float t);

    /**
     * @brief Sets the current vertex.
     * @param x X-coordinate of the vertex.
     * @param y Y-coordinate of the vertex.
     * @param z Z-coordinate of the vertex.
     */
    static void Vertex3f(float x, float y, float z);

    /**
     * @brief Sets the current normal vector.
     * @param nx X-component of the normal vector.
     * @param ny Y-component of the normal vector.
     * @param nz Z-component of the normal vector.
     */
    static void Normal3f(float nx, float ny, float nz);

    /**
     * @brief Specifies the mode and face for polygon rasterization.
     * @param face The face for which to set the mode.
     * @param mode The rasterization mode.
     */
    static void PolygonMode(GLenum face, GLenum mode);

    /**
     * @brief Generates vertex array object names.
     * @param value The number of vertex array object names to generate.
     * @param id Pointer to an array in which the generated vertex array object names are stored.
     */
    static void GenerateVertexArrays(GLsizei value, unsigned int* id);

    /**
     * @brief Deletes named vertex array objects.
     * @param value The number of vertex array object names to delete.
     * @param id Pointer to an array containing the vertex array object names to delete.
     */
    static void DeleteVertexArrays(GLsizei value, unsigned int* id);

    /**
     * @brief Enables a generic vertex attribute array.
     * @param index The index of the generic vertex attribute array to enable.
     */
    static void EnableVertexAttribArray(unsigned int index);

    /**
     * @brief Defines an array of generic vertex attribute data.
     * @param index The index of the generic vertex attribute array to modify.
     * @param size The number of components per generic vertex attribute.
     * @param type The data type of each component in the array.
     * @param normalized Whether the data should be normalized.
     * @param stride The byte offset between consecutive generic vertex attributes.
     * @param pointer The offset of the first component of the first generic vertex attribute in the array in the data store.
     */
    static void VertexAttribPointer(unsigned int index, int size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

    /**
     * @brief Binds a vertex array object.
     * @param id The name of the vertex array object to bind.
     */
    static void BindVertexArray(unsigned int id);

    /**
     * @brief Generates buffer object names.
     * @param n The number of buffer object names to generate.
     * @param buffers Pointer to an array in which the generated buffer object names are stored.
     */
    static void GenBuffers(GLsizei n, unsigned int* buffers);

    /**
     * @brief Binds a buffer to a buffer target.
     * @param target The target to which the buffer will be bound.
     * @param buffer The name of the buffer object to bind.
     */
    static void BindBuffer(GLenum target, unsigned int buffer);

    /**
     * @brief Creates and initializes a buffer object's data store.
     * @param target The target buffer object.
     * @param size The size in bytes of the buffer object's new data store.
     * @param data Pointer to the data that will be copied into the data store.
     * @param usage The expected usage pattern of the data store.
     */
    static void BufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);

    /**
     * @brief Deletes buffer objects.
     * @param n The number of buffer objects to delete.
     * @param buffers Pointer to an array containing the buffer objects to delete.
     */
    static void DeleteBuffers(GLsizei n, const unsigned int* buffers);

    /**
     * @brief Generates texture names.
     * @param n The number of texture names to generate.
     * @param textures Pointer to an array in which the generated texture names are stored.
     */
    static void GenTextures(GLsizei n, unsigned int* textures);

    /**
     * @brief Binds a named texture to a texture target.
     * @param target The texture target to which the texture will be bound.
     * @param texture The name of the texture to bind.
     */
    static void BindTexture(GLenum target, unsigned int texture);

    /**
     * @brief Sets texture parameters.
     * @param target The target of the operation.
     * @param pname The parameter name.
     * @param param The value of the parameter.
     */
    static void TexParameteri(GLenum target, GLenum pname, int param);

    /**
     * @brief Specifies a two-dimensional texture image.
     * @param target The target texture.
     * @param level The level-of-detail number.
     * @param internalformat The number of color components in the texture.
     * @param width The width of the texture image.
     * @param height The height of the texture image.
     * @param border The width of the border. Must be 0.
     * @param format The format of the pixel data.
     * @param type The data type of the pixel data.
     * @param pixels Pointer to the image data in memory.
     */
    static void TexImage2D(GLenum target, int level, int internalformat, GLsizei width, GLsizei height, int border, GLenum format, GLenum type, const void* pixels);

    /**
     * @brief Deletes named textures.
     * @param n The number of textures to delete.
     * @param textures Pointer to an array containing the texture names to delete.
     */
    static void DeleteTextures(GLsizei n, const unsigned int* textures);

    /**
     * @brief Creates a shader object.
     * @param type The type of shader to create.
     * @return The name (ID) of the shader object.
     */
    static unsigned int CreateShader(GLenum type);

    /**
     * @brief Sets the source code in a shader object.
     * @param shader The name of the shader object.
     * @param count The number of strings in the strings parameter.
     * @param string Array of pointers to strings containing the source code to be loaded into the shader.
     * @param length An array containing the lengths of each string in the strings array.
     */
    static void ShaderSource(unsigned int shader, GLsizei count, const char* const* string, const int* length);

    /**
     * @brief Compiles a shader object.
     * @param shader The name of the shader object.
     */
    static void CompileShader(unsigned int shader);

    /**
     * @brief Returns a parameter from a shader object.
     * @param shader The name of the shader object.
     * @param pname The parameter to query.
     * @param params Pointer to an integer where the parameter value will be stored.
     */
    static void GetShaderiv(unsigned int shader, GLenum pname, int* params);

    /**
     * @brief Returns the info log for a shader object.
     * @param shader The name of the shader object.
     * @param maxLength The maximum length of the info log.
     * @param length Pointer to an integer where the length of the info log will be stored.
     * @param infoLog Pointer to a character array where the info log will be stored.
     */
    static void GetShaderInfoLog(unsigned int shader, GLsizei maxLength, GLsizei* length, char* infoLog);

    /**
     * @brief Deletes a shader object.
     * @param shader The name of the shader object.
     */
    static void DeleteShader(unsigned int shader);

    /**
     * @brief Creates a program object.
     * @return The name (ID) of the program object.
     */
    static unsigned int CreateProgram();

    /**
     * @brief Deletes a program object.
     * @param id The name of the program object.
     */
    static void DeleteProgram(unsigned int id);

    /**
     * @brief Attaches a shader object to a program object.
     * @param program The name of the program object.
     * @param shader The name of the shader object to attach.
     */
    static void AttachShader(unsigned int program, unsigned int shader);

    /**
     * @brief Links a program object.
     * @param program The name of the program object.
     */
    static void LinkProgram(unsigned int program);

    /**
     * @brief Validates a program object.
     * @param program The name of the program object.
     */
    static void ValidateProgram(unsigned int program);

    /**
     * @brief Sets the current program object.
     * @param program The name of the program object to use.
     */
    static void UseProgram(unsigned int program);

    /**
     * @brief Returns the location of a uniform variable.
     * @param program The name of the program object.
     * @param name The name of the uniform variable.
     * @return The location of the uniform variable.
     */
    static int GetUniformLocation(unsigned int program, const char* name);

    /**
     * @brief Sets the value of a uniform variable of type int.
     * @param location The location of the uniform variable.
     * @param v0 The value to set.
     */
    static void Uniform1i(int location, int v0);

    /**
     * @brief Sets the value of a uniform variable of type float.
     * @param location The location of the uniform variable.
     * @param v0 The value to set.
     */
    static void Uniform1f(int location, GLfloat v0);

    /**
     * @brief Sets the value of a uniform variable of type vec2.
     * @param location The location of the uniform variable.
     * @param v0 The value to set for the first component.
     * @param v1 The value to set for the second component.
     */
    static void Uniform2f(int location, GLfloat v0, GLfloat v1);

    /**
     * @brief Sets the value of a uniform variable of type vec3.
     * @param location The location of the uniform variable.
     * @param v0 The value to set for the first component.
     * @param v1 The value to set for the second component.
     * @param v2 The value to set for the third component.
     */
    static void Uniform3f(int location, GLfloat v0, GLfloat v1, GLfloat v2);

    /**
     * @brief Sets the value of a uniform variable of type vec4.
     * @param location The location of the uniform variable.
     * @param v0 The value to set for the first component.
     * @param v1 The value to set for the second component.
     * @param v2 The value to set for the third component.
     * @param v3 The value to set for the fourth component.
     */
    static void Uniform4f(int location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

    /**
     * @brief Sets the value of a uniform array variable of type float.
     * @param location The location of the uniform variable.
     * @param count The number of elements in the array.
     * @param value Pointer to the array containing the values to set.
     */
    static void Uniform1fv(int location, GLsizei count, const GLfloat* value);

    /**
     * @brief Sets the value of a uniform array variable of type vec3.
     * @param location The location of the uniform variable.
     * @param count The number of elements in the array.
     * @param value Pointer to the array containing the values to set.
     */
    static void Uniform3fv(int location, GLsizei count, const GLfloat* value);

    /**
     * @brief Sets the value of a uniform array variable of type vec4.
     * @param location The location of the uniform variable.
     * @param count The number of elements in the array.
     * @param value Pointer to the array containing the values to set.
     */
    static void Uniform4fv(int location, GLsizei count, const GLfloat* value);

    /**
     * @brief Sets the value of a uniform matrix variable of type mat3.
     * @param location The location of the uniform variable.
     * @param count The number of elements in the array.
     * @param transpose Whether to transpose the matrix.
     * @param value Pointer to the array containing the matrix values to set.
     */
    static void UniformMatrix3fv(int location, GLsizei count, GLboolean transpose, const GLfloat* value);

    /**
     * @brief Sets the value of a uniform matrix variable of type mat4.
     * @param location The location of the uniform variable.
     * @param count The number of elements in the array.
     * @param transpose Whether to transpose the matrix.
     * @param value Pointer to the array containing the matrix values to set.
     */
    static void UniformMatrix4fv(int location, GLsizei count, GLboolean transpose, const GLfloat* value);

    /**
     * @brief Renders primitives from array data.
     * @param mode The primitive type to render.
     * @param count The number of elements to be rendered.
     * @param type The type of the values in indices.
     * @param indices Pointer to the location where the indices are stored.
     */
    static void DrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices);

    /**
     * @brief Generates mipmaps for a specified texture target.
     * @param target The target texture.
     */
    static void GenerateMipMap(GLenum target);

    /**
     * @brief Gets the height of a window.
     * @param window The GLFW window.
     * @return The height of the window.
     */
    static float GetWindowHeight(Window window);

    /**
     * @brief Gets the width of a window.
     * @param window The GLFW window.
     * @return The width of the window.
     */
    static float GetWindowWidth(Window window);

    /**
     * @brief Renders primitives from array data with a base vertex.
     * @param mode The primitive type to render.
     * @param count The number of elements to be rendered.
     * @param type The type of the values in indices.
     * @param indices Pointer to the location where the indices are stored.
     * @param basevertex The value to add to each element of indices when choosing elements from the enabled vertex arrays.
     */
    static void DrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, void* indices, GLint basevertex);

private:
    static std::vector<KeyCallback> keyCallbacks;
    static std::vector<CursorPosCallback> cursorPosCallbacks;

    // Static callback function to dispatch to instance callback
    static void KeyCallbackDispatcher(GLFWwindow* window, int key, int scancode, int action, int mods);

    // Static callback function to dispatch to instance cursor position callback
    static void CursorPosCallbackDispatcher(GLFWwindow* window, double xpos, double ypos);

    static void errorCallback(int error, const char* description) {
        std::cerr << "GLFW Error " << error << ": " << description << std::endl;
    }

    /**
     * @brief Callback function called when the framebuffer size of a window changes.
     * @param window The GLFW window whose framebuffer size changed.
     * @param width The new width of the framebuffer.
     * @param height The new height of the framebuffer.
     */
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};

inline std::vector<GraphicsUtility::KeyCallback> GraphicsUtility::keyCallbacks;
inline std::vector<GraphicsUtility::CursorPosCallback> GraphicsUtility::cursorPosCallbacks;

