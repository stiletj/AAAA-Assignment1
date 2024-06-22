#include "GraphicsUtility.h"

int GraphicsUtility::Initialise()
{
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Error: GLFW initialization failed" << std::endl;
        return -1; 
    }

    glfwSetErrorCallback(errorCallback);

    // Specify OpenGL version (3.3 in this example)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Set the profile to core
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int GraphicsUtility::initialiseOpenGLExtensions() {
    // Initialize GLEW
    glewExperimental = GL_TRUE; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Error: GLEW initialization failed" << std::endl;
        Terminate();
        return -1;
    }
}

void GraphicsUtility::Terminate()
{
    glfwTerminate(); 
}

void GraphicsUtility::destroyWindow(Window window)
{
    glfwDestroyWindow(window); 
}

GLFWwindow* GraphicsUtility::CreateWindow(const char* title) {
    // Get the primary monitor (you can use other monitors if needed)
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();

    // Get the video mode of the monitor
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "My GLFW Window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    return window;
}

GLFWwindow* GraphicsUtility::CreateWindow(const char* title, int width, int height ) {
    GLFWwindow* window = glfwCreateWindow(width, height, "My GLFW Window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    return window; 
}

void GraphicsUtility::makeContextCurrent(GLFWwindow* window) {
    glfwMakeContextCurrent(window);
}

void GraphicsUtility::setFramebufferSizeCallback(GLFWwindow* window) {
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}

bool GraphicsUtility::shouldClose(GLFWwindow* window) {
    return glfwWindowShouldClose(window);
}

void GraphicsUtility::swapBuffers(GLFWwindow* window) {
    glfwSwapBuffers(window);
}

void GraphicsUtility::pollEvents() {
    glfwPollEvents();
}

void GraphicsUtility::setWindowShouldClose(GLFWwindow* window, bool value) {
    glfwSetWindowShouldClose(window, value ? GLFW_TRUE : GLFW_FALSE);
}

void GraphicsUtility::AddKeyCallback(KeyCallback callback) {
    keyCallbacks.push_back(callback);
}

void GraphicsUtility::AddCursorPosCallback(CursorPosCallback callback)
{
    cursorPosCallbacks.push_back(callback);
}

void GraphicsUtility::SetClearColor(float red, float green, float blue, float alpha)
{
    glClearColor(red, green, blue, alpha);
}

void GraphicsUtility::Clear(int buffers)
{
    glClear(buffers);
}

void GraphicsUtility::Enable(GLenum cap)
{
    glEnable(cap);
}

void GraphicsUtility::Disable(GLenum cap)
{
    glDisable(cap);
}

void GraphicsUtility::Begin(GLenum mode)
{
    glBegin(mode);
}

void GraphicsUtility::End()
{
    glEnd();
}

void GraphicsUtility::Color3f(float red, float green, float blue)
{
    glColor3f(red, green, blue);
}

void GraphicsUtility::TexCoord2f(float s, float t)
{
    glTexCoord2f(s, t);
}

void GraphicsUtility::Vertex3f(float x, float y, float z)
{
    glVertex3f(x, y, z);
}

void GraphicsUtility::Normal3f(float nx, float ny, float nz)
{
    glNormal3f(nx, ny, nz);
}

void GraphicsUtility::PolygonMode(GLenum face, GLenum mode)
{
    glPolygonMode(face, mode);
}

void GraphicsUtility::GenerateVertexArrays(GLsizei value, unsigned int *id)
{
    glGenVertexArrays(value, id);
}

void GraphicsUtility::DeleteVertexArrays(GLsizei value, unsigned int* id)
{
    glDeleteVertexArrays(value, id);
}

void GraphicsUtility::EnableVertexAttribArray(unsigned int index)
{
    glEnableVertexAttribArray(index);
}

void GraphicsUtility::VertexAttribPointer(unsigned int index, int size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void GraphicsUtility::BindVertexArray(unsigned int id)
{
    glBindVertexArray(id);
}

void GraphicsUtility::GenBuffers(GLsizei n, unsigned int* buffers)
{
    glGenBuffers(n, buffers);
}

void GraphicsUtility::BindBuffer(GLenum target, unsigned int buffer)
{
    glBindBuffer(target, buffer);
}

void GraphicsUtility::BufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)
{
    glBufferData(target, size, data, usage);
}

void GraphicsUtility::DeleteBuffers(GLsizei n, const unsigned int* buffers)
{
    glDeleteBuffers(n, buffers);
}

void GraphicsUtility::GenTextures(GLsizei n, unsigned int* textures)
{
    glGenTextures(n, textures);
}

void GraphicsUtility::BindTexture(GLenum target, unsigned int texture)
{
    glBindTexture(target, texture);
}

void GraphicsUtility::TexParameteri(GLenum target, GLenum pname, int param)
{
    glTexParameteri(target, pname, param);
}

void GraphicsUtility::TexImage2D(GLenum target, int level, int internalformat, GLsizei width, GLsizei height, int border, GLenum format, GLenum type, const void* pixels)
{
    glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

void GraphicsUtility::DeleteTextures(GLsizei n, const unsigned int* textures)
{
    glDeleteTextures(n, textures);
}

unsigned int GraphicsUtility::CreateShader(GLenum type)
{
    return glCreateShader(type);
}

void GraphicsUtility::ShaderSource(unsigned int shader, GLsizei count, const char* const* string, const int* length)
{
    glShaderSource(shader, count, string, length);
}

void GraphicsUtility::CompileShader(unsigned int shader)
{
    glCompileShader(shader);
}

void GraphicsUtility::GetShaderiv(unsigned int shader, GLenum pname, int* params)
{
    glGetShaderiv(shader, pname, params);
}

void GraphicsUtility::GetShaderInfoLog(unsigned int shader, GLsizei maxLength, GLsizei* length, char* infoLog)
{
    glGetShaderInfoLog(shader, maxLength, length, infoLog);
}

void GraphicsUtility::DeleteShader(unsigned int shader)
{
    glDeleteShader(shader);
}

unsigned int GraphicsUtility::CreateProgram()
{
    return glCreateProgram();
}

void GraphicsUtility::DeleteProgram(unsigned int id)
{
    glDeleteProgram(id); 
}

void GraphicsUtility::AttachShader(unsigned int program, unsigned int shader)
{
    glAttachShader(program, shader);
}

void GraphicsUtility::LinkProgram(unsigned int program)
{
    glLinkProgram(program);
}

void GraphicsUtility::ValidateProgram(unsigned int program)
{
    glValidateProgram(program);
}

void GraphicsUtility::UseProgram(unsigned int program)
{
    glUseProgram(program);
}

int GraphicsUtility::GetUniformLocation(unsigned int program, const char* name)
{
    return glGetUniformLocation(program, name);
}

void GraphicsUtility::Uniform1i(int location, int v0)
{
    glUniform1i(location, v0);
}

void GraphicsUtility::Uniform1f(int location, GLfloat v0)
{
    glUniform1f(location, v0);
}

void GraphicsUtility::Uniform2f(int location, GLfloat v0, GLfloat v1)
{
    glUniform2f(location, v0, v1);
}

void GraphicsUtility::Uniform3f(int location, GLfloat v0, GLfloat v1, GLfloat v2)
{
    glUniform3f(location, v0, v1, v2);
}

void GraphicsUtility::Uniform4f(int location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    glUniform4f(location, v0, v1, v2, v3);
}

void GraphicsUtility::Uniform1fv(int location, GLsizei count, const GLfloat* value)
{
    glUniform1fv(location, count, value);
}

void GraphicsUtility::Uniform3fv(int location, GLsizei count, const GLfloat* value)
{
    glUniform3fv(location, count, value);
}

void GraphicsUtility::Uniform4fv(int location, GLsizei count, const GLfloat* value)
{
    glUniform4fv(location, count, value);
}

void GraphicsUtility::UniformMatrix3fv(int location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    glUniformMatrix3fv(location, count, transpose, value);
}

void GraphicsUtility::UniformMatrix4fv(int location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    glUniformMatrix4fv(location, count, transpose, value);
}

void GraphicsUtility::DrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices)
{
    glDrawElements(mode, count, type, indices); 
}

void GraphicsUtility::GenerateMipMap(GLenum target)
{
    glGenerateMipmap(target); 
}

float GraphicsUtility::GetWindowHeight(Window window)
{
    int width;
    int height;
    
    glfwGetWindowSize(window, &width, &height);

    return (float)height;
}

float GraphicsUtility::GetWindowWidth(Window window)
{
    int width;
    int height;

    glfwGetWindowSize(window, &width, &height);

    return (float)width;
}

void GraphicsUtility::DrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, void* indices, GLint basevertex)
{
    glDrawElementsBaseVertex(mode, count, type, indices, basevertex);
}

/*
void GraphicsUtility::KeyCallbackDispatcher(GLFWwindow* window, int key, int scancode, int action, int mods) {
    for (auto& callback : keyCallbacks) {
        callback(window, key, scancode, action, mods);
    }
}

void GraphicsUtility::CursorPosCallbackDispatcher(GLFWwindow* window, double xpos, double ypos) {
    for (auto& callback : cursorPosCallbacks) {
        callback(window, xpos, ypos);
    }
}
*/

void GraphicsUtility::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); // Adjust the viewport
}