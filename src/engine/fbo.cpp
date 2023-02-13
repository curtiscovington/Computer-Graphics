#include <engine/fbo.h>

FBO::FBO() {
    glGenFramebuffers(1, &m_id);
}

FBO::~FBO() {
    Delete();
}

void FBO::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

void FBO::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::Delete() {
    glDeleteFramebuffers(1, &m_id);
}