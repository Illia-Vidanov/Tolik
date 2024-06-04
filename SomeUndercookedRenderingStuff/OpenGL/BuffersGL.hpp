#ifndef TOLIK_BUFFERS_GL_HPP
#define TOLIK_BUFFERS_GL_HPP

#include <stdint.h>

#include "Setup.hpp"

#include "glad/glad.h"

#include "Debug/Debug.hpp"
#include "Rendering/OpenGL/UtilitiesGL.hpp"

namespace Tolik
{
struct Vertex;

class VBOGL
{
public:
  VBOGL() { GL_CALL(glGenBuffers(1, &m_id)); }
  template<typename T> VBOGL(T *firstElement, std::size_t count) { GL_CALL(glGenBuffers(1, &m_id)); BufferData(firstElement, count); }
  inline void Delete() const { GL_CALL(glDeleteBuffers(1, &m_id)); }

  inline void Bind() const { GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_id)); }
  inline void Unbind() const { GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0)); }

  template<typename T>
  inline void BufferData(T *firstElement, std::size_t count) const;

private:
  uint32_t m_id;
};


class EBOGL
{
public:
  EBOGL() { GL_CALL(glGenBuffers(1, &m_id)); }
  template<typename T> EBOGL(T *firstElement, std::size_t count) { GL_CALL(glGenBuffers(1, &m_id)); BufferData(firstElement, count); }
  inline void Delete() const { GL_CALL(glDeleteBuffers(1, &m_id)); }

  inline void Bind() const { GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id)); }
  inline void Unbind() const { GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); }

  template<typename T>
  inline void BufferData(T *firstElement, std::size_t count);
  inline constexpr std::size_t GetCount() const { return m_count; }
  inline constexpr uint32_t GetGLType() const { return m_glType; }

private:
  uint32_t m_id;
  std::size_t m_count;
  uint32_t m_glType;
};

template<typename T>
inline void VBOGL::BufferData(T *firstElement, std::size_t count) const
{
  Bind();
  GL_CALL(glBufferData(GL_ARRAY_BUFFER, count * sizeof(T), firstElement, GL_STATIC_DRAW));
}

template<typename T>
inline void EBOGL::BufferData(T *firstElement, std::size_t count)
{
  Bind();
  GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(T), firstElement, GL_STATIC_DRAW));
  m_count = count;
  m_glType = GetGLTypeFromType<T>();
}
}

#endif