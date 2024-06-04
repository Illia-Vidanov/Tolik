#ifndef TOLIK_CURSOR_HPP
#define TOLIK_CURSOR_HPP

#include <stdint.h>
#include <string>

#include "Setup.hpp"

#include "Math/Vector.hpp"
#include "Utilities/EnumFunctions.hpp"

namespace Tolik
{
class Window;

enum class CursorState : uint8_t
{
  NONE = 0,
  Custom = TOLIK_BIT(0),

  Locked = TOLIK_BIT(1),
  Grabed = TOLIK_BIT(2),
  Hidden = TOLIK_BIT(3),
};

/* TODO:
1. Custom texture (sprite class required)
2. Animated texture
*/

class Cursor
{
friend class Window;

public:
  Cursor(Window *window, const Vec2i &position) : m_window(window), m_position(position) {}
  ~Cursor() { ClearTexture(); }

  void SetTexture(const std::string &path);
  void ClearTexture();

  inline const Vec2i &GetHotspotPosition() const { return m_hotspotPosition; }
  inline void SetCursorHotspot(int x, int y) { m_hotspotPosition = Vec2i(x, y); }
  inline void SetCursorHotspot(const Vec2i &position) { m_hotspotPosition = position; }

  inline const Vec2i &GetPosition() const { return m_position; }
  void Warp(int x, int y) const;
  inline void Warp(const Vec2i &position) const { Warp(position.x(), position.y()); }

  inline CursorState GetState() const { return m_state; }
  inline bool IsCustom() const { return static_cast<bool>(m_state & CursorState::Custom); }
  inline bool IsLocked() const { return static_cast<bool>(m_state & CursorState::Locked); }
  inline bool IsGrabed() const { return static_cast<bool>(m_state & CursorState::Grabed); }
  inline bool IsHidden() const { return static_cast<bool>(m_state & CursorState::Hidden); }

  inline void SetLocked(bool state) { state ? Lock() : Unlock(); }
  inline void SetGrabed(bool state) { state ? Grab() : Ungrab(); }
  inline void SetHidden(bool state) { state ? Hide() : Show(); }
  void SetState(CursorState state);
  void Lock();
  void Unlock();
  void Grab();
  void Ungrab();
  void Hide();
  void Show();


private:
  void Update();

  Window *m_window;
  CursorState m_state;
  Vec2i m_hotspotPosition;
  const Vec2i &m_position;
};
}

#endif