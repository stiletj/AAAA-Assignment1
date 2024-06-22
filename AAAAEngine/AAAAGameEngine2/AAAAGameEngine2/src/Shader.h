#pragma once

#include "GraphicsUtility.h"

#include <string>
#include <unordered_map>

#include "DataStructures.h"

/**
 * @struct ShaderProgramSource
 *
 * @brief A structure representing shader source code for both vertex and fragment shaders.
 */
struct ShaderProgramSource
{
	std::string VertexSource;    ///< Vertex shader source code.
	std::string FragmentSource;  ///< Fragment shader source code.
};

/**
 * @class Shader
 *
 * @brief A class responsible for loading, compiling, and managing shader programs.
 */
class Shader {
private:
	std::string m_FilePath;                           ///< Filepath to the shader source code.
	unsigned int m_RendererID;                        ///< OpenGL renderer ID for the shader program.
	std::unordered_map<std::string, int> m_UniformLocationCache; ///< Cache for uniform locations.

public:
	/**
	 * @brief Construct a shader object and load shader source code from a file.
	 *
	 * @param filepath The path to the shader source code file.
	 */
	Shader(const std::string& filepath);

	/**
	 * @brief Destructor to clean up shader resources.
	 */
	~Shader();

	/**
	 * @brief Bind the shader for rendering.
	 */
	void Bind() const;

	/**
	 * @brief Unbind the shader.
	 */
	void Unbind() const;

	/**
	 * @brief Set an integer uniform in the shader program.
	 *
	 * @param name The name of the uniform variable.
	 * @param value The integer value to set.
	 */
	void SetUniform1i(const std::string& name, int value);

	/**
	 * @brief Set a floating-point uniform in the shader program.
	 *
	 * @param name The name of the uniform variable.
	 * @param value The float value to set.
	 */
	void SetUniform1f(const std::string& name, float value);

	void SetUniform1fv(const std::string& name, unsigned int size, float* values);

	/**
	 * @brief Set a 2-component floating point uniform in the shader program.
	 *
	 * @param name The name of the uniform variable.
	 * @param value A glm::vec2 containing the values to set.
	 */
	void SetUniform2f(const std::string& name, const glm::vec2& value);

	/**
	 * @brief Set a 3-component floating point uniform in the shader program.
	 *
	 * @param name The name of the uniform variable.
	 * @param value A glm::vec3 containing the values to set.
	 */
	void SetUniform3f(const std::string& name, const glm::vec3& value);

	void SetUniform3fv(const std::string& name, unsigned int size, const std::vector<glm::vec3>& value);

	/**
	 * @brief Set a 4-component floating point uniform in the shader program.
	 *
	 * @param name The name of the uniform variable.
	 * @param value A glm::vec4 containing the values to set.
	 */
	void SetUniform4f(const std::string& name, const glm::vec4& value);

	void SetUniform4fv(const std::string& name, unsigned int size, const std::vector<glm::vec4>& value);

	/**
	 * @brief Set a 3x3 matrix uniform in the shader program.
	 *
	 * @param name The name of the uniform variable.
	 * @param matrix A glm::mat3 representing the matrix to set.
	 */
	void SetUniformMat3f(const std::string& name, const glm::mat3& matrix);

	/**
	 * @brief Set a 4x4 matrix uniform in the shader program.
	 *
	 * @param name The name of the uniform variable.
	 * @param matrix A glm::mat4 representing the matrix to set.
	 */
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	/**
	 * @brief Parse shader source code from a file.
	 *
	 * @param filepath The path to the shader source code file.
	 * @return A ShaderProgramSource containing vertex and fragment shader source code.
	 */
	ShaderProgramSource ParseShader(const std::string& filepath);

	/**
	 * @brief Compile a shader from source code.
	 *
	 * @param type The type of shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER).
	 * @param source The shader source code.
	 * @return The OpenGL ID of the compiled shader.
	 */
	unsigned int CompileShader(unsigned int type, const std::string& source);

	/**
	 * @brief Create a shader program from vertex and fragment shaders.
	 *
	 * @param vertexShader The source code for the vertex shader.
	 * @param fragmentShader The source code for the fragment shader.
	 * @return The OpenGL ID of the shader program.
	 */
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	/**
	 * @brief Get the location of a uniform variable in the shader program.
	 *
	 * @param name The name of the uniform variable.
	 * @return The location of the uniform variable.
	 */
	int GetUniformLocation(const std::string& name);
};
