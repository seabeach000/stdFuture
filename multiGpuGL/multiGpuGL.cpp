// multiGpuGL.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "GL/glew.h"
#include "GL/wglew.h"

#include <memory>

#define MAX_GPU 4
int main()
{
	//std::shared_ptr<sf::Context> device_;
	//device_.reset(new sf::Context());
	//device_->setActive(true);


	//GLenum err = glewInit();
	//if (err != GLEW_OK)
	//{
	//	fprintf(stderr, "error initializaing GLew %s\n", glewGetErrorString(err));
	//	return 0;
	//}
	//if (!GLEW_VERSION_3_0)
	//	return 0;

	GLuint fbo_;
	PIXELFORMATDESCRIPTOR pfd;
	int    pf, gpuIndex = 0;
	HGPUNV hGPU[MAX_GPU];
	HGPUNV GpuMask[MAX_GPU];
	HDC    affDC;
	HGLRC  affRC;

	// Get a list of the first MAX_GPU GPUs in the system
	while ((gpuIndex < MAX_GPU) && wglEnumGpusNV(gpuIndex,
		&hGPU[gpuIndex])) {
		gpuIndex++;
	}

	// Create an affinity-DC associated with the first GPU
	GpuMask[0] = hGPU[0];
	GpuMask[1] = NULL;

	affDC = wglCreateAffinityDCNV(GpuMask);

	// Set a pixelformat on the affinity-DC
	pf = ChoosePixelFormat(affDC, &pfd);
	SetPixelFormat(affDC, pf, &pfd);
	DescribePixelFormat(affDC, pf, sizeof(PIXELFORMATDESCRIPTOR),
		&pfd);

	affRC = wglCreateContext(affDC);
	wglMakeCurrent(affDC, affRC);

	glGenFramebuffers(1, &fbo_);
	// Make a previously created FBO current so we have something
	// to render into. Since there's no window, the default system
	// created FBO is incomplete.
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo_);


	//glBindFramebuffer(GL_FRAMEBUFFER, fbo_);


	glDeleteFramebuffers(1, &fbo_);
	//device_.reset();

    return 0;
}

