#include "Rendering/OpenGL/VAOGL.hpp"

#include <vector>
#include <stdint.h>

#include "Setup.hpp"

#include "glad/glad.h"

#include "Rendering/OpenGL/BuffersGL.hpp"
#include "Rendering/OpenGL/UtilitiesGL.hpp"
#include "Debug/Debug.hpp"

namespace Tolik
{
void BufferLayoutGL::AddBufferLayoutElement(uint32_t type, int8_t size, uint8_t normalized)
{
  m_layoutElements.emplace_back(type, size, normalized, m_stride);
  m_stride += GetSizeFromGLType(type) * size;
}

void VAOGL::AddVBO(const VBOGL &vbo, const BufferLayoutGL &layout) const
{
  Bind();
  vbo.Bind();
  const std::vector<BufferLayoutElementGL> &elements = layout.GetLayoutElements();

  for(std::size_t i = 0; i < elements.size(); i++)
  {
    GL_CALL(glVertexAttribPointer(i, elements[i].size, elements[i].type, elements[i].normalized, layout.GetStride(), reinterpret_cast<void*>(static_cast<intptr_t>(elements[i].offset))));
    GL_CALL(glEnableVertexAttribArray(i));
  }
}

void VAOGL::AddEBO(const EBOGL &ebo) const
{
  Bind();
  ebo.Bind();
}
}