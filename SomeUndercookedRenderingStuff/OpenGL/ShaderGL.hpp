#ifndef TOLIK_SHADER_GL_HPP
#define TOLIK_SHADER_GL_HPP

#include <stdint.h>
#include <string>
#include <functional>
#include <initializer_list>

#include "Setup.hpp"

#include "glad/glad.h"

#include "Utilities/FileReader.hpp"
#include "Debug/Debug.hpp"

namespace Tolik
{
class Debug;

class ShaderGL
{
public:
  template<typename... Args>  ShaderGL(const Args&... args) { static_assert(std::conjunction_v<std::is_convertible<Args, std::string>...>, "You need strings for shader constructor"); CreateProgram({CompileShader(static_cast<std::string>(args))...}); }
  inline void Delete() const { GL_CALL(glDeleteProgram(m_id)); }
  
  // Temp. Not sure if needed
  uint32_t GetID() const { return m_id; }

  inline void Use() const { GL_CALL(glUseProgram(m_id)); }
  
  template<typename T> inline void SetUniform(const std::string &name, T t0) const { Debug::GetLogger("main").Error("No overload of ShaderGL::SetUniform with such parametrs exist ", __PRETTY_FUNCTION__); }
  template<typename T> inline void SetUniform(const std::string &name, T t0, T t1) const { Debug::GetLogger("main").Error("No overload of ShaderGL::SetUniform with such parametrs exist ", __PRETTY_FUNCTION__); }
  template<typename T> inline void SetUniform(const std::string &name, T t0, T t1, T t2) const { Debug::GetLogger("main").Error("No overload of ShaderGL::SetUniform with such parametrs exist ", __PRETTY_FUNCTION__); }
  template<typename T> inline void SetUniform(const std::string &name, T t0, T t1, T t2, T t3) const { Debug::GetLogger("main").Error("No overload of ShaderGL::SetUniform with such parametrs exist ", __PRETTY_FUNCTION__); }
  template<typename T> inline void SetUniform1v(const std::string &name, int count, const T *t) const { Debug::GetLogger("main").Error("No overload of ShaderGL::SetUniform with such parametrs exist ", __PRETTY_FUNCTION__); }
  template<typename T> inline void SetUniform2v(const std::string &name, int count, const T *t) const { Debug::GetLogger("main").Error("No overload of ShaderGL::SetUniform with such parametrs exist ", __PRETTY_FUNCTION__); }
  template<typename T> inline void SetUniform3v(const std::string &name, int count, const T *t) const { Debug::GetLogger("main").Error("No overload of ShaderGL::SetUniform with such parametrs exist ", __PRETTY_FUNCTION__); }
  template<typename T> inline void SetUniform4v(const std::string &name, int count, const T *t) const { Debug::GetLogger("main").Error("No overload of ShaderGL::SetUniform with such parametrs exist ", __PRETTY_FUNCTION__); }
  inline void SetUniformMatrix2(const std::string &name, int count, bool transpose, const float *t) const;
  inline void SetUniformMatrix3(const std::string &name, int count, bool transpose, const float *t) const;
  inline void SetUniformMatrix4(const std::string &name, int count, bool transpose, const float *t) const;
  inline void SetUniformMatrix2x3(const std::string &name, int count, bool transpose, const float *t) const;
  inline void SetUniformMatrix3x2(const std::string &name, int count, bool transpose, const float *t) const;
  inline void SetUniformMatrix2x4(const std::string &name, int count, bool transpose, const float *t) const;
  inline void SetUniformMatrix4x2(const std::string &name, int count, bool transpose, const float *t) const;
  inline void SetUniformMatrix3x4(const std::string &name, int count, bool transpose, const float *t) const;
  inline void SetUniformMatrix4x3(const std::string &name, int count, bool transpose, const float *t) const;

  inline bool operator==(const ShaderGL &other) { return m_id == other.m_id; }
  inline bool operator!=(const ShaderGL &other) { return m_id != other.m_id; }

private:
  static inline const std::unordered_map<std::string, uint32_t> s_extensionToShaderType = 
  {
    { "vert", GL_VERTEX_SHADER },
    { "frag", GL_FRAGMENT_SHADER },
    { "geom", GL_GEOMETRY_SHADER },
    { "vs", GL_VERTEX_SHADER },
    { "fs", GL_FRAGMENT_SHADER },
    { "gs", GL_GEOMETRY_SHADER },
  };

  uint32_t m_id;

  uint32_t CompileShader(const std::string &path) const;
  void CreateProgram(std::initializer_list<uint32_t> list);
  int GetLocation(const std::string &name) const;
  inline static uint32_t ExtensionToShaderType(const std::string &extension) { return s_extensionToShaderType.at(extension); }
};
}

#include "Rendering/OpenGL/ShaderGL.tpp"

#endif