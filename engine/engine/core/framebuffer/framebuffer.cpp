#include "framebuffer.h"
// Include std library
#include <map>

// Include third party library
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Tara {
	AssetPool<FrameBuffer>* FrameBuffer::m_framebufferPool = nullptr;

	std::map<MSAASamples, int32_t> sampleMap = {
		{MSAASamples::None, 1},
		{MSAASamples::_2x, 2},
		{MSAASamples::_4x, 4},
		{MSAASamples::_8x, 8},
		{MSAASamples::_16x, 16},
	};

	FrameBuffer::FrameBuffer(int32_t width, int32_t height)
	{
		m_width = width;
		m_height = height;
		glGenFramebuffers(1, &m_framebufferID);
		glGenTextures(1, &m_textureID);
		GetAssetPool().Add(this);
	}
	FrameBuffer::~FrameBuffer()
	{
		TARA_DEBUG_LEVEL("Framebuffer destroy! %s", 1, Name.c_str());
		glDeleteFramebuffers(1, &m_framebufferID);
		glDeleteTextures(1, &m_textureID);
	}
	AssetPool<FrameBuffer>& FrameBuffer::GetAssetPool()
	{
		if (!m_framebufferPool) m_framebufferPool = new AssetPool<FrameBuffer>();
		return *m_framebufferPool;
	}

	void FrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
	}
	void FrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	bool FrameBuffer::BindTexture(FrameBufferTextureType type)
	{
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		return true;
	}
	void FrameBuffer::UnbindTexture()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void FrameBuffer::Resize(int32_t _w, int32_t _h)
	{
		m_width = _w;
		m_height = _h;

		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	uint32_t& FrameBuffer::FramebufferID()
	{
		return m_framebufferID;
	}
	uint32_t& FrameBuffer::TextureID() {
		return m_textureID;
	}
	glm::ivec2& FrameBuffer::Size() {
		glm::ivec2 v = glm::ivec2(m_width, m_height);
		return v;
	}

	
	DisplayFrameBuffer::DisplayFrameBuffer(int32_t width, int32_t height, MSAASamples sample) : FrameBuffer(width, height)
	{
		m_ssaa = sample;

		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
		// Samples color texture
		glGenTextures(1, &m_multiSampledTextureID);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_multiSampledTextureID);
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, sampleMap.at(m_ssaa), GL_RGB, m_width, m_height, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_multiSampledTextureID, 0);
		// Depth, render buffer
		glGenRenderbuffers(1, &m_renderBufferID);
		glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferID);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, sampleMap.at(m_ssaa), GL_DEPTH24_STENCIL8, m_width, m_height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferID);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

		// second post processing framebuffer
		glGenFramebuffers(1, &m_intermediateFramebufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_intermediateFramebufferID);
		// Color
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureID, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
	}

	DisplayFrameBuffer::~DisplayFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_intermediateFramebufferID);
		glDeleteTextures(1, &m_multiSampledTextureID);
		glDeleteRenderbuffers(1, &m_renderBufferID);
	}

	void DisplayFrameBuffer::Blit()
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_framebufferID);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_intermediateFramebufferID);
		glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	}

	void DisplayFrameBuffer::SetSamples(MSAASamples _samples)
	{
		m_ssaa = _samples;

		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_multiSampledTextureID);
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, sampleMap.at(m_ssaa), GL_RGB, m_width, m_height, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

		glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferID);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, sampleMap.at(m_ssaa), GL_DEPTH24_STENCIL8, m_width, m_height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
	void DisplayFrameBuffer::Resize(int32_t _w, int32_t _h)
	{
		FrameBuffer::Resize(_w, _h);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_multiSampledTextureID);
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, sampleMap.at(m_ssaa), GL_RGB, m_width, m_height, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

		glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferID);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, sampleMap.at(m_ssaa), GL_DEPTH24_STENCIL8, m_width, m_height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	ShadowFrameBuffer::ShadowFrameBuffer(int32_t width, int32_t height) : FrameBuffer(width, height)
	{
		// Frame buffer and depth binding
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);

		// depth texture
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_textureID, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	ShadowFrameBuffer::~ShadowFrameBuffer()
	{
	}
};