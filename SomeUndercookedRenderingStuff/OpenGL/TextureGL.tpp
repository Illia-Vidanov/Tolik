#ifndef TOLIK_TEXTURE_GL_TPP
#define TOLIK_TEXTURE_GL_TPP

#ifndef TOLIK_TEXTURE_GL_HPP
#error __FILE__ should only be included from TextureGL.hpp
#endif

namespace Tolik
{
template<std::size_t Index, typename... Args>
void TextureGL::SetParametrs(const std::tuple<std::pair<int, Args>...> &data) const
{
  Bind();
  // Clamp is important because compiler looks ahead and gives errors
  if constexpr(Index != sizeof...(Args) - 1)
		SetParametrs<std::clamp(Index + 1, static_cast<std::size_t>(1), sizeof...(Args) - 1)>(data);

  SetParametr(std::get<0>(std::get<Index>(data)), std::get<1>(std::get<Index>(data)));
}

template<>
inline void TextureGL::SetParametr<int>(int name, int data) const
{
  GL_CALL(glTexParameteri(m_type, name, data));
}

template<>
inline void TextureGL::SetParametr<float>(int name, float data) const
{
  GL_CALL(glTexParameterf(m_type, name, data));
}
}

#endif