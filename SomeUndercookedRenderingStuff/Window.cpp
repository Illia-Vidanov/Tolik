#include "Rendering/Window.hpp"

#include "Setup.hpp"

#include "SDL2/SDL.h"

#include "Input/KeyID.hpp"
#include "Input/UserInput.hpp"
#include "Math/Vector.hpp"
#include "Debug/Debug.hpp"
#include "Rendering/Renderer.hpp"

namespace Tolik
{
struct SDL_DisplayMode : ::SDL_DisplayMode {};

Window::~Window()
{
  m_renderer.Quit();
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

Window::Window(bool *running, UserInput *userInput)
  : m_renderer(RenderAPIType::OpenGL) // Here we decide what render API we will use
  , m_running(running)
  , m_userInput(userInput)
  , m_cursor(this, m_userInput->GetAxis(InputAxis::MousePosition))
{
  m_displayMode = new SDL_DisplayMode();
  SDL_CALL(SDL_GetCurrentDisplayMode(0, m_displayMode));
  m_windowSize = Vec2i(m_displayMode->w / 2, m_displayMode->h / 2);
  m_windowCenter = m_windowSize / 2;

  SDL_CALL(m_window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_windowSize.x(), m_windowSize.y(), m_renderer.GetSDLWindowFlags()));

  m_renderer.SetWindow(this);
}

void Window::Update()
{
  m_userInput->Update();
  m_cursor.Update();
  ListenToEvents();
}

void Window::ListenToEvents()
{

  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
    if(Debug::showSDLEvents)
      Debug::GetLogger().Info("SDL_Event: ", std::hex, event.type, std::dec);

    switch(event.type)
    {
    case SDL_QUIT:
      *m_running = false;
      break;

    // Input
    case SDL_KEYDOWN:
      m_userInput->UpdateKeyDown(static_cast<uint32_t>(SDLScancodeToKeyID(event.key.keysym.scancode) | SDLKeyModToKeyMod(event.key.keysym.mod)));
      break;
    case SDL_KEYUP:
      m_userInput->UpdateKeyUp(static_cast<uint32_t>(SDLScancodeToKeyID(event.key.keysym.scancode) | SDLKeyModToKeyMod(event.key.keysym.mod)));
      break;
    case SDL_MOUSEBUTTONDOWN:
      m_userInput->UpdateMouseKeyDown(static_cast<uint32_t>(event.button.button));
      break;
    case SDL_MOUSEBUTTONUP:
      m_userInput->UpdateMouseKeyUp(static_cast<uint16_t>(event.button.button));
      break;
    case SDL_MOUSEWHEEL:
      m_userInput->UpdateMouseWheelDelta((m_userInput->GetKey(KeyID::Lshift) || m_userInput->GetKey(KeyID::Rshift)) ?
                                          Vec2(event.wheel.y, event.wheel.x) : Vec2(event.wheel.x, event.wheel.y));
      break;
    case SDL_MOUSEMOTION:
      MouseMotion(event);
      break;
    
    // Window events
    case SDL_WINDOWEVENT:
      switch(event.window.type)
      {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
          WindowResized(event);
          break;
      }
      break;

    // Unused events
    case SDL_TEXTINPUT:
      break;
    default:
      Debug::GetLogger("main").Warning("Unhandlet SDL_Event: @0", event.type);
      break;
    }
  }
}

void Window::WindowResized(const SDL_Event &event)
{
  m_windowSize = Vec2(event.window.data2, event.window.data2);
  m_windowCenter = m_windowSize / 2;
  m_renderer.UpdateDrawbleSize();
}

void Window::MouseMotion(const SDL_Event &event)
{
  if(m_cursor.IsLocked() && !m_cursor.IsHidden())
  {
    if(event.motion.xrel != 0 || event.motion.yrel != 0)
      m_cursor.Warp(m_windowCenter);
    m_userInput->UpdateMousePosition(Vec2::zero(), Vec2(event.motion.xrel, event.motion.yrel));
  }
  else if(m_cursor.IsLocked())
    m_userInput->UpdateMousePosition(Vec2::zero(), Vec2(event.motion.xrel, event.motion.yrel));
  else
    m_userInput->UpdateMousePosition(Vec2(event.motion.x, event.motion.y), Vec2(event.motion.xrel, event.motion.yrel));
}
}