#ifndef TOLIK_UTILS_GL_HPP
#define TOLIK_UTILS_GL_HPP

#include <stdint.h>

#include "Setup.hpp"

#include "glad/glad.h"

#include "Debug/Debug.hpp"

namespace Tolik
{
constexpr std::size_t GetSizeFromGLType(uint32_t type);
template<typename Type> constexpr inline uint32_t GetGLTypeFromType() { Debug::GetLogger().Error("No gl type fot type \"@0\"", typeid(Type).name()); return GL_INT; }


// IMPLEMIENTATION


template<> constexpr inline uint32_t GetGLTypeFromType<int32_t>()  { return GL_INT; }
template<> constexpr inline uint32_t GetGLTypeFromType<uint32_t>() { return GL_UNSIGNED_INT; }
template<> constexpr inline uint32_t GetGLTypeFromType<int16_t>()  { return GL_SHORT; }
template<> constexpr inline uint32_t GetGLTypeFromType<uint16_t>() { return GL_UNSIGNED_SHORT; }
template<> constexpr inline uint32_t GetGLTypeFromType<int8_t>()   { return GL_BYTE; }
template<> constexpr inline uint32_t GetGLTypeFromType<uint8_t>()  { return GL_UNSIGNED_BYTE; }

constexpr std::size_t GetSizeFromGLType(uint32_t type)
{
  switch(type)
  {
  case GL_DOUBLE:
    return 8;
  case GL_FLOAT:
  case GL_UNSIGNED_INT:
  case GL_INT:
    return 4;
  case GL_SHORT:
  case GL_UNSIGNED_SHORT:
    return 2;
  case GL_BYTE:
  case GL_UNSIGNED_BYTE:
    return 1;
  default:
    Debug::GetLogger("main").Error("No GL_TYPE with index: @0", type);
    return 4;
  }
}
}

#endif