#ifndef TOLIK_VAO_GL_HPP
#define TOLIK_VAO_GL_HPP

#include <vector>
#include <stdint.h>

#include "Setup.hpp"

#include "glad/glad.h"

#include "Debug/Debug.hpp"

namespace Tolik
{
class VBOGL;
class EBOGL;

struct BufferLayoutElementGL
{
  inline BufferLayoutElementGL(uint32_t newType, int8_t newSize, int8_t newNormalized, int8_t newOffset) : type(newType), size(newSize), normalized(newNormalized), offset(newOffset) {}

  uint32_t type = GL_FLOAT;
  int8_t size = 3;
  int8_t normalized = 0;
  int8_t offset = 0; // hope that one vertex won't be larger then 255 bytes
};


class BufferLayoutGL
{
public:
  inline BufferLayoutGL() = default;
  template<typename... Args> BufferLayoutGL(uint32_t type, int8_t size, int8_t normalized, Args... args) { static_assert(!(sizeof...(Args) % 3), "Number of arguments is not multiple of 3"); AddBufferLayoutElement(type, size, normalized); Iterate(args...); }

  template<typename... Args> void Iterate(uint32_t type, int8_t size, int8_t normalized, Args... args) { AddBufferLayoutElement(type, size, normalized); Iterate(args...); }
  inline void Iterate() {}
  void AddBufferLayoutElement(uint32_t type, int8_t size, uint8_t normalized);
  inline std::size_t GetStride() const { return m_stride; }
  inline const std::vector<BufferLayoutElementGL> &GetLayoutElements() const { return m_layoutElements; }

private:
  std::vector<BufferLayoutElementGL> m_layoutElements;
  std::size_t m_stride = 0;
};


class VAOGL
{
public:
  inline VAOGL() { GL_CALL(glGenVertexArrays(1, &m_id)); }
  inline void Delete() const { GL_CALL(glDeleteVertexArrays(1, &m_id)); }

  inline void Bind() const { GL_CALL(glBindVertexArray(m_id)); }
  inline void Unbind() const { GL_CALL(glBindVertexArray(0)); }

  void AddVBO(const VBOGL &vbo, const BufferLayoutGL &layout) const;
  void AddEBO(const EBOGL &ebo) const;

private:
  uint32_t m_id;
};
}

#endif