#ifndef GFXE_TEXTURE_H
#define GFXE_TEXTURE_H

#include "../core/integer.h"
#include "../glad/glad.h"

#include "buffer.h"

#include <vector>

enum TextureWrap {
	WrapNone = 0,
	ClampToEdge = GL_CLAMP_TO_EDGE,
	Repeat = GL_REPEAT,
	MirroredRepeat = GL_MIRRORED_REPEAT
};

enum TextureFilter {
	Nearest = GL_NEAREST,
	Linear = GL_LINEAR,
	NearestMipMapNearest = GL_NEAREST_MIPMAP_NEAREST,
	NearestMipMapLinear = GL_NEAREST_MIPMAP_LINEAR,
	LinearMipMapLinear = GL_LINEAR_MIPMAP_LINEAR,
	LinearMipMapNearest = GL_LINEAR_MIPMAP_NEAREST
};

enum Format {
	R = GL_RED,
	RG = GL_RG,
	RGB = GL_RGB,
	RGBA = GL_RGBA,
	BGR = GL_BGR,
	BGRA = GL_BGRA,
	Depth = GL_DEPTH_COMPONENT,
	DepthStencil = GL_DEPTH_STENCIL
};

enum CubeMapSide {
	PositiveX = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	NegativeX = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	PositiveY = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	NegativeY = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	PositiveZ = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	NegativeZ = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};

enum TextureType {
	Texture1D = GL_TEXTURE_1D,
	Texture2D = GL_TEXTURE_2D,
	Texture2DArray = GL_TEXTURE_2D_ARRAY,
	Texture3D = GL_TEXTURE_3D,
	CubeMap = GL_TEXTURE_CUBE_MAP
};

class Texture {
public:

	Texture() = default;
	~Texture() = default;

	Texture& create(
		TextureType type,
		Format format,
		u32 width, u32 height, u32 depth = 1,
		bool floatingPoint = false, u32 depthSize = 24
	);

	void destroy();

	Texture& wrapMode(TextureWrap s, TextureWrap t, TextureWrap r = TextureWrap::WrapNone);
	Texture& filter(TextureFilter min, TextureFilter mag);

	Texture& array(u32 layerCount);

	Texture& updateCube(const u8* data, CubeMapSide side, DataType dataType = DataType::TypeUByte);
	Texture& updateArray(const u8* data, DataType dataType = DataType::TypeUByte);
	Texture& update(const u8* data, DataType dataType);

	Texture& generateMipmaps();

	Texture& bind(u32 slot = 0);
	Texture& unbind();

	GLuint id() const { return m_id; }

	u32 width() const { return m_width; }
	u32 height() const { return m_height; }
	u32 depth() const { return m_depth; }
	u32 layerCount() const { return m_layerCount; }
	TextureType type() const { return m_type; }
	Format format() const { return m_format; }

private:
	GLuint m_id{ 0 };
	TextureType m_type;
	Format m_format;

	bool m_floatingPoint{ false };
	u32 m_depthSize{ 24 };
	u32 m_layerCount{ 0 };

	u32 m_width{ 0 }, m_height{ 0 }, m_depth{ 1 };
};

inline static GLenum getInternalFormat(Format format, bool floatingPoint = false, u32 depthSize = 24) {
	switch (format) {
		case Format::R: return floatingPoint ? GL_R16F : GL_R8;
		case Format::RG: return floatingPoint ? GL_RG16F : GL_RG8;
		case Format::BGR:
		case Format::RGB: return floatingPoint ? GL_RGB16F : GL_RGB8;
		case Format::BGRA:
		case Format::RGBA: return floatingPoint ? GL_RGBA16F : GL_RGBA8;
		case Format::Depth: {
			switch (depthSize) {
				case 16: return GL_DEPTH_COMPONENT16;
				case 24: return GL_DEPTH_COMPONENT24;
				case 32: return floatingPoint ? GL_DEPTH_COMPONENT32F : GL_DEPTH_COMPONENT32;
				default: return GL_DEPTH_COMPONENT24;
			}
		}
		case Format::DepthStencil: return floatingPoint ? GL_DEPTH32F_STENCIL8 : GL_DEPTH24_STENCIL8;
		default: return 0;
	}
}

#endif // GFXE_TEXTURE_H