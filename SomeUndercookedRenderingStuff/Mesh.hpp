#ifndef TOLIK_MESH_HPP
#define TOLIK_MESH_HPP

#include <stdint.h>

#include "Setup.hpp"

namespace Tolik
{
enum class MeshType : uint32_t;

class Mesh
{
public:
  virtual ~Mesh() = default;
  inline constexpr MeshType GetMeshType() const { return m_meshType; }

protected:
  Mesh(const MeshType meshType) : m_meshType(meshType) {}

  const MeshType m_meshType;
};
}

#endif