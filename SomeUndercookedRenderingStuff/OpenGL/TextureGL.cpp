#include "Rendering/OpenGL/TextureGL.hpp"

#include <string>
#include <stdint.h>
#include <tuple>
#include <utility>

#include "Setup.hpp"

#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Debug/Debug.hpp"
#include "Math/Vector.hpp"

namespace Tolik
{
void TextureGL::BufferData(const std::string &path, const Vec2i &dimensions)
{
  //m_path = path;
  m_isBuffered = true;

  int height, width;

  // TODO: own function to read files
  uint8_t *data = stbi_load(path.c_str(), &width, &height, nullptr, static_cast<bool>(m_flags & TextureFlags::IsTransparent) ? STBI_rgb_alpha : STBI_rgb);
  
  if(!data)
    return Debug::GetLogger().Error("Failed to load texture ", path);

  const uint32_t format = static_cast<bool>(m_flags & TextureFlags::IsTransparent) ? GL_RGBA : GL_RGB;

  Bind();


  if(m_type == GL_TEXTURE_1D || m_type == GL_PROXY_TEXTURE_1D)
    GL_CALL(glTexImage1D(m_type, 0, format, width, 0, format, GL_UNSIGNED_BYTE, data));
  else if(dimensions != Vec2i::zero())
  {
    const uint32_t bytesPerPixel = static_cast<bool>(m_flags & TextureFlags::IsTransparent) ? 4 : 3;
    const uint32_t textureSize = width * height * bytesPerPixel;
    const uint32_t tileWidth = width / dimensions.x();
    const uint32_t tileHeight = height / dimensions.y();
    const uint32_t cellCount = dimensions.x() * dimensions.y();

    uint8_t *formatedData = new uint8_t[textureSize];
    for(uint32_t i = 0; i < cellCount; i++)
    {
      for(uint32_t y = 0; y < tileHeight; y++)
      {
        const uint32_t dataStart = ((i % dimensions.y()) * tileWidth + tileHeight * width * (i / dimensions.x()) + y * width) * bytesPerPixel;
        std::copy(&data[dataStart], &data[dataStart + tileWidth * bytesPerPixel], &formatedData[(i * tileWidth * tileHeight + y * tileWidth) * bytesPerPixel]);
      }
    }
    
    GL_CALL(glTexImage3D(m_type, 0, format, tileWidth, tileHeight, cellCount, 0, format, GL_UNSIGNED_BYTE, formatedData));

    delete [] formatedData;
  }
  else
    GL_CALL(glTexImage2D(m_type, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data));

  if(static_cast<bool>(m_flags & TextureFlags::GenerateMipmap))
    GL_CALL(glGenerateMipmap(m_type));

  stbi_image_free(data);
}
}
