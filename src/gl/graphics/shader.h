#ifndef GFXE_SHADER_H
#define GFXE_SHADER_H

#include <string>
#include <unordered_map>
#include <optional>

#include "../core/integer.h"
#include "../glad/glad.h"

class Shader {
public:
	enum ShaderType {
		VertexShader = GL_VERTEX_SHADER,
		FragmentShader = GL_FRAGMENT_SHADER,
		GeometryShader = GL_GEOMETRY_SHADER,
	};

	enum ProgramInterface {
		ShaderStorageBlock,
		UniformBufferBlock
	};

	struct Uniform {
		u32 loc;
		void set(i32 v);
		void set(f32 v);
		void set(f32 x, f32 y);
		void set(f32 x, f32 y, f32 z);
		void set(f32 x, f32 y, f32 z, f32 w);
		void mat3(const f32* v, u32 count, bool transpose = false);
		void mat4(const f32* v, u32 count, bool transpose = false);
	};

	using ShaderMap = std::unordered_map<ShaderType, GLuint>;
	using ValueMap = std::unordered_map<std::string, GLuint>;

	Shader() = default;
	~Shader() = default;

	Shader& create();
	void destroy();

	Shader& bind();
	Shader& unbind();

	Shader& add(const std::string& source, ShaderType type);
	// Shader& add(const std::vector<u8>& spirv, ShaderType type);
	Shader& link();

	i32 getBlockIndex(ProgramInterface interface, const std::string& name);
	i32 getUniformIndex(const std::string& name);
	i32 getAttributeIndex(const std::string& name);

	void uniformBlockBinding(u32 blockIndex, u32 binding);
	void storageBlockBinding(u32 blockIndex, u32 binding);

	Uniform get(const std::string& name);

	GLuint id() const { return m_id; }

private:
	GLuint m_id{ 0 };
	ShaderMap m_subShaders;

	ValueMap m_attributes, m_uniforms, m_blockIndices;

	bool _shaderCheck(GLuint s);
};

#endif // GFXE_SHADER_H
