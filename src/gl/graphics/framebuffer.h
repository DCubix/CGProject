#ifndef GFXE_FRAMEBUFFER_H
#define GFXE_FRAMEBUFFER_H

#include "../glad/glad.h"
#include "texture.h"

#include <vector>

enum FrameBufferTarget {
	DRFrameBuffer = GL_FRAMEBUFFER,
	DrawFrameBuffer = GL_DRAW_FRAMEBUFFER,
	ReadFrameBuffer = GL_READ_FRAMEBUFFER
};

enum Attachment {
	ColorAttachment = GL_COLOR_ATTACHMENT0,
	DepthAttachment = GL_DEPTH_ATTACHMENT,
	StencilAttachment = GL_STENCIL_ATTACHMENT,
	DepthStencilAttachment = GL_DEPTH_STENCIL_ATTACHMENT,
	NoAttachment = GL_NONE
};

enum ClearBufferMask {
	ColorBuffer = GL_COLOR_BUFFER_BIT,
	DepthBuffer = GL_DEPTH_BUFFER_BIT,
	StencilBuffer = GL_STENCIL_BUFFER_BIT
};

class FrameBuffer {
public:
	FrameBuffer() = default;
	~FrameBuffer() = default;

	FrameBuffer& create(u32 width, u32 height, u32 depth = 1);
	void destroy();

	FrameBuffer& color(
		TextureType type, Format format,
		bool floatingPoint = false,
		u32 depthSize = 24,
		u32 mip = 0,
		u32 layer = 0
	);

	FrameBuffer& depth(u32 depthSize = 24);
	FrameBuffer& stencil();

	FrameBuffer& renderBuffer(
		Format storage,
		Attachment attachment,
		bool floatingPoint = false,
		u32 depthSize = 24
	);

	FrameBuffer& bind(
		FrameBufferTarget target = FrameBufferTarget::DRFrameBuffer,
		Attachment readBuffer = Attachment::NoAttachment
	);
	FrameBuffer& unbind(bool resetViewport = true);

	void drawBuffer(u32 index);
	void resetDrawBuffers();

	void blit(
		int sx0, int sy0, int sx1, int sy1,
		int dx0, int dy0, int dx1, int dy1,
		ClearBufferMask mask,
		TextureFilter filter
	);

	GLuint id() const { return m_id; }

	u32 width() const { return m_width; }
	u32 height() const { return m_height; }
	u32 depth() const { return m_depth; }

	Texture& color(u32 id) { return m_colorAttachments[id]; }

private:
	struct SavedColorAttachment {
		Format format;
		TextureType target;
		u32 mip;
	};

	GLuint m_id{ 0 }, m_rboID{ 0 };

	u32 m_width, m_height, m_depth{1};
	i32 m_viewport[4];

	FrameBufferTarget m_bound;

	Format m_renderBufferStorage;

	std::vector<Texture> m_colorAttachments;
	Texture m_depthAttachment, m_stencilAttachment;

	std::vector<SavedColorAttachment> m_savedColorAttachments;
};

#endif // GFXE_FRAMEBUFFER_H
