#include "Shader.h"


namespace ClusterEngine
{
	Shader::Shader() {}

	Shader::Shader(const char* vertexPath, const  char* fragmentPath) {
		//retrieve the source codes from the given paths
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		//ensure that file streams can throw exceptions
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try 
		{
			//open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;

			//read buffers and store them in to the stream string
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			//close the file references
			vShaderFile.close();
			fShaderFile.close();

			//copy the string stream in to the strings
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure& e) 
		{
			std::cout << "ERROR::SHADERFILE_NOT_SUCCESSFULLY_READ" << std::endl;
		}

		//convert the string in to a literal string (const char*)
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		//**	compile the shaders		**
		unsigned int vertex, fragment;

		//vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		CheckCompileErrors(vertex, "VERTEX_SHADER");

		//fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		CheckCompileErrors(fragment, "FRAGMENT_SHADER");

		//shader program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		CheckCompileErrors(ID, "PROGRAM");

		//delete the shaders to clear the space
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	//activate program
	void Shader::Use(){
		glUseProgram(ID);
	}

	//utilities functions
	void Shader::SetBool(const std::string& name, bool state) const noexcept
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)state);
	}

	void Shader::SetInt(const std::string& name, int value) const noexcept
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void Shader::SetFloat(const std::string& name, float value) const noexcept
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	void Shader::SetVector(const std::string& name, const Vector3& value) const noexcept
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), value.X, value.Y, value.Z);
	}

	void Shader::SetVector(const std::string& name, float x, float y, float z, float w) const  noexcept
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}

	void Shader::SetBool(const int IDuniform, bool state) const noexcept
	{
		glUniform1i(IDuniform, (int)state);
	}

	void Shader::SetInt(const int IDuniform, int value) const noexcept
	{
		glUniform1i(IDuniform, value);
	}

	void Shader::SetFloat(const int IDuniform, float value) const noexcept
	{
		glUniform1f(IDuniform, value);
	}

	void Shader::SetVector(const int IDuniform, const Vector3& value) const noexcept
	{
		glUniform3f(IDuniform, value.X, value.Y, value.Z);
	}

	void Shader::SetVector(const int IDuniform, float x, float y, float z, float w) const  noexcept
	{
		glUniform4f(IDuniform, x, y, z, w);
	}

	//private functions
	void Shader::CheckCompileErrors(unsigned int shader, std::string type) 
	{
		int success;
		char infoLog[1024];

		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}

	Shader::~Shader()
	{
		glDeleteProgram(ID);
	}
}