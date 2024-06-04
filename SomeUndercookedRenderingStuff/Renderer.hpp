#ifndef TOLIK_RENDERER_HPP
#define TOLIK_RENDERER_HPP

#include <stdint.h>
#include <set>

#include "Setup.hpp"

#include "Math/Constants.hpp"
#include "Debug/Debug.hpp"
#include "Rendering/Mesh.hpp"
// Because we need to construct it in template function CreateMeshGL
#include "Rendering/OpenGL/MeshGL.hpp"

namespace Tolik
{
class Window;
class Camera;

struct Vertex
{
  Vertex(DefFloatType newX, DefFloatType newY, DefFloatType newZ) : x(newX), y(newY), z(newZ) {}
  
  DefFloatType x, y, z;
};

// MeshType is enum that determins what shader and other stuff we will use in creating and rendering mesh
enum class MeshType : uint32_t;

enum class RenderAPIType : int8_t
{
  OpenGL
};

struct MeshLessThen
{
  inline constexpr bool operator()(const Mesh *mesh1, const Mesh *mesh2) const { return mesh1->GetMeshType() < mesh2->GetMeshType(); }
};

// Yes. I know about virtual functions, but a) they meight be slower; b) you can't use templates
class Renderer
{
public:
  // First initialization phase (before creating window)
  Renderer(RenderAPIType api);
  // Second initialization phase (after creating window)
  inline void SetWindow(Window *window);
  // Couldn't use destructor because we need to control order of destruction in Window class
  inline void Quit();

  inline void RenderMesh(Mesh *mesh, std::size_t count = 1);

  inline void StartFrame() const;
  inline void Render(const Camera &camera);
  inline void EndFrame() const;

  template<typename VertexType, typename IndexType> inline Mesh *CreateMesh(MeshType meshType, VertexType *verts, std::size_t vertexCount, IndexType *inds, std::size_t indexCount) const;
  
  // Function for debugging. Expected to use const_cast to acces this function
  inline void Debug(void *data);
  inline uint32_t GetSDLWindowFlags() const;
  inline void UpdateDrawbleSize();

  inline constexpr int GetDrawbleWidth() const { return m_width; }
  inline constexpr int GetDrawbleHeight() const { return m_height; }

private:
  // GL implementations

  void InitGL();
  void SetWindowGL(Window *window);

  void QuitGL();

  void StartFrameGL() const;
  void RenderGL(const Camera &camera);
  void EndFrameGL() const;

  template<typename VertexType, typename IndexType> inline Mesh *CreateMeshGL(MeshType meshType, VertexType *verts, std::size_t vertexCount, IndexType *inds, std::size_t indexCount) const;

  void DebugGL(void *data) const;
  void UpdateDrawbleSizeGL();
  uint32_t GetSDLWindowFlagsGL() const;


  const RenderAPIType m_api;
  int m_width, m_height;
  void *m_resources;
  void *m_context;
  Window *m_window;
  std::multiset<Mesh*, MeshLessThen> meshes;
};
}

#include "Rendering/Renderer.tpp"

#endif