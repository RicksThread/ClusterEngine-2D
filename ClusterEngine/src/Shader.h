#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include "Math/Vector3.hpp"

namespace ClusterEngine
{
	class Shader
	{
	public:
		unsigned int ID;

		Shader();
		Shader(const char* vertexPath, const  char* fragmentPath);

		void Use();
		void SetBool(const std::string& name, bool state) const noexcept;
		void SetInt(const std::string& name, int value) const noexcept;
		void SetFloat(const std::string& name, float value) const noexcept;
		void SetVector(const std::string& name, const Vector3& value) const noexcept;
		void SetVector(const std::string& name, float x, float y, float z, float w) const noexcept;
		
		void SetBool(const int IDuniform, bool state) const noexcept;
		void SetInt(const int IDuniform, int value) const noexcept;
		void SetFloat(const int IDuniform, float value) const noexcept;
		void SetVector(const int IDuniform, const Vector3& value) const noexcept;
		void SetVector(const int IDuniform, float x, float y, float z, float w) const noexcept;
		~Shader();
	private:
		void CheckCompileErrors(unsigned int shader, std::string type);
	};
}