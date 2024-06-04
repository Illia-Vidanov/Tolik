#ifndef TOLIK_TEXTURE_GL_HPP
#define TOLIK_TEXTURE_GL_HPP

#include <string>
#include <stdint.h>
#include <tuple>
#include <utility>

#include "Setup.hpp"

#include "glad/glad.h"

#include "Math/Vector.hpp"
#include "Debug/Debug.hpp"

namespace Tolik
{
enum class TextureFlags : uint16_t
{
  NONE = 0,

  GenerateMipmap = TOLIK_BIT(0),
  IsTransparent  = TOLIK_BIT(1)
};

class TextureGL
{
public:
  TextureGL(uint32_t type, TextureFlags flags) : m_type(type), m_flags(flags)
  { GL_CALL(glGenTextures(1, &m_id)); }
  template<typename... Args> TextureGL(uint32_t type, TextureFlags flags, const std::string &path, const Vec2i &dimensions) : m_type(type), m_flags(flags)
  { GL_CALL(glGenTextures(1, &m_id)); BufferData(path, dimensions); }
  template<typename... Args> TextureGL(uint32_t type, TextureFlags flags, const std::string &path) : m_type(type), m_flags(flags)
  { GL_CALL(glGenTextures(1, &m_id)); BufferData(path); }
  template<typename... Args> TextureGL(uint32_t type, TextureFlags flags, const std::string &path, const std::tuple<std::pair<int, Args>...> &parametrs, const Vec2i &dimensions = Vec2i::zero()) : m_type(type), m_flags(flags)
  { GL_CALL(glGenTextures(1, &m_id)); SetParametrs(parametrs); BufferData(path, dimensions); }

  inline void Delete() { GL_CALL(glDeleteTextures(1, &m_id)); }

  inline void Bind() const { GL_CALL(glBindTexture(m_type, m_id)); }
  inline void Unbind() const { GL_CALL(glBindTexture(m_type, 0)); }

  inline void SetFlags(TextureFlags flags) { m_flags = flags; }
  void BufferData(const std::string &path, const Vec2i &dimensions = Vec2i::zero());
  template<std::size_t Index = 0, typename... Args> void SetParametrs(const std::tuple<std::pair<int, Args>...> &data) const;
  template<typename T> inline void SetParametr(int name, T data) const { Debug::GetLogger().Error("No function to set glTexParametr with parametr of type \'@0\'", typeid(T).name()); }

  inline bool IsBuffered() { return m_isBuffered; }
  inline uint32_t GetType() { return m_type; }
  inline TextureFlags GetFlags() { return m_flags; }
  //inline std::string GetPath() { return m_path; }

private:
  uint32_t m_id = 0;
  const uint32_t m_type = 0;
  TextureFlags m_flags;
  bool m_isBuffered = false;
  //std::string m_path;
};
}

#include "Rendering/OpenGL/TextureGL.tpp"

#endif