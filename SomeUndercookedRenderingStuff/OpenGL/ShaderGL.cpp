#include "Rendering/OpenGL/ShaderGL.hpp"

#include <stdint.h>
#include <string>

#include "Setup.hpp"

#include "glad/glad.h"

#include "Utilities/FileReader.hpp"
#include "Debug/Debug.hpp"

namespace Tolik
{
uint32_t ShaderGL::CompileShader(const std::string &path) const
{
  std::string source;
  FileReader::ReadTxtFile(path, source);
  const char *charSource = source.c_str();

  int succes;
  uint32_t shader;
  GL_CALL(shader = glCreateShader(ExtensionToShaderType(FileReader::GetExtention(path))));
  GL_CALL(glShaderSource(shader, 1, &charSource, NULL));
  GL_CALL(glCompileShader(shader));
  GL_CALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &succes));
  if(!succes)
  {
    char buffer[512];
    GL_CALL(glGetShaderInfoLog(shader, 512, NULL, buffer));
    Debug::GetLogger("main").Error("In compiling @0\n @1", path, buffer);
  }

  return shader;
}

void ShaderGL::CreateProgram(std::initializer_list<uint32_t> list)
{
  GL_CALL(m_id = glCreateProgram());
  for(auto shader : list)
    GL_CALL(glAttachShader(m_id, shader));
  
  int succes;
  GL_CALL(glLinkProgram(m_id));
  GL_CALL(glGetProgramiv(m_id, GL_LINK_STATUS, &succes));
  if(!succes)
  {
    char buffer[512];
    GL_CALL(glGetProgramInfoLog(m_id, 512, NULL, buffer));
    Debug::GetLogger("main").Error("Error in linking shaders ", buffer);
  }

  for(auto shader : list)
    GL_CALL(glDeleteShader(shader));
}

int ShaderGL::GetLocation(const std::string &name) const
{
  int result;
  GL_CALL(result = glGetUniformLocation(m_id, name.c_str()));
  if(result == -1)
  {
    Debug::GetLogger("main").Error(name, " does not correspond to an active uniform variable in \
    program, name starts with the reserved prefix \"gl_\", or name is associated with an atomic counter or a named uniform block.");
    return 0;
  }

  return result;
}
}