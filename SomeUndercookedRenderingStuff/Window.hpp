#ifndef TOLIK_WINDOW_HPP
#define TOLIK_WINDOW_HPP

#include "Setup.hpp"

#include "Rendering/Renderer.hpp"
#include "Rendering/Cursor.hpp"
#include "Math/Vector.hpp"

class SDL_Window;
union SDL_Event;

namespace Tolik
{
class UserInput;
class Renderer;
struct SDL_DisplayMode;

class Window
{
public:
  Window(bool *running, UserInput *userInput);
  ~Window();



  void Update();
  inline SDL_Window *GetSDLWindow() const { return m_window; }
  inline Renderer &GetRenderer() { return m_renderer; }
  inline Cursor &GetCursor() { return m_cursor; }
  inline int GetWidth() const { return m_windowSize.x(); }
  inline int GetHeight() const { return m_windowSize.y(); }
  inline const Vec2i &GetSize() const { return m_windowSize; }
  inline const Vec2i &GetWindowCenter() const { return m_windowCenter; }


private:
  void ListenToEvents();
  void WindowResized(const SDL_Event &event);
  void MouseMotion(const SDL_Event &event);

  Renderer m_renderer;
  bool *m_running;
  UserInput *m_userInput;
  SDL_Window *m_window;
  Vec2i m_windowSize;
  Vec2i m_windowCenter;
  Cursor m_cursor;
  SDL_DisplayMode *m_displayMode;
};
}

#endif