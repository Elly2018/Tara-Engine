#include "framebuffer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Tara {
	AssetPool<FrameBuffer> FrameBuffer::m_framebufferPool = AssetPool<FrameBuffer>();

	FrameBuffer::FrameBuffer(int32_t width, int32_t height)
	{
		m_width = width;
		m_height = height;
		glGenFramebuffers(1, &m_framebufferID);
		Bind();

		// Color
		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureID, 0);
		// Depth, render buffer
		glGenRenderbuffers(1, &m_renderBufferID);
		glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferID);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		Unbind();
	}
	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &m_framebufferID);
		glDeleteTextures(1, &m_textureID);
		glDeleteRenderbuffers(1, &m_renderBufferID);
	}
	AssetPool<FrameBuffer> FrameBuffer::GetAssetPool()
	{
		return m_framebufferPool;
	}

	void FrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
	}
	void FrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void FrameBuffer::BindTexture()
	{
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}
	void FrameBuffer::UnbindTexture()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	uint32_t FrameBuffer::GetTextureID() {
		return m_textureID;
	}
	glm::ivec2 FrameBuffer::GetSize() {
		return glm::ivec2(m_width, m_height);
	}
};