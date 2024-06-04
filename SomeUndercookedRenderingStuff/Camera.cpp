#include "Rendering/Camera.hpp"

#include "Setup.hpp"

#include "glm/ext.hpp"

#include "Math/Transform.hpp"
#include "Debug/Debug.hpp"

namespace Tolik
{
glm::mat4 Tolik::Camera::GetViewMatrix() const
{
  glm::mat4 view;
  view[0] = Vec4(transform.Right()).ToGlm();
  view[1] = Vec4(transform.Up()).ToGlm();
  view[2] = Vec4(transform.Backward()).ToGlm();
  view[3] = Vec4(transform.GetPosition(), 1).ToGlm();
  return glm::inverse(view);
}
}