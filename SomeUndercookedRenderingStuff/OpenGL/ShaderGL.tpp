#ifndef TOLIK_SHADER_GL_TPP
#define TOLIK_SHADER_GL_TPP

#ifndef TOLIK_SHADER_GL_HPP
#error __FILE__ should only be included from ShaderGL.hpp
#endif

namespace Tolik
{
template<> inline void ShaderGL::SetUniform<int>(const std::string &name, int t0) const
{
  Use();
  GL_CALL(glUniform1i(GetLocation(name), t0));
}

template<> inline void ShaderGL::SetUniform<int>(const std::string &name, int t0, int t1) const
{
  Use();
  GL_CALL(glUniform2i(GetLocation(name), t0, t1));
}

template<> inline void ShaderGL::SetUniform<int>(const std::string &name, int t0, int t1, int t2) const
{
  Use();
  GL_CALL(glUniform3i(GetLocation(name), t0, t1, t2));
}

template<> inline void ShaderGL::SetUniform<int>(const std::string &name, int t0, int t1, int t2, int t3) const
{
  Use();
  GL_CALL(glUniform4i(GetLocation(name), t0, t1, t2, t3));
}

template<> inline void ShaderGL::SetUniform1v<int>(const std::string &name, int count, const int *t) const
{
  Use();
  GL_CALL(glUniform1iv(GetLocation(name), count, t));
}

template<> inline void ShaderGL::SetUniform2v<int>(const std::string &name, int count, const int *t) const
{
  Use();
  GL_CALL(glUniform2iv(GetLocation(name), count, t));
}

template<> inline void ShaderGL::SetUniform3v<int>(const std::string &name, int count, const int *t) const
{
  Use();
  GL_CALL(glUniform3iv(GetLocation(name), count, t));
}

template<> inline void ShaderGL::SetUniform4v<int>(const std::string &name, int count, const int *t) const
{
  Use();
  GL_CALL(glUniform4iv(GetLocation(name), count, t));
}


template<> inline void ShaderGL::SetUniform<float>(const std::string &name, float t0) const
{
  Use();
  GL_CALL(glUniform1f(GetLocation(name), t0));
}

template<> inline void ShaderGL::SetUniform<float>(const std::string &name, float t0, float t1) const
{
  Use();
  GL_CALL(glUniform2f(GetLocation(name), t0, t1));
}

template<> inline void ShaderGL::SetUniform<float>(const std::string &name, float t0, float t1, float t2) const
{
  Use();
  GL_CALL(glUniform3f(GetLocation(name), t0, t1, t2));
}

template<> inline void ShaderGL::SetUniform<float>(const std::string &name, float t0, float t1, float t2, float t3) const
{
  Use();
  GL_CALL(glUniform4f(GetLocation(name), t0, t1, t2, t3));
}

template<> inline void ShaderGL::SetUniform1v<float>(const std::string &name, int count, const float *t) const
{
  Use();
  GL_CALL(glUniform1fv(GetLocation(name), count, t));
}

template<> inline void ShaderGL::SetUniform2v<float>(const std::string &name, int count, const float *t) const
{
  Use();
  GL_CALL(glUniform2fv(GetLocation(name), count, t));
}

template<> inline void ShaderGL::SetUniform3v<float>(const std::string &name, int count, const float *t) const
{
  Use();
  GL_CALL(glUniform3fv(GetLocation(name), count, t));
}

template<> inline void ShaderGL::SetUniform4v<float>(const std::string &name, int count, const float *t) const
{
  Use();
  GL_CALL(glUniform4fv(GetLocation(name), count, t));
}


template<> inline void ShaderGL::SetUniform<uint32_t>(const std::string &name, uint32_t t0) const
{
  Use();
  GL_CALL(glUniform1ui(GetLocation(name), t0));
}

template<> inline void ShaderGL::SetUniform<uint32_t>(const std::string &name, uint32_t t0, uint32_t t1) const
{
  Use();
  GL_CALL(glUniform2ui(GetLocation(name), t0, t1));
}

template<> inline void ShaderGL::SetUniform<uint32_t>(const std::string &name, uint32_t t0, uint32_t t1, uint32_t t2) const
{
  Use();
  GL_CALL(glUniform3ui(GetLocation(name), t0, t1, t2));
}

template<> inline void ShaderGL::SetUniform<uint32_t>(const std::string &name, uint32_t t0, uint32_t t1, uint32_t t2, uint32_t t3) const
{
  Use();
  GL_CALL(glUniform4ui(GetLocation(name), t0, t1, t2, t3));
}

template<> inline void ShaderGL::SetUniform1v<uint32_t>(const std::string &name, int count, const uint32_t *t) const
{
  Use();
  GL_CALL(glUniform1uiv(GetLocation(name), count, t));
}

template<> inline void ShaderGL::SetUniform2v<uint32_t>(const std::string &name, int count, const uint32_t *t) const
{
  Use();
  GL_CALL(glUniform2uiv(GetLocation(name), count, t));
}

template<> inline void ShaderGL::SetUniform3v<uint32_t>(const std::string &name, int count, const uint32_t *t) const
{
  Use();
  GL_CALL(glUniform3uiv(GetLocation(name), count, t));
}

template<> inline void ShaderGL::SetUniform4v<uint32_t>(const std::string &name, int count, const uint32_t *t) const
{
  Use();
  GL_CALL(glUniform4uiv(GetLocation(name), count, t));
}


inline void ShaderGL::SetUniformMatrix2(const std::string &name, int count, bool transpose, const float *t) const
{
  Use();
  GL_CALL(glUniformMatrix2fv(GetLocation(name), count, transpose, t));
}

inline void ShaderGL::SetUniformMatrix3(const std::string &name, int count, bool transpose, const float *t) const
{
  Use();
  GL_CALL(glUniformMatrix3fv(GetLocation(name), count, transpose, t));
}

inline void ShaderGL::SetUniformMatrix4(const std::string &name, int count, bool transpose, const float *t) const
{
  Use();
  GL_CALL(glUniformMatrix4fv(GetLocation(name), count, transpose, t));
}

inline void ShaderGL::SetUniformMatrix2x3(const std::string &name, int count, bool transpose, const float *t) const
{
  Use();
  GL_CALL(glUniformMatrix2x3fv(GetLocation(name), count, transpose, t));
}

inline void ShaderGL::SetUniformMatrix3x2(const std::string &name, int count, bool transpose, const float *t) const
{
  Use();
  GL_CALL(glUniformMatrix3x2fv(GetLocation(name), count, transpose, t));
}

inline void ShaderGL::SetUniformMatrix2x4(const std::string &name, int count, bool transpose, const float *t) const
{
  Use();
  GL_CALL(glUniformMatrix2x4fv(GetLocation(name), count, transpose, t));
}

inline void ShaderGL::SetUniformMatrix4x2(const std::string &name, int count, bool transpose, const float *t) const
{
  Use();
  GL_CALL(glUniformMatrix4x2fv(GetLocation(name), count, transpose, t));
}

inline void ShaderGL::SetUniformMatrix3x4(const std::string &name, int count, bool transpose, const float *t) const
{
  Use();
  GL_CALL(glUniformMatrix3x4fv(GetLocation(name), count, transpose, t));
}

inline void ShaderGL::SetUniformMatrix4x3(const std::string &name, int count, bool transpose, const float *t) const
{
  Use();
  GL_CALL(glUniformMatrix4x3fv(GetLocation(name), count, transpose, t));
}
}

#endif